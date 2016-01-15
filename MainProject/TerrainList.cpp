#include "stdafx.h"
#include "TerrainList.h"

namespace {
	static float gridToCenter(int32_t gridPos, float center) {
		return ((gridPos + center) * GRID_INCREMENT) - GRID_OFFSET;
	}

	struct GridPos {
		int32_t x;
		int32_t z;

		GridPos() : x(0), z(0) {}
		GridPos(int32_t x, int32_t z) : x(x), z(z) {}
	};

	template <class T>
	class ShiftingArray {
	public:
		ShiftingArray() : buffer(NULL) { setSize(0); }

		ShiftingArray(int32_t n): buffer(NULL) { setSize(n); }

		~ShiftingArray() { setSize(0);}

		void setSize(size_t size) {
			if (buffer) delete[] buffer;
			if (size > 0) {
				buffer = new T[size];
			}
			n = size;
			offset = 0;
		}

		T& operator[](int32_t index) { return buffer[(index + offset + n) % n]; }

		void shift(int32_t amount) { offset = (offset + amount + n) % n; }

		int32_t size() const { return n; }

	private:
		T* buffer;
		int32_t n;
		int32_t offset;
	};
}

class ChunkMap {
public:
	ChunkMap(int32_t sqRadius) : radius(sqRadius), items(sqRadius) {
		for (int32_t i = 0; i < sqRadius; ++i) {
			items[i].setSize(sqRadius);
		}
	}

	void shiftX(int32_t amount, float chunkX, float chunkZ, Perlin* perlin) {
		int32_t step = amount < 0 ? -1 : 1;
		int32_t outOfDate = amount < 0 ? 0 : radius - 1;
		float cX = gridToCenter(outOfDate, chunkX);
		for (int32_t i = 0; i != amount; i += step) {
			for (int32_t z = 0; z < radius; ++z) {
				float cZ = gridToCenter(z, chunkZ);
				items[z].shift(step);
				items[z][outOfDate].rebase(cX, cZ, perlin);
			}
		}
	}

	void shiftZ(int32_t amount, float chunkX, float chunkZ, Perlin* perlin) {
		int32_t step = amount < 0 ? -1 : 1;
		int32_t outOfDate = amount < 0 ? 0 : radius - 1;
		float cZ = gridToCenter(outOfDate, chunkZ);
		for (int32_t i = 0; i != amount; i += step) {
			items.shift(step);
			for (int32_t x = 0; x < radius; ++x) {
				float cX = gridToCenter(x, chunkX);
				items[outOfDate][x].rebase(cX, cZ, perlin);
			}
		}
	}

	int32_t getRadius() const { return radius; }

	TerrainChunk* item(int32_t x, int32_t z) {
		return &items[z][x];
	}

private:
	int32_t radius;
	ShiftingArray<ShiftingArray<TerrainChunk>> items;
};

TerrainList::TerrainList(const Perlin& p) {
	this->perlin = p;
	chunkMap = new ChunkMap((int32_t)ceilf(CHUNKS_PER_SIDE));
}

TerrainList::~TerrainList() {
	delete chunkMap;
}

TerrainList::const_iterator::const_iterator(int32_t x, int32_t z, const TerrainList* list) :x(x), z(z), list(list) {}

bool TerrainList::const_iterator::operator!=(const const_iterator& other) const {
	return list != other.list || x != other.x || z != other.z;
}

TerrainList::const_iterator& TerrainList::const_iterator::operator++() {
	if (++x >= list->chunkMap->getRadius()) {
		x = 0;
		++z;
	}
	return *this;
}

TerrainList::ChunkRef TerrainList::const_iterator::operator*() const {
	ChunkRef ref;
	ref.chunk = list->chunkMap->item(x, z);
	ref.centerX = gridToCenter(x, list->chunkX);
	ref.centerY = gridToCenter(z, list->chunkZ);
	return ref;
}

TerrainList::const_iterator TerrainList::begin() const {
	return const_iterator(0, 0, this);
}

TerrainList::const_iterator TerrainList::end() const {
	return const_iterator(0, chunkMap->getRadius(), this);
}

void TerrainList::setChar(Character* c) {
	character = c;
}

static void worldPosToGridPos(float worldX, float worldZ, float& gridX, float& gridZ) {
	gridX = floorf(worldX / (SCALING_FACTOR * GRID_INCREMENT) + 0.5f);
	gridZ = floorf(worldZ / (SCALING_FACTOR * GRID_INCREMENT) + 0.5f);
}

void TerrainList::firstInit() {
	chunkX = chunkZ = 0.f;

	int32_t radius = chunkMap->getRadius();
	for (int32_t z = 0; z < radius; ++z) {
		float cZ = gridToCenter(z, chunkZ);
		for (int32_t x = 0; x < radius; ++x) {
			float cX = gridToCenter(x, chunkX);
			chunkMap->item(x, z)->initialize(cX, cZ, &perlin);
		}
	}
}

void TerrainList::examineChunks() {
	glm::vec3 charPos = character->getPos();
	float newChunkX, newChunkZ;
	worldPosToGridPos(charPos.x, charPos.z, newChunkX, newChunkZ);

	int32_t shiftX = (int32_t)(newChunkX - chunkX);
	int32_t shiftZ = (int32_t)(newChunkZ - chunkZ);

	if (shiftX != 0) {
		chunkX = newChunkX;
		chunkMap->shiftX(shiftX, chunkX, chunkZ, &perlin);
	}

	if (shiftZ != 0) {
		chunkZ = newChunkZ;
		chunkMap->shiftZ(shiftZ, chunkX, chunkZ, &perlin);
	}
}
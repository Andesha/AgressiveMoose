#version 130

struct globLight{
	vec3 direction ;
	vec3 amb;
	vec3 diff;
};

in vec4 fragmentColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

uniform sampler2D texIm;	// ground texture
uniform vec3 viewerPos;		// position of viewer for specular
uniform globLight light;

void main(){


	// the ambiant
	vec3 ambiant = light.amb * vec3(texture(texIm, TexCoord)); 

	//the diffuse
	// used for diffuse lighting
	vec3 lightDir = normalize(-light.direction);
	float diffFactor = max(dot(Normal,lightDir), 0.0);
	vec3 diffuse = light.diff * diffFactor * vec3(texture(texIm, TexCoord));
	//color = texture(texIm, TexCoord);
	color = vec4(ambiant + diffuse, 1.0);
}
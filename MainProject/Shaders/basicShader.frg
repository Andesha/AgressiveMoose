#version 130

in vec4 fragmentColor;

out vec4 color;
in vec2 TexCoord;
uniform sampler2D texIm;

void main(){
	color = texture2D(texIm, TexCoord);
	// texture(texIm, TexCoord);
}
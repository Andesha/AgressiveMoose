#version 130

in vec4 fragmentColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texIm;

void main(){
	color = texture(texIm,TexCoord);
}
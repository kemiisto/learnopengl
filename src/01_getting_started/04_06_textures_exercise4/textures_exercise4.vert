#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTextureCoord;

out vec3 color;
out vec2 textureCoord;

void main() {
	gl_Position = vec4(vertexPosition, 1.0);
	color = vertexColor;
	textureCoord = vertexTextureCoord;
}

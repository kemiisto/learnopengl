#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTextureCoord;

uniform mat4 transformation;

out vec2 textureCoord;

void main() {
	gl_Position = transformation * vec4(vertexPosition, 1.0);
	textureCoord = vertexTextureCoord;
}
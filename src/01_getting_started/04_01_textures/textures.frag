#version 330 core

in vec3 color;
in vec2 textureCoord;
uniform sampler2D texture0;

out vec4 fragmentColor;

void main() {
	fragmentColor = texture(texture0, textureCoord) * vec4(color, 1.0);
}

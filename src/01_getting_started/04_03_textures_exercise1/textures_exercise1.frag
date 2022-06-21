#version 330 core

in vec3 color;
in vec2 textureCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 fragmentColor;

void main() {
	fragmentColor = mix(
		texture(texture0, textureCoord),
		texture(texture1, vec2(-textureCoord.x, textureCoord.y)),
		0.2
	);
}

#version 330 core

in vec2 texCoords;

uniform vec3 MeshColor;
uniform float MeshTransparency;
uniform sampler2D Texture0;

out vec4 FragColor;

void main() {
    FragColor = texture(Texture0, texCoords) * vec4(MeshColor, MeshTransparency);
}
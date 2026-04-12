#version 330 core

in vec2 texCoords;

uniform vec3 MeshColor;
uniform float MeshTransparency;

out vec4 FragColor;

void main() {
    FragColor = vec4(MeshColor, MeshTransparency);
}
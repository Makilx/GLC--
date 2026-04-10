#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texPos;

uniform vec3 MeshPos;
uniform mat4 Camera;

out vec2 texCoords;

void main() {
    texCoords = texPos;

    gl_Position = Camera * vec4(aPos + MeshPos, 0);
}

#version 330 core

in vec2 texCoords;

uniform vec3 MeshColor;
uniform float MeshTransparency;
uniform sampler2D Texture0;

out vec4 FragColor;

void main() {
    vec4 textureImage = vec4(1);

    if (texCoords == vec2(-1, -1)) {
        textureImage = texture(Texture0, texCoords);
        if (textureImage.a <= 0.1) discard;
    }

    FragColor = textureImage * vec4(MeshColor, MeshTransparency);
}

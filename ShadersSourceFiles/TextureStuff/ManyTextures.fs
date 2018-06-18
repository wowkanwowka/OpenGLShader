#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D first_texture;
uniform sampler2D second_texture;

void main() {
    FragColor = mix(texture(first_texture, TexCoord), texture(second_texture, TexCoord), 0.2);
}
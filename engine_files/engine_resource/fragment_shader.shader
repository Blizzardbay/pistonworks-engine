#version 330 core
out vec4 FragColor;

in vec2 fragment_texture_coords;
in vec3 fragment_color;
flat in int fragment_is_colored;

uniform sampler2D this_texture;

void main() {
    if (fragment_is_colored > 0) {
        FragColor = texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y)) * vec4(fragment_color, 1.0f);
    }
    else {
        FragColor = texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y));
    }
}
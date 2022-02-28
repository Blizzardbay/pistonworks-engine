#version 330 core
out vec4 FragColor;

in vec2 fragment_texture_coords;
in vec4 fragment_color;
flat in int fragment_is_colored;
flat in int fragment_is_text;

uniform sampler2D this_texture;

void main() {
    if (fragment_is_colored > 0) {
        if (fragment_is_text > 0) {
            FragColor = vec4(1.0, 1.0, 1.0, texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y)).r) * fragment_color;
        }
        else {
            FragColor = texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y)) * fragment_color;
        }
    }
    else {
        FragColor = texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y));
    }
}
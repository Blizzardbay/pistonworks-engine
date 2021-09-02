#version 330 core
out vec4 FragColor;

in vec2 fragment_texture_coords;
in vec4 fragment_color;
flat in int fragment_is_colored;

uniform sampler2D this_texture;

void main() {
    if (fragment_is_colored > 0) {
        vec4 temp = vec4(1.0, 1.0, 1.0, texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y)).r);
        FragColor = fragment_color * temp;
    }
    else {
        FragColor = texture(this_texture, vec2(fragment_texture_coords.x, fragment_texture_coords.y));
    }
}
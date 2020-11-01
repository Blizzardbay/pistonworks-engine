#version 330 core

layout(location = 0) in vec3 object_position;
layout(location = 1) in vec2 object_texture_coords;
layout(location = 2) in vec3 object_color;

out vec2 fragment_texture_coords;
out vec3 fragment_color;
flat out int fragment_is_colored;

uniform mat4 object_model;
uniform mat4 object_view;
uniform mat4 object_projection;

uniform int object_is_colored;

void main() {
    gl_Position = object_projection * object_view * object_model * vec4(object_position.x, object_position.y, 0.0, 1.0);
    fragment_texture_coords = object_texture_coords;
    fragment_color = object_color;
    fragment_is_colored = object_is_colored;
}
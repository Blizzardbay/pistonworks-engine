#version 460 core
#extension GL_ARB_bindless_texture : enable

layout(location = 0) in vec3 object_position;
layout(location = 1) in vec2 object_texture_coords;
layout(location = 2) in vec4 object_color;
layout(location = 3) in int object_is_colored;
layout(location = 4) in int object_is_text;
layout(location = 5) in int object_model_index;
layout(location = 6) in uvec2 object_texture_handle;

layout(std430, binding = 0) buffer object_matrices {
    mat4 object_matrix_data[];
};

out vec2 fragment_texture_coords;
out vec4 fragment_color;
flat out int fragment_is_colored;
flat out int fragment_is_text;
flat out uvec2 fragment_texture_handle;

uniform mat4 object_view;
uniform mat4 object_projection;

void main() {
    gl_Position = object_projection * object_view * object_matrix_data[object_model_index] * vec4(object_position, 1.0);

    fragment_texture_coords = object_texture_coords;
    fragment_color = object_color;
    fragment_is_colored = object_is_colored;
    fragment_is_text = object_is_text;
    fragment_texture_handle = object_texture_handle;
}
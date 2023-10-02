#version 450 core
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_NV_gpu_shader5 : enable
#extension GL_ARB_bindless_texture : enable

layout(location = 0) in vec3 object_position;
layout(location = 1) in vec2 object_texture_coords;
layout(location = 2) in vec4 object_color;
layout(location = 3) in mat4 object_model;
layout(location = 7) in int object_is_colored;
layout(location = 8) in int object_is_text;
layout(location = 9) in uint64_t object_texture_handle;

out vec2 fragment_texture_coords;
out vec4 fragment_color;
flat out int fragment_is_colored;
flat out int fragment_is_text;
flat out uint64_t fragment_texture_handle;

uniform mat4 object_view;
uniform mat4 object_projection;

void main() {
    gl_Position = object_projection * object_view * object_model * vec4(object_position, 1.0);

    fragment_texture_coords = object_texture_coords;
    fragment_color = object_color;
    fragment_is_colored = object_is_colored;
    fragment_is_text = object_is_text;
    fragment_texture_handle = object_texture_handle;
}
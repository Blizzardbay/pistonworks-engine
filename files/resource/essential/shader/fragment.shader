#version 450 core
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_NV_gpu_shader5 : enable
#extension GL_ARB_bindless_texture : enable

out vec4 FragColor;

in vec2 fragment_texture_coords;
in vec4 fragment_color;
flat in int fragment_is_colored;
flat in int fragment_is_text;
flat in uint64_t fragment_texture_handle;

void main() {
    // Not readable so explanation
    // if(fragment_is_text == 1) texture is not used so text vec4 gets used
    // if(fragment_is_text == 0) texture is used so text vec4 is not used
    // if(fragment_is_colored == 1) normal passed color vec4 is used
    // if(fragment_is_colored == 0) color vec4 = vec4(1.0) so other setting stay the same
    FragColor = vec4((texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y)) * (vec4(1.0) * int(!bool(fragment_is_text)))) + (vec4(1.0) * fragment_is_text)) *
        vec4((fragment_color * (vec4(1.0) * fragment_is_colored)) + ((vec4(1.0) * int(!bool(fragment_is_colored))))) *
        vec4((vec4(1.0, 1.0, 1.0, texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y)).r) * (vec4(1.0) * fragment_is_text))
            + ((vec4(1.0) * int(!bool(fragment_is_text)))));
    //if (fragment_is_colored > 0) {
        //if (fragment_is_text > 0) {
            //FragColor = vec4(1.0, 1.0, 1.0, texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y)).r) * fragment_color;
        //}
        //else {
           // FragColor = texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y)) * fragment_color;
        //}
   // }
    //else {
        //if (fragment_is_text > 0) {
            //FragColor = vec4(1.0, 1.0, 1.0, texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y)).r);
        //}
        //else {
            //FragColor = texture2D(sampler2D(fragment_texture_handle), vec2(fragment_texture_coords.x, fragment_texture_coords.y));
        //}
    //}
}
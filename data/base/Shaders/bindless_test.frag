#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core_color.frag.glsl"

layout(location = 0) in vec2 in_tex_coord;

layout(set = 1, binding = 0) uniform sampler2D in_tex_sampler[];

vec4 get_tex_color()
{
    return texture(in_tex_sampler[1], in_tex_coord);
}

void main() 
{
   out_color = get_tex_color();
}
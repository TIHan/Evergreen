#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;

layout(location = 0) out vec2 out_tex_coord;

void main() 
{
    out_tex_coord = in_tex_coord;
    gl_Position = vec4(in_position.x, in_position.y, 0, 1);
}
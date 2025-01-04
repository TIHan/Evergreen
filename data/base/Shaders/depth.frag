#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec2 in_tex_coord;

layout(set = 2, binding = 0) uniform sampler2D in_tex_sampler;

void main() 
{
   vec4 color = texture(in_tex_sampler, in_tex_coord);
   if (color.a == 0)
   {
      discard;
   }
}

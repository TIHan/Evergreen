#version 450
#extension GL_GOOGLE_include_directive : enable
#extension GL_EXT_nonuniform_qualifier : require
#include "core.glsl"
#include "core_tex.frag.glsl"
#include "core_color.frag.glsl"

layout(location = 1) in flat int in_texture_index;

layout(set = 5, binding = 0) uniform sampler2D in_textures[];

vec4 get_tex_color_bindless()
{
   return texture(in_textures[in_texture_index], in_tex_coord);
}

void main() 
{
   vec4 color = get_tex_color_bindless();
   if (color.a != 1)
   {
      discard;
   }

   out_color = color;
}
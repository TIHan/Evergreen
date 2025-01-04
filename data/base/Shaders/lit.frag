#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"
#include "core_tex.frag.glsl"
#include "core_color.frag.glsl"
#include "core_input.frag.glsl"
#include "lit_core.glsl"
#include "shadow_core.glsl"

bool is_lit(vec3 light_space_ndc, vec3 tex_coord_with_index)
{
   if (light_space_ndc.z <= texture(in_shadow_maps, tex_coord_with_index).x && light_space_ndc.z <= texture(in_sprite_shadow_maps, tex_coord_with_index).x)
   {
      return true;
   }
   return false;
}
#include "abstract_shadow.glsl"

void main() 
{
   vec4 color = get_tex_color();
   if (color.a != 1)
   {
      discard;
   }

   float shadow = compute_shadow(in_normal, iViewInverse[3].xyz, in_position_world.xyz);
   float diffuse = compute_diffuse(in_normal, in_position_world.xyz);
   color.a = 0.5; // REMOVE THIS; this is just temporary to test out transparency
   out_color = color * diffuse * shadow;
}
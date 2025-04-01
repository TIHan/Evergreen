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

// Hash function to generate pseudo-random numbers
float rand(vec2 co) 
{
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 stochasticTexture(sampler2D tex, vec2 uv, float noiseStrength) 
{
    vec2 tileUV = uv;
    vec2 baseTile = floor(tileUV);
    vec2 fractUV = fract(tileUV);
    
    // Generate random jitter to offset UVs and break tiling patterns
    vec2 randomOffset = vec2(rand(baseTile), rand(baseTile + vec2(1.0, 1.0))) - 0.5;
    randomOffset *= noiseStrength; // Scale randomness based on strength
    
    vec2 jitteredUV = (baseTile + fractUV + randomOffset);
    
    return texture(tex, jitteredUV);
}

vec4 get_tex_color_repeat()
{
   vec2 uv = in_tex_coord * textureSize(in_tex_sampler, 0);
   vec4 color = texture(in_tex_sampler, uv);
   float dist = length(iViewInverse[3].xyz - in_position_world.xyz);
   float minValue = 10.0;
   float maxValue = 25.0;
   float alpha = smoothstep(minValue, maxValue, dist);

   vec4 stochasticColor = stochasticTexture(in_tex_sampler, uv, 1);
   return mix(color, stochasticColor, alpha);
}

void main() 
{
   vec4 color = get_tex_color_repeat();
   if (color.a != 1)
   {
      discard;
   }

   float shadow = compute_shadow(in_normal, iViewInverse[3].xyz, in_position_world.xyz);
   float diffuse = compute_diffuse(in_normal, in_position_world.xyz);
   color.a = 0.5; // REMOVE THIS; this is just temporary to test out transparency
   out_color = color * diffuse * shadow;
}
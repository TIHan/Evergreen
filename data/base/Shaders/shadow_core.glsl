layout(set = 4, binding = 0) uniform sampler2DArray in_shadow_maps;
layout(set = 4, binding = 1) uniform sampler2DArray in_sprite_shadow_maps;
layout(set = 4, binding = 2) uniform ShadowMapUniform
{
   int shadowMapCount;
};
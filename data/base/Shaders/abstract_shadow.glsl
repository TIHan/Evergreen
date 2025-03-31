// Abstract
// bool is_lit(vec3 light_space_ndc, vec3 tex_coord_with_index)

#define EPSILON 0.00001

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

float compute_raw_shadow_factor(vec4 light_space_pos, int shadowMapIndex)
{
   // Convert light space position to NDC
   vec3 light_space_ndc = light_space_pos.xyz /= light_space_pos.w;
 
   // If the fragment is outside the light's projection then it is outside
   // the light's influence, which means it is in the shadow (notice that
   // such sample would be outside the shadow map image)
   if (abs(light_space_ndc.x) > 1.0 ||
      abs(light_space_ndc.y) > 1.0 ||
      abs(light_space_ndc.z) > 1.0)
      return 0;
 
   // Translate from NDC to shadow map space (Vulkan's Z is already in [0..1])
   vec2 shadow_map_coord = light_space_ndc.xy * 0.5 + 0.5;

   if (is_lit(light_space_ndc, vec3(shadow_map_coord.xy, shadowMapIndex)))
   {
      return 0;
   }
   return 1;
} 


float compute_shadow_factor(vec4 light_space_pos, int shadowMapIndex, uint shadow_map_size, uint pcf_size)
{
   vec3 light_space_ndc = light_space_pos.xyz /= light_space_pos.w;
 
   if (abs(light_space_ndc.x) > 1.0 ||
      abs(light_space_ndc.y) > 1.0 ||
      abs(light_space_ndc.z) > 1.0)
      return 0; // In the shadow
 
   vec2 shadow_map_coord = light_space_ndc.xy * 0.5 + 0.5;
 
   // compute total number of samples to take from the shadow map
   int pcf_size_minus_1 = int(pcf_size - 1);
   float kernel_size = 2.0 * pcf_size_minus_1 - 0.1;
   float num_samples = kernel_size * kernel_size;
 
   // Counter for the shadow map samples not in the shadow
   float lighted_count = 0.0;
 
   // Take samples from the shadow map
   float shadow_map_texel_size = 1.0 / shadow_map_size;
   for (int x = -pcf_size_minus_1; x <= pcf_size_minus_1; x++)
   for (int y = -pcf_size_minus_1; y <= pcf_size_minus_1; y++) {
      // Compute coordinate for this PFC sample
      vec2 pcf_coord = shadow_map_coord + vec2(x, y) * shadow_map_texel_size;
 
      //if (is_lit(light_space_ndc, vec3(pcf_coord + poissonDisk[(abs(x + y)) % 4]/700.0, shadowMapIndex)))
      if (is_lit(light_space_ndc, vec3(pcf_coord, shadowMapIndex)))
      {
         lighted_count += 1;
      }
   }
 
   return clamp(1 - (lighted_count / num_samples), 0, 1);
}

float compute_shadow(vec3 normal, vec3 camera_position_world, vec3 position_world)
{
   float settings_ShadowAmount = 0.25;
   float camera_dist = length(camera_position_world - position_world);
   float shadow_quality_falloff = 30;
   uint pcf_size = 3;//uint(mix(3, 5, clamp(1 - (camera_dist / shadow_quality_falloff), 0, 1)));
   uint shadow_map_size_factor = 4;//uint(mix(2, 8, clamp(1 - (camera_dist / shadow_quality_falloff), 0, 1)));

   float shadow = 0.0;
   for (int i = 0; i < shadowMapCount; i++)
   {
      Light light = in_lights[i];
      vec3 lightDiff = light.view_inverse[3].xyz - position_world.xyz;
      vec3 lightDir = normalize(lightDiff);
      float lightDist = length(lightDiff);
      float shadowFactor = 1;

      if (dot(lightDir, normal) >= 0)
      {
         //shadowFactor = compute_raw_shadow_factor(in_Positions_light_space[i], i);
         shadowFactor = compute_shadow_factor(in_Positions_light_space[i], i, 2048 * shadow_map_size_factor, pcf_size);
      }

      //shadow += smoothstep(shadowFactor * settings_ShadowAmount, 0, (lightDist / 40)); 
      shadow += min((shadowFactor * settings_ShadowAmount), settings_ShadowAmount);  
   }

   return clamp((1 - shadow), 0, 1);
}
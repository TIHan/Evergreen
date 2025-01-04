layout(set = 3, binding = 0) readonly buffer lights_buf
{
   Light in_lights[8];
   int  in_light_count;
};

layout(location = 3) in flat int in_Positions_light_space_count;
layout(location = 4) in vec4 in_Positions_light_space[8];

float compute_diffuse(vec3 normal, vec3 position_world)
{
   float diffuse = 0;
   for (int i = 0; i < in_light_count; i++)
   {
      Light light = in_lights[i];

      vec3 lightDir = light.direction.xyz;
      float lightDist = length(light.view_inverse[3].xyz - position_world);

      float distFactor = clamp(1 - (lightDist / 30), 0, 1);
      float distDiffuse = smoothstep(0, 1, distFactor);

      float diff = max(dot(normal, lightDir), distFactor);

      diffuse = max(distDiffuse * diff, diffuse);
   }
   return diffuse;
}
#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 out_position_world;
layout(location = 2) out vec3 out_Normal;
layout(location = 3) out flat int out_Positions_light_space_count;
layout(location = 4) out vec4 out_Positions_light_space[8];

layout(set = 2, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

layout(set = 3, binding = 0) readonly buffer lights_buf
{
   Light in_lights[8];
   int  in_light_count;
};

void main() 
{
    Instance instance = Instances[gl_InstanceIndex];
    mat4 model = instance.transform;

    vec4 position_world = ConvertLocalToWorldSpace(inPosition, model);

    gl_Position = ConvertViewToClipSpace(ConvertWorldToViewSpace(position_world, iView), iProjection);
    fragTexCoord = inTexCoord;
    out_position_world = position_world.xyz;

    for (int i = 0; i < in_light_count; i++)
    {
        Light light = in_lights[i];
        out_Positions_light_space[i] = light.view_projection * position_world;
    }
    out_Positions_light_space_count = in_light_count;
    out_Normal = normalize(mat3(transpose(inverse(model))) * inNormal);
}
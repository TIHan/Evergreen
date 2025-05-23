#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 out_position_world;

layout(set = 2, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

void main() 
{
    mat4 model = Instances[gl_InstanceIndex].transform;

    vec3 position = inPosition;

    vec4 position_world = ConvertLocalToWorldSpace(position, model);

    gl_Position = ConvertViewToClipSpace(ConvertWorldToViewSpace(position_world, iView), iProjection);
    fragTexCoord = inTexCoord;
    out_position_world = position_world.xyz;
}
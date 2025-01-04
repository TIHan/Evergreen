#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(set = 1, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main()
{
    mat4 transform = Instances[gl_InstanceIndex].transform;

    vec3 position = inPosition;
    vec4 position_worldSpace = ConvertLocalToWorldSpace(position, transform);
    vec4 position_clipSpace = ConvertViewToClipSpace(ConvertWorldToViewSpace(position_worldSpace, iView), iProjection);

    gl_Position = position_clipSpace;
    fragTexCoord = inTexCoord;
}
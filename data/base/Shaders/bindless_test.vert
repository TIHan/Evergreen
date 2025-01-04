#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main() 
{
    fragTexCoord = inTexCoord;
    gl_Position = ConvertViewToClipSpace(ConvertWorldToViewSpace(vec4(inPosition, 1), iView), iProjection);
}
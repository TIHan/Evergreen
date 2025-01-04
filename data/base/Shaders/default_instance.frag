#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 in_position_world;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

void main() 
{
    vec4 color = texture(texSampler, fragTexCoord);
    color.w = 1;
    outColor = color;
}
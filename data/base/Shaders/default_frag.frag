#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

void main() 
{
    outColor = texture(texSampler, fragTexCoord);
}
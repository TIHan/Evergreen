#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(set = 2, binding = 0) uniform sampler2D occluderSampler;
layout(set = 3, binding = 0) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() 
{
    float depth = gl_FragCoord.z;
    vec2 uv = gl_FragCoord.xy / iResolution;
    float occluderDepth = texture(occluderSampler, uv).r;
    if (depth > occluderDepth)
        discard;

    vec4 color = texture(texSampler, fragTexCoord);
    if (color.a != 1)
    {
        discard;
    }

    outColor = vec4(1, 1, 0, 1);
}
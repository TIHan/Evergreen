#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec4 inPosition_screen;
layout(location = 2) in vec4 inPosition_world;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 4, binding = 0) uniform sampler2D texSamplerDepth;

#define EPSILON 0.00001

float rippleEffectValue(float time, vec2 texCoord)
{ 
    return cos(length(texCoord - 0.5) * 60 - time * 15) * 0.003;
}

vec2 rippleEffect(float time, vec2 texCoord, vec2 uv)
{
    vec2 ripple = vec2(0) + rippleEffectValue(time, texCoord);
    uv.x += ripple.x;
    uv.y += ripple.y;
    return uv;
}

vec3 computePosition_EyeSpace(vec2 xy, float depth)
{
    vec3 ndcPos;
    ndcPos.xy = xy;
    ndcPos.z = depth;
    ndcPos -= 0.5;
    ndcPos *= 2.0;
    vec4 clipPos;
    float a = iCameraNearZ + iCameraFarZ;
    float b = iCameraNearZ - iCameraFarZ;
    float c = 2 * iCameraNearZ * iCameraFarZ;
    float d = (ndcPos.z * b);
    float zeye = -(c / (a + d));
    clipPos.w = -zeye;
    clipPos.xyz = ndcPos * clipPos.w;
    vec4 eyePos = iProjectionInverse * clipPos;
    return eyePos.xyz;
}

vec3 computePosition_EyeSpace(float depth)
{
    return computePosition_EyeSpace(gl_FragCoord.xy / iResolution, depth);
}

void main() 
{
    vec2 xy = inPosition_screen.xy;
    vec2 uv = xy / inPosition_screen.w;
    uv = (uv + vec2(1)) * 0.5;    
    uv.y = -uv.y;

    vec4 color = texture(texSampler, uv);
    vec4 depthColor = texture(texSamplerDepth, uv);

    vec3 scenePosition = computePosition_EyeSpace(depthColor.x);
    vec3 position = computePosition_EyeSpace(gl_FragCoord.z);

    uv = rippleEffect(iTime, fragTexCoord, uv);
    uv.x = clamp(abs(uv.x), EPSILON, 1 - EPSILON);
    uv.y = -(clamp(abs(uv.y), EPSILON, 1 - EPSILON));

    float alpha = clamp(length(scenePosition - position), 0, 1);

    vec4 rippleColor = texture(texSampler, uv);
    rippleColor.y += clamp(rippleEffectValue(iTime, fragTexCoord), 0, 1) * 200 * (alpha - 0.5);
    rippleColor.z += clamp(rippleEffectValue(iTime, fragTexCoord), 0, 1) * 400 * (alpha - 0.5);

    if (alpha >= 0.5)
        outColor = rippleColor;
    else
        outColor = color;
}
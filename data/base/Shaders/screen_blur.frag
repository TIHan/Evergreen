#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 in_position_world;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 3, binding = 0) uniform sampler2D depthSampler;
layout(set = 4, binding = 0) uniform sampler2D screenDepthSampler;

const int KernelSize = 16;

// Bottom
vec4 VerticalBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = -kernel; i <= 0; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(0, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;   
    }
    
    return accumulation / count;
}

// Top
vec4 VerticalBlurReverse(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = kernel; i >= 0; i--)
    {
        vec4 value = texture(texSampler, uv + vec2(0, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }
    
    return accumulation / count;
}

vec4 TopLeftBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = 0; i <= kernel; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }
    
    return accumulation / count;
}

vec4 TopRightBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = 0; i <= kernel; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(-i * pixelSize, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }
    
    return accumulation / count;
}

// Left
vec4 HorizontalBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.x; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = -kernel; i <= 0; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, 0));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;   
    }
    
    return accumulation / count;
}

// Right
vec4 HorizontalBlurReverse(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.x; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = kernel; i >= 0; i--)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, 0));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++; 
    }
    
    return accumulation / count;
}

vec4 BottomLeftBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = 0; i <= kernel; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, -i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }
    
    return accumulation / count;
}

vec4 BottomRightBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / iResolution.y; 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = 0; i <= kernel; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(-i * pixelSize, -i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }
    
    return accumulation / count;
}

void main() 
{
    vec4 maskColor = texture(texSampler, fragTexCoord);
    if (maskColor.rgb == vec3(0)) // is it black?
    {
        vec4 bottomBlurColor = VerticalBlur(fragTexCoord);
        vec4 topBlurColor = VerticalBlurReverse(fragTexCoord);
        vec4 leftBlurColor = HorizontalBlur(fragTexCoord);
        vec4 rightBlurColor = HorizontalBlurReverse(fragTexCoord);

        vec4 topLeftBlurColor = TopLeftBlur(fragTexCoord);
        vec4 topRightBlurColor = TopRightBlur(fragTexCoord);
        vec4 bottomLeftBlurColor = BottomLeftBlur(fragTexCoord);
        vec4 bottomRightBlurColor = BottomRightBlur(fragTexCoord);

        vec4 blurColor = max(max(bottomBlurColor, topBlurColor), max(leftBlurColor, rightBlurColor));
        blurColor = max(max(blurColor, topLeftBlurColor), topRightBlurColor);
        blurColor = max(blurColor, bottomLeftBlurColor);
        blurColor = max(blurColor, bottomRightBlurColor);
        outColor = blurColor;
    }
    else
    {
        outColor = vec4(0);
    }
}
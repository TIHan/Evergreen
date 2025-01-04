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

layout(set = 3, binding = 0) uniform sampler2D texSampler;

void main()
{
    vec2 texSize = textureSize(texSampler, 0) * 0.025;
    mat4 scale = CreateScaleMatrix4x4(texSize.x, texSize.y, 1);
    mat4 model = Instances[gl_InstanceIndex].transform;

    model = model * scale;
    mat4 modelView = CreateBillboardModelView(false, model, iView, texSize.x, texSize.y);

    vec4 position_worldSpace = ConvertLocalToWorldSpace(inPosition, modelView);

    gl_Position = iProjection * position_worldSpace;
    fragTexCoord = inTexCoord;
}
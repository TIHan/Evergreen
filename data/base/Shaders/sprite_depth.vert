#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

layout(set = 1, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

layout(set = 2, binding = 0) uniform sampler2D texSampler;

// Rotation matrix around the X axis.
mat4 rotateX(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat4(
        vec4(1, 0, 0, 0),
        vec4(0, c, -s, 0),
        vec4(0, s, c, 0),
        vec4(0, 0,0, 1)
    );
}

// Rotation matrix around the Y axis.
mat4 rotateY(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat4(
        vec4(c, 0, s, 0),
        vec4(0, 1, 0, 0),
        vec4(-s, 0, c, 0),
        vec4(0, 0, 0, 1)
    );
}

// Rotation matrix around the Z axis.
mat4 rotateZ(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat4(
        vec4(c, -s, 0, 0),
        vec4(s, c, 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 0, 1)
    );
}

const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;


float get_angle(vec3 v1, vec3 v2)
{
    return acos(dot(v1, v2) / (length(v1) * length(v2)));
}

float get_directed_angle(vec3 v1, vec3 v2)
{
    return atan(v2.y, v2.x) - atan(v1.y, v1.x);
}

void main() 
{
    vec2 texSize = textureSize(texSampler, 0) * 0.025;
    mat4 scale = CreateScaleMatrix4x4(texSize.x, texSize.y, 1);
    mat4 model = Instances[gl_InstanceIndex].transform;

    vec3 dir = normalize(vec3(iViewInverse[3].xy - model[3].xy, 0));
    vec3 modelDir = normalize(vec3(GetDirectionFromModelView(model).xy, 0));
    mat4 rot = rotateY(get_directed_angle(dir, modelDir));

    model = model * rot * scale;

    if (iLightKind == LIGHT_SPOT)
    {
        gl_Position = iProjection * iView * model * vec4(inPosition, 1);
    }
    else // Directional
    {
        mat4 billboard_model_view = CreateBillboardModelView(false, model, iView, texSize.x, texSize.y);
        gl_Position = iProjection * ConvertLocalToWorldSpace(inPosition, billboard_model_view);
    }

    fragTexCoord = inTexCoord;
}
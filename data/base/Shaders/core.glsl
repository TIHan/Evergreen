vec4 ConvertLocalToWorldSpace(vec3 v_local, mat4 model)
{
    return model * vec4(v_local, 1);
}

vec4 ConvertWorldToViewSpace(vec4 v_world, mat4 view)
{
    return view * v_world;
}

vec4 ConvertViewToClipSpace(vec4 v_view, mat4 projection)
{
    return projection * v_view;
}

float GetScalingFactor(mat4 model)
{
    return sqrt(model[0][0] * model[0][0] + model[0][1] * model[0][1] + model[0][2] * model[0][2]);
}

mat4 CreateScaleMatrix4x4(float x, float y, float z)
{
	return mat4(x, 0, 0, 0,
	            0, y, 0, 0,
	            0, 0, z, 0,
	            0, 0, 0, 1);
}

vec3 GetDirectionFromModelView(mat4 m) 
{
    return normalize(vec3(m[2][0], m[2][1], -m[2][2]));
}

vec3 GetPositionFromModelView(mat4 m) 
{
    vec4 position = m[3];
    return position.xyz / position.w;
}

mat4 CreateBillboardModelView(bool useSpherical, mat4 model, mat4 view, float scaleX, float scaleY)
{
    mat4 modelView = view * model;

    // First colunm.
   modelView[0][0] = scaleX;
   modelView[0][1] = 0.0; 
   modelView[0][2] = 0.0; 

    // Second colunm. Spherical.
    if (useSpherical)
    {
        modelView[1][0] = 0.0; 
        modelView[1][1] = scaleY; 
        modelView[1][2] = 0.0; 
    }

    // Thrid colunm.
   modelView[2][0] = 0.0; 
   modelView[2][1] = 0.0; 
   modelView[2][2] = 1.0;

    return modelView;
}

mat4 translate(float x, float y, float z)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(x,   y,   z,   1.0)
    );
}

#define LIGHT_DIRECTIONAL 0
#define LIGHT_SPOT 1

layout(set = 0, binding = 0) uniform Globals {
    mat4 iView;
    mat4 iViewInverse;
    mat4 iProjection;
    mat4 iProjectionInverse;
    vec2 iResolution;
    float iTime;
    float iTimeDelta;
    float iFarZ;
    float iNearZ;
    float _iPadding0;
    float _iPadding1;
    mat4 iMainCameraView;
    mat4 iMainCameraViewInverse;
    mat4 iMainCameraProjection;
    mat4 iMainCameraProjectionInverse;
    mat4 iLightViewProjection;
    vec4 iMouse;
    vec4[6] iFrustumPlanes;
    float iAlpha;
    float iBackgroundAlpha;
    int iLightKind;
    int iSuperSamplingAmount;
};

vec4 get_main_camera_position()
{
    return iMainCameraViewInverse[3];
}

mat4 set_view_position(mat4 view, vec4 position)
{
    mat4 view_inverse = inverse(view);
    view_inverse[3] = position;
    return inverse(view_inverse);
}

struct Instance
{
    mat4 transform;
    int texture_index;
    int padding0;
    int padding1;
    int padding2;
};

struct Light
{
   mat4 view;
   mat4 view_inverse;
   mat4 projection;
   mat4 view_projection;
   vec4 direction;
};
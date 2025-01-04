#pragma once

typedef int EgAssetBool;

#define EG_EXPORT __declspec(dllexport)

typedef struct {
    float x;
    float y;
} EgAssetVector2;

typedef struct {
    float x;
    float y;
    float z;
} EgAssetVector3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} EgAssetVector4;

typedef struct {
    EgAssetVector3 min;
    EgAssetVector3 max;
} EgAssetAABB;

typedef struct {
    unsigned int* indices;
    unsigned int indexCount;

    EgAssetVector3* vertices;
    unsigned int vertexCount;

    EgAssetVector3* normals;
    EgAssetVector2* texCoords;

    EgAssetAABB aabb;

    unsigned int materialIndex;

} EgAssetMesh;

typedef struct {
    unsigned char* rawData;
    int width;
    int height;
    int channels;
    int desiredChannels;
} EgAssetImage;

extern "C" {

    EG_EXPORT EgAssetBool egAssetReadImage(unsigned char* buffer, int bufferLength, EgAssetImage* outImage);
    EG_EXPORT void egAssetFreeImage(EgAssetImage image);
    EG_EXPORT EgAssetBool egAssetReadMeshes(const char* pFilePath, void(*callbackMesh)(EgAssetMesh));

}
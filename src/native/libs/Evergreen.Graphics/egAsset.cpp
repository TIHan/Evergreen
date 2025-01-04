#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <vector>

#include "egAsset.h"

extern "C" {

	EG_EXPORT EgAssetBool egAssetReadImage(unsigned char* buffer, int bufferLength, EgAssetImage* outImage)
	{
		if (outImage)
		{
			int width, height, channels;
			outImage->desiredChannels = 4;
			unsigned char* img = stbi_load_from_memory(buffer, bufferLength, &outImage->width, &outImage->height, &outImage->channels, outImage->desiredChannels);
			if (img)
			{
				outImage->rawData = img;
				return true;
			}
		}
		return false;
	}

	EG_EXPORT void egAssetFreeImage(EgAssetImage image)
	{
		stbi_image_free(image.rawData);
	}

	EG_EXPORT EgAssetBool egAssetReadMeshes(const char* pFilePath, void(*callbackMesh)(EgAssetMesh))
	{
		auto scene = aiImportFile(pFilePath, aiProcess_Triangulate | aiProcess_GenBoundingBoxes);

		if (scene && scene->HasMeshes())
		{
			// for-each Mesh
			for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
			{
				auto mesh = scene->mMeshes[meshIndex];

				if (mesh->HasFaces() && mesh->HasTextureCoords(0) && mesh->HasNormals())
				{
					EgAssetMesh egMesh;

					egMesh.materialIndex = mesh->mMaterialIndex;

					egMesh.aabb = *((EgAssetAABB*)&mesh->mAABB);

					egMesh.vertices = (EgAssetVector3*)mesh->mVertices;
					egMesh.vertexCount = mesh->mNumVertices;

					egMesh.normals = (EgAssetVector3*)mesh->mNormals;

					auto texCoordCount = mesh->mNumUVComponents[0];
					if (texCoordCount == 2)
					{
						auto texCoords = new EgAssetVector2[egMesh.vertexCount];

						std::vector<unsigned int> indices;

						for (unsigned int i = 0; i < egMesh.vertexCount; i++)
						{
							auto v = mesh->mTextureCoords[0][i];

							texCoords[i].x = v.x;
							texCoords[i].y = 1 - v.y;
						}

						egMesh.texCoords = texCoords;

						// for-each Face
						for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
						{
							auto face = &mesh->mFaces[faceIndex];

							// for-each Index
							if (face->mNumIndices == 3 /* triangle */)
							{
								for (unsigned int i = 0; i < face->mNumIndices; i++)
								{
									indices.push_back(face->mIndices[i]);
								}
							}
						}

						egMesh.indexCount = indices.size();
						egMesh.indices = indices.data();

						callbackMesh(egMesh);

						delete[] texCoords;
					}
				}
			}

			delete scene;
			return true;
		}

		if (scene)
		{
			delete scene;
		}

		return false;
	}

}
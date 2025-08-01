#pragma once
#include <vector>

//#include "CU_Matrix.h"
#include <map>
#include <functional>
#include <string>
#include <tga2d/engine_defines.h>
#include VECTORFILE

typedef std::function<void(void*, std::string)> FUNCTION_ON_LOAD;
#define NUM_BONES_PER_VEREX 4
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
namespace Tga2D
{


	class SVertexCollection
	{
	public:
		void PushVec4(Vector4f aPos)
		{
			myData.push_back(aPos.myX);
			myData.push_back(aPos.myY);
			myData.push_back(aPos.myZ);
			myData.push_back(aPos.myW);

		}
		void PushVec2(Vector2f aPos)
		{
			myData.push_back(aPos.myX);
			myData.push_back(aPos.myY);
		}

		std::vector<float> myData;
	};



	struct VertexBoneData
	{
		unsigned int IDs[NUM_BONES_PER_VEREX];
		float Weights[NUM_BONES_PER_VEREX];

		VertexBoneData()
		{
			Reset();
		};

		void Reset()
		{
			ZERO_MEM(IDs);
			ZERO_MEM(Weights);
		}

		void AddBoneData(unsigned int BoneID, float Weight)
		{
			for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++) {
				if (Weights[i] == 0.0) {
					IDs[i] = BoneID;
					Weights[i] = Weight;
					return;
				}
			}

			// should never get here - more bones than we have space for
			assert(0);
		}
	};

	struct BoneInfo
	{
		Matrix44 BoneOffset;
		Matrix44 FinalTransformation;

		BoneInfo()
		{

		}
	};

	class CLoaderMesh
	{
	public:
		CLoaderMesh()
		{
			myShaderType = 0;
			myMaterialIndex = 0;
		}
		~CLoaderMesh() {}

		char* myVerticies;
		int myVertexCount;
		std::vector<unsigned int> myIndexes;
		unsigned int myShaderType;
		unsigned int myVertexBufferSize;
		unsigned int myMaterialIndex;



		CLoaderMesh* CreateChild() { CLoaderMesh* model = new CLoaderMesh(); myChildren.push_back(model); return model; }
		std::vector<CLoaderMesh*> myChildren;

		class CLoaderModel* myModel;

	};

	struct STexture
	{
		std::string myPath;
		unsigned int myUVSetIndex;
	};

	class CLoaderModel
	{
	public:
		CLoaderModel() {
			myIsLoaded = false; myAnimTime = 0.0f; myLodLevel = 0; myHasUvSet = false;
		}
		~CLoaderModel() {}
		void SetData(const char* aModelPath) { myModelPath = aModelPath; }

		bool myIsLoaded;


		std::vector<std::vector<STexture>> myTextures;
		CLoaderMesh* CreateMesh() { CLoaderMesh* model = new CLoaderMesh(); myMeshes.push_back(model); model->myModel = this; return model; }

		std::vector<CLoaderMesh*> myMeshes;
		std::string myModelPath;
		std::string myTexturePath;
		float myAnimTime;
		//const aiScene* myScene;
		Matrix44 m_GlobalInverseTransform;
		std::vector<BoneInfo> m_BoneInfo;
		std::map<std::string, unsigned int> m_BoneMapping;
		unsigned int m_NumBones;
		FUNCTION_ON_LOAD myFuncToCallOnLoad;
		struct aiMetadata* myMetaData;
		unsigned int myExtraShaderType;
		unsigned short myLodLevel;
		bool myHasUvSet;
	};

	class CMeshNode
	{
	public:
		~CMeshNode();
		void Render();
		class CModelShape* myModelShape = nullptr;
	};

	class CFBXLoader
	{
		friend class CMeshNode;
	public:
		CFBXLoader();
		~CFBXLoader();
		CMeshNode* LoadModel(std::string aPath, FUNCTION_ON_LOAD aFunc, unsigned int aExtraShaderType = 0);
	protected:
		//void DoLoad(class CLoaderModel* aModel, class CLoaderMesh* aMesh, struct aiMesh* aAIMesh, const struct aiScene* aScene);
		//void OnLoaded(void* someData);
		//class CMeshNode* LoadModelInternal(void* someInput);
		//int DetermineAndLoadVerticies(struct aiMesh* aMesh, CLoaderMesh* aLoaderMesh);
		//void LoadMaterials(const struct aiScene* sc, CLoaderModel* aModel);
		//void LoadTexture(int aType, std::vector<STexture>& someTextures, struct aiMaterial* aMaterial);

	};
}

#include "stdafx.h"
#include "FBXLoader.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <map>
#include <string>
#include <future>
#include <windows.h>
#include <fstream>
#include <tga2d/math/matrix44.h>
#include <tga2d/primitives/model_shape.h>

#include VECTORFILE

//#pragma comment (lib, "..\\Libs\\assimp_d.lib")
#pragma comment (lib, "assimp-vc140-mt.lib")

#define TEXTURE_SET_0 0
#define TEXTURE_SET_1 1
#define TEXTURE_SET_2 2
#define TEXTURE_SET_3 3

#define VERTEX_COLOR_SET_0 0
#define VERTEX_COLOR_SET_1 1
#define VERTEX_COLOR_SET_2 2
#define VERTEX_COLOR_SET_3 3

using namespace Tga2D;
CFBXLoader::CFBXLoader()
{
}


CFBXLoader::~CFBXLoader()
{
}

Matrix44 ConvertToEngineMatrix33(const aiMatrix3x3& AssimpMatrix)
{

	Matrix44 mat;
	mat.myMatrix[0][0] = AssimpMatrix.a1;	mat.myMatrix[0][1] = AssimpMatrix.a2;	mat.myMatrix[0][2] = AssimpMatrix.a3;	mat.myMatrix[0][3] = 0.0f;
	mat.myMatrix[1][0] = AssimpMatrix.b1;	mat.myMatrix[1][1] = AssimpMatrix.b2;	mat.myMatrix[1][2] = AssimpMatrix.b3;	mat.myMatrix[1][3] = 0.0f;
	mat.myMatrix[2][0] = AssimpMatrix.c1;	mat.myMatrix[2][1] = AssimpMatrix.c2;	mat.myMatrix[2][2] = AssimpMatrix.c3;	mat.myMatrix[2][3] = 0.0f;
	mat.myMatrix[3][0] = 0.0f;				mat.myMatrix[3][1] = 0.0f;				mat.myMatrix[3][2] = 0.0f;				mat.myMatrix[3][3] = 1.0f;
	return mat;
}

// constructor from Assimp matrix
Matrix44 ConvertToEngineMatrix44(const aiMatrix4x4& AssimpMatrix)
{
	Matrix44 mat;
	mat.myMatrix[0][0] = AssimpMatrix.a1; mat.myMatrix[0][1] = AssimpMatrix.a2; mat.myMatrix[0][2] = AssimpMatrix.a3; mat.myMatrix[0][3] = AssimpMatrix.a4;
	mat.myMatrix[1][0] = AssimpMatrix.b1; mat.myMatrix[1][1] = AssimpMatrix.b2; mat.myMatrix[1][2] = AssimpMatrix.b3; mat.myMatrix[1][3] = AssimpMatrix.b4;
	mat.myMatrix[2][0] = AssimpMatrix.c1; mat.myMatrix[2][1] = AssimpMatrix.c2; mat.myMatrix[2][2] = AssimpMatrix.c3; mat.myMatrix[2][3] = AssimpMatrix.c4;
	mat.myMatrix[3][0] = AssimpMatrix.d1; mat.myMatrix[3][1] = AssimpMatrix.d2; mat.myMatrix[3][2] = AssimpMatrix.d3; mat.myMatrix[3][3] = AssimpMatrix.d4;
	return mat;
}

int DetermineAndLoadVerticies(aiMesh* fbxMesh, CLoaderMesh* aLoaderMesh)
{
	if (!fbxMesh->HasTextureCoords(TEXTURE_SET_0))
	{
		assert("Error: No UV:s found");
		return 0;
	}

	int vertexBufferSize = 0;
	vertexBufferSize += (fbxMesh->HasPositions() ? sizeof(float) * 4 : 0);
	vertexBufferSize += (fbxMesh->HasTextureCoords(TEXTURE_SET_0) ? sizeof(float) * 2 : 0);
	vertexBufferSize += (fbxMesh->HasBones() ? sizeof(float) * 8 : 0);

	aLoaderMesh->myVertexBufferSize = vertexBufferSize;
	aLoaderMesh->myVerticies = new char[vertexBufferSize * fbxMesh->mNumVertices];
	aLoaderMesh->myVertexCount = fbxMesh->mNumVertices;

	std::vector<VertexBoneData> collectedBoneData;
	if (fbxMesh->HasBones())
	{
		collectedBoneData.resize(fbxMesh->mNumVertices);

		unsigned int BoneIndex = 0;
		for (unsigned int i = 0; i < fbxMesh->mNumBones; i++) 
		{
			
			std::string BoneName(fbxMesh->mBones[i]->mName.data);
			if (aLoaderMesh->myModel->m_BoneMapping.find(BoneName) == aLoaderMesh->myModel->m_BoneMapping.end())
			{
				// Allocate an index for a new bone
				BoneIndex = aLoaderMesh->myModel->m_NumBones;
				aLoaderMesh->myModel->m_NumBones++;
				BoneInfo bi;
				aLoaderMesh->myModel->m_BoneInfo.push_back(bi);


				Matrix44 NodeTransformation = ConvertToEngineMatrix44(fbxMesh->mBones[i]->mOffsetMatrix);

				aLoaderMesh->myModel->m_BoneInfo[BoneIndex].BoneOffset = NodeTransformation;
				aLoaderMesh->myModel->m_BoneMapping[BoneName] = BoneIndex;
			}
			else {
				BoneIndex = aLoaderMesh->myModel->m_BoneMapping[BoneName];
			}

			for (unsigned int j = 0; j < fbxMesh->mBones[i]->mNumWeights; j++) 
			{
				unsigned int VertexID = fbxMesh->mBones[i]->mWeights[j].mVertexId;
				float Weight = fbxMesh->mBones[i]->mWeights[j].mWeight;
				collectedBoneData[VertexID].AddBoneData(BoneIndex, Weight);
			}
		}
	}
	

	SVertexCollection vertexCollection;
	for (unsigned int i = 0; i < fbxMesh->mNumVertices; i++)
	{
		if (fbxMesh->HasPositions())
		{
			aiVector3D& mVertice = fbxMesh->mVertices[i];
			vertexCollection.PushVec4(Vector4f(mVertice.x, mVertice.y, mVertice.z, 1));

		}

		if (fbxMesh->HasBones())
		{
			VertexBoneData& boneData = collectedBoneData[i];

			aiVector3D bones;
			vertexCollection.PushVec4(Vector4f((float)boneData.IDs[0], (float)boneData.IDs[1], (float)boneData.IDs[2], (float)boneData.IDs[3]));

			aiVector3D weights;
			vertexCollection.PushVec4(Vector4f(boneData.Weights[0], boneData.Weights[1], boneData.Weights[2], boneData.Weights[3]));
		}

		if (fbxMesh->HasTextureCoords(TEXTURE_SET_0))		//HasTextureCoords(texture_coordinates_set)
		{
			vertexCollection.PushVec2(Vector2f(fbxMesh->mTextureCoords[TEXTURE_SET_0][i].x, fbxMesh->mTextureCoords[TEXTURE_SET_0][i].y));
		}

	}
	
	memcpy(aLoaderMesh->myVerticies, &vertexCollection.myData[0], vertexBufferSize * fbxMesh->mNumVertices);

	return vertexBufferSize;
}




void OnLoaded(void* someData)
{
	CLoaderModel* model = reinterpret_cast<CLoaderModel*>(someData);
	if (model)
	{
		model->myIsLoaded = true;
		if (model->myFuncToCallOnLoad)
		{
			model->myFuncToCallOnLoad(model, "");
		}
	}	
}

bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}
CMeshNode* LoadModelInternal(void* someInput)
{
	CLoaderModel* model = reinterpret_cast<CLoaderModel*>(someInput);
	const aiScene* scene = NULL;

	if (!is_file_exist(model->myModelPath.c_str()))
	{
		OutputDebugStringA("File not found");
	}
	//scene = aiImportFile(model->myModelPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);

	aiPropertyStore* store = aiCreatePropertyStore();
	scene = aiImportFileExWithProperties(model->myModelPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded, nullptr, store);
	if (!scene)
	{
		std::string error = std::string(aiGetErrorString());
		if (model->myFuncToCallOnLoad)
		{
			model->myFuncToCallOnLoad(nullptr, error);
		}
		
		if (error.find("Tokensize") == std::string::npos)
		{
			error += " :File error, Basic layout is missing, are the UV Coordinates present?";
		}
		if (model->myFuncToCallOnLoad)
		{
			model->myFuncToCallOnLoad(nullptr, error);
		}
		//assert(error);
		OutputDebugStringA(aiGetErrorString());

		return nullptr;
	}

	CMeshNode* node = nullptr;

	//else
	{

	//	model->myScene = scene;
		node = new CMeshNode();
		CModelShape* modelShapeToDX11 = new CModelShape();
		node->myModelShape = modelShapeToDX11;
		if (scene->HasMeshes())
		{
			CLoaderMesh* tempLoader = new CLoaderMesh();
			tempLoader->myModel = model;
			DetermineAndLoadVerticies(scene->mMeshes[0], tempLoader);


			for (unsigned int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
			{
				for (unsigned int j = 0; j < scene->mMeshes[0]->mFaces[i].mNumIndices; j++)
				{
					tempLoader->myIndexes.push_back(scene->mMeshes[0]->mFaces[i].mIndices[j]);
				}
			}
			node->myModelShape->Init(tempLoader);
		}
		//node->CreateHiarcy(model, scene);

		if (scene->HasAnimations())
		{

			//node->AddAnimationScene(scene);
		//	node->AddActiveAnimation(0);
			//CEngine::GetInstance()->GetScene()->AddAnimDataOnModel(scene);
		}
	}

	OutputDebugStringA(model->myModelPath.c_str());
	
	if (!scene)
	{
		std::string error = std::string(aiGetErrorString());
		if (error.find("Tokensize") == std::string::npos)
		{
			error += " :FBX 2016/2017 not supported. Export with 2014/2015 instead.";
		}
		if (model->myFuncToCallOnLoad)
		{
			model->myFuncToCallOnLoad(nullptr, error);
		}
		OutputDebugStringA(aiGetErrorString());
		return nullptr;
	}

	
	
/*
	for (unsigned int n = 0; n < scene->mNumMeshes; ++n)
	{*/
		/*CLoaderMesh* mesh = model->CreateMesh();

		aiMesh* fbxMesh = scene->mMeshes[n];

		DetermineAndLoadVerticies(fbxMesh, mesh);

		

		for (unsigned int i = 0; i < fbxMesh->mNumFaces; i++)
		{
			for (uint j = 0; j < fbxMesh->mFaces[i].mNumIndices; j++)
			{
				mesh->myIndexes.push_back(fbxMesh->mFaces[i].mIndices[j]);
			}
		}


	}

	if (scene->mNumAnimations > 0)
	{
		model->myAnimTime = (float)scene->mAnimations[0]->mDuration;
	}
	
	LoadMaterials(scene, model);


	Matrix44f NodeTransformation = ConvertToEngineMatrix44(scene->mRootNode->mTransformation);


	model->m_GlobalInverseTransform = NodeTransformation;*/
//	model->m_GlobalInverseTransform = ~model->m_GlobalInverseTransform;

	return node;

}


void LoadTexture(int aType, std::vector<STexture>& someTextures, aiMaterial* aMaterial)
{
	STexture texture;
	int texIndex = 0;
	aiReturn texFound = AI_SUCCESS;

	aiString path;	// filename

	unsigned int uvSet = 0;
	texFound = aMaterial->GetTexture((aiTextureType)aType, texIndex, &path, nullptr, &uvSet);
	if (texFound == AI_FAILURE)
	{
		texture.myPath = "";
		texture.myUVSetIndex = 0;
		someTextures.push_back(texture);
		return;
	}

	std::string filePath = std::string(path.data);

	const size_t last_slash_idx = filePath.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		filePath.erase(0, last_slash_idx + 1);
	}

	texture.myPath = filePath;
	texture.myUVSetIndex = uvSet;
	someTextures.push_back(texture);
}

void LoadMaterials(const struct aiScene* sc, CLoaderModel* aModel)
{
	if (aModel->myTextures.size() > 0)
	{
		return;
	}
	int materialCount = sc->mNumMaterials;
	if (sc->mNumMaterials > 8)
	{
		std::string errorStr = "Sorry, only 8 different materials supported";
		errorStr += ", you have: " + std::to_string(materialCount);
		//CEngine::GetInstance()->GetScene()->SetErrorString(errorStr, 0);
		materialCount = 8;
	}

	for (int i = 0; i < materialCount; i++)
	{
		aModel->myTextures.push_back(std::vector<STexture>());
	}

	for (int m = 0; m < materialCount; m++)
	{
		LoadTexture(aiTextureType_DIFFUSE, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_ALBEDO
		LoadTexture(aiTextureType_SPECULAR, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_ROUGHNESS
		LoadTexture(aiTextureType_AMBIENT, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_AMBIENTOCCLUSION
		LoadTexture(aiTextureType_EMISSIVE, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_EMISSIVE
		LoadTexture(aiTextureType_HEIGHT, aModel->myTextures[m], sc->mMaterials[m]);
		LoadTexture(aiTextureType_NORMALS, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_NORMAL
		LoadTexture(aiTextureType_SHININESS, aModel->myTextures[m], sc->mMaterials[m]);
		LoadTexture(aiTextureType_OPACITY, aModel->myTextures[m], sc->mMaterials[m]);
		LoadTexture(aiTextureType_DISPLACEMENT, aModel->myTextures[m], sc->mMaterials[m]);
		LoadTexture(aiTextureType_LIGHTMAP, aModel->myTextures[m], sc->mMaterials[m]);
		LoadTexture(aiTextureType_REFLECTION, aModel->myTextures[m], sc->mMaterials[m]); // TEXTURE_DEFINITION_METALNESS
	}
}

void DoLoad(CLoaderModel* aModel, CLoaderMesh* aMesh, aiMesh* aAIMesh, const aiScene* aScene)
{
	CLoaderMesh* mesh = aMesh;

	aiMesh* fbxMesh = aAIMesh;

	DetermineAndLoadVerticies(fbxMesh, mesh);

	for (unsigned int i = 0; i < fbxMesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < fbxMesh->mFaces[i].mNumIndices; j++)
		{
			mesh->myIndexes.push_back(fbxMesh->mFaces[i].mIndices[j]);
		}
	}


	if (aScene->mNumAnimations > 0)
	{
		aModel->myAnimTime = (float)aScene->mAnimations[0]->mDuration;
	}

	LoadMaterials(aScene, aModel);


	Matrix44 NodeTransformation = ConvertToEngineMatrix44(aScene->mRootNode->mTransformation);


	aModel->m_GlobalInverseTransform = NodeTransformation;
}




CMeshNode* CFBXLoader::LoadModel(std::string aPath, FUNCTION_ON_LOAD aFunc, unsigned int aExtraShaderType)
{

	CLoaderModel* newModel = new CLoaderModel();
	newModel->myFuncToCallOnLoad = aFunc;
	newModel->SetData(aPath.c_str());
	newModel->myModelPath = aPath;
	newModel->myTexturePath = aPath;
	newModel->myExtraShaderType = aExtraShaderType;

	return LoadModelInternal((void*)newModel);
	/*
		CEngine::GetInstance()->GetThreadPool()->CreateJob((void*)newModel, std::bind(&CFBXLoader::LoadModelInternal, this, std::placeholders::_1), std::bind(&CFBXLoader::OnLoaded, this, std::placeholders::_1));
		return newModel;*/
}

void Tga2D::CMeshNode::Render()
{
	myModelShape->Render();
}

#include "stdafx.h"
#include "FBXModel.h"
#include <tga2d/loaders/FBXLoader.h>


using namespace Tga2D;
FBXModel::FBXModel()
{
}


FBXModel::~FBXModel()
{
}

bool FBXModel::Init(const std::string& aPath)
{
	CFBXLoader loader;
	myMesh = loader.LoadModel(aPath.c_str(), nullptr);

	return false;
}

void FBXModel::Render()
{
	myMesh->Render();
}
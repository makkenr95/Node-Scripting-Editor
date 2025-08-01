#include "stdafx.h"
#include "primitives/model_shape.h"
#include "engine.h"
#include "render/Renderer.h"
#include "texture/texture_manager.h"
#include <tga2d/loaders/FBXLoader.h>
#include <tga2d/shaders/shader.h>
#include <tga2d/shaders/shader_model.h>


using namespace Tga2D;
CModelShape::CModelShape()
{

}


CModelShape::~CModelShape()
{
}

bool CModelShape::Init(CLoaderMesh* aModel)
{
	myVertexCount = aModel->myVertexCount;
	myIndexCount = static_cast<unsigned>(aModel->myIndexes.size());;
	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = aModel->myVertexBufferSize * aModel->myVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = aModel->myVertexBufferSize;
	myVertexStride = bd.StructureByteStride;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &aModel->myVerticies[0];

	hr = CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateBuffer(&bd, &InitData, &myVertexBuffer);
	if (FAILED(hr) != S_OK)
		return false;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(unsigned int) * static_cast<unsigned int>(aModel->myIndexes.size());
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &aModel->myIndexes[0];

	hr = CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateBuffer(&bd, &InitData, &myIndexBuffer);
	if (FAILED(hr) != S_OK)
		return false;


	myShader = new CShaderModel(CEngine::GetInstance());
	myShader->Init();

	return true;
}

void Tga2D::CModelShape::Render()
{
	CEngine::GetInstance()->GetDirect3D().Set3DRenderState();
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
	CEngine::GetInstance()->GetDirect3D().Set2DRenderState();
}

void CModelShape::Draw(CDirectEngine* aRenderer)
{
	UNREFERENCED_PARAMETER(aRenderer);
	myShader->Render(this, nullptr, myVertexBuffer, myIndexBuffer);
}
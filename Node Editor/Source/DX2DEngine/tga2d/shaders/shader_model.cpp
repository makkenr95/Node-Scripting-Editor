#include "stdafx.h"

#include "shaders/shader_model.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "render/render_object.h"
#include "sprite/textured_quad.h"
#include "texture/texture.h"
#include "light/light_manager.h"
#include "texture/texture_manager.h"
#include <tga2d/primitives/model_shape.h>

using namespace Tga2D;

CShaderModel::CShaderModel(CEngine* aEngine)
	:CShader(aEngine)
{
}


CShaderModel::~CShaderModel()
{
}

bool Tga2D::CShaderModel::Init()
{
	std::vector<std::string> somePathsToAnimations;
	somePathsToAnimations.push_back("ani/CH_NPC_Undead@Walk_01_17G3_AN.fbx");
	somePathsToAnimations.push_back("ani/CH_NPC_Undead@Idle_01_17G3_AN.fbx");
	myAnimation = new CAnimation();
	myAnimation->Init("ani/CH_NPC_Undead_17G3_SK.fbx", somePathsToAnimations);

	// GPU
	D3D11_BUFFER_DESC matrixVertexBufferDesc;
	matrixVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixVertexBufferDesc.ByteWidth = sizeof(Matrix44) * 64;
	matrixVertexBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixVertexBufferDesc.MiscFlags = 0;
	matrixVertexBufferDesc.StructureByteStride = 0;

	HRESULT result = S_OK;
	result = myDirect3dEngine->GetDevice()->CreateBuffer(&matrixVertexBufferDesc, NULL, &myBoneBuffer);



	return CShader::CreateShaders("shaders/model_shader_vs.fx", "shaders/model_shader_ps.fx", nullptr);
}

bool  Tga2D::CShaderModel::Init(std::string aPixelShaderFile, std::string aVertexShaderFile, std::string aPixelMainFunction, std::string aVertexMainFunction)
{
	return CShader::CreateShaders(aVertexShaderFile.c_str(), aPixelShaderFile.c_str(), nullptr, aPixelMainFunction, aVertexMainFunction);
}

void Tga2D::CShaderModel::Render(CModelShape* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer, ID3D11Buffer* aIndexBuffer)
{
	if (!myIsReadyToRender)
	{
		return;
	}

	myAnimation->Step(1.0f / 60.0f);
	//CAnimation* firstSecond = myAnimations[myBlend.mySecond];

	for (int i = 0; i < 64; i++)
	{
		myBones[i] = Matrix44();
	}

	myAnimation->BoneTransformWithBlend(myBones, 0);

	CShader::Render(aObject);

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedVResource;
	result = myDirect3dEngine->GetContext()->Map(myBoneBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVResource);
	if (FAILED(result))
	{
		//INFO_PRINT("Error in rendering!");
		return;
	}
	char* dataVPtr = (char*)mappedVResource.pData;
	memcpy(dataVPtr, &myBones[0], sizeof(Matrix44) * 64);
	myDirect3dEngine->GetContext()->Unmap(myBoneBuffer, 0);
	myDirect3dEngine->GetContext()->VSSetConstantBuffers(1, 1, &myBoneBuffer);

	myDirect3dEngine->GetContext()->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	SetShaderParameters(aObject, aObjectBuffer, aVertexBuffer);

	myDirect3dEngine->GetContext()->DrawIndexed(aObject->myIndexCount, 0, 0);

}

void CreateLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& anArray, LPCSTR aName, int aSemanticIndex, DXGI_FORMAT aFormat, int aInputSlot, D3D11_INPUT_CLASSIFICATION aClassification, int aInstanceStep)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout;
	polygonLayout.SemanticName = aName;
	polygonLayout.SemanticIndex = aSemanticIndex;
	polygonLayout.Format = aFormat;
	polygonLayout.InputSlot = aInputSlot;
	polygonLayout.AlignedByteOffset = anArray.size() > 0 ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
	polygonLayout.InputSlotClass = aClassification;
	polygonLayout.InstanceDataStepRate = aInstanceStep;
	anArray.push_back(polygonLayout);
}

bool Tga2D::CShaderModel::CreateInputLayout(ID3D10Blob* aVS)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;

	CreateLayout(layout, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	//CreateLayout(layout, "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	//CreateLayout(layout, "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	//CreateLayout(layout, "BINORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	CreateLayout(layout, "BONES", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	CreateLayout(layout, "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	CreateLayout(layout, "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);


	unsigned int numElements = (unsigned int)layout.size();
	HRESULT result = myDirect3dEngine->GetDevice()->CreateInputLayout(&layout[0], numElements, aVS->GetBufferPointer(), aVS->GetBufferSize(), &myLayout);
	if (FAILED(result))
	{
		ERROR_PRINT("%s", "Layout error");
	}
	return true;
}

void CShaderModel::SetShaderParameters(CModelShape* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer)
{
	const unsigned int strides = aObject->myVertexStride;
	const unsigned int offsets = 0;
	myDirect3dEngine->GetContext()->IASetVertexBuffers(0, 1, &aVertexBuffer, &strides, &offsets);
	myDirect3dEngine->GetContext()->VSSetConstantBuffers(EConstantBufferSlot_Object, 1, &aObjectBuffer);
}

void CShaderModel::UpdateVertexes(CTexturedQuad* aQuad, ID3D11Buffer* aVertexBuffer)
{
	UNREFERENCED_PARAMETER(aQuad);
	UNREFERENCED_PARAMETER(aVertexBuffer);
	/*
	D3D11_MAPPED_SUBRESOURCE mappedVertexResource;
	SVertex* dataVertexPtr;
	HRESULT result = myDirect3dEngine->GetContext()->Map(aVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertexResource);
	if (FAILED(result))
	{
		INFO_PRINT("Error in rendering!");
		return;
	}
	dataVertexPtr = (SVertex*)mappedVertexResource.pData;

	const STextureRext& textureRect = aQuad->GetTextureRect();

	const float startSize = 1.0f;

	float theZ = 0.0f;
	dataVertexPtr[0].X = 0;
	dataVertexPtr[0].Y = -startSize;
	dataVertexPtr[0].Z = theZ;
	dataVertexPtr[0].texX = textureRect.myStartX;
	dataVertexPtr[0].texY = textureRect.myEndY;

	dataVertexPtr[1].X = 0;
	dataVertexPtr[1].Y = 0;
	dataVertexPtr[1].Z = theZ;
	dataVertexPtr[1].texX = textureRect.myStartX;
	dataVertexPtr[1].texY = textureRect.myStartY;

	dataVertexPtr[2].X = startSize;
	dataVertexPtr[2].Y = -startSize;
	dataVertexPtr[2].Z = theZ;
	dataVertexPtr[2].texX = textureRect.myEndX;
	dataVertexPtr[2].texY = textureRect.myEndY;

	dataVertexPtr[3].X = startSize;
	dataVertexPtr[3].Y = 0;
	dataVertexPtr[3].Z = theZ;
	dataVertexPtr[3].texX = textureRect.myEndX;
	dataVertexPtr[3].texY = textureRect.myStartY;

	dataVertexPtr[4].X = startSize;
	dataVertexPtr[4].Y = -startSize;
	dataVertexPtr[4].Z = theZ;
	dataVertexPtr[4].texX = textureRect.myEndX;
	dataVertexPtr[4].texY = textureRect.myEndY;

	dataVertexPtr[5].X = 0;
	dataVertexPtr[5].Y = 0;
	dataVertexPtr[5].Z = theZ;
	dataVertexPtr[5].texX = textureRect.myStartX;
	dataVertexPtr[5].texY = textureRect.myStartY;

	myDirect3dEngine->GetContext()->Unmap(aVertexBuffer, 0); */
}
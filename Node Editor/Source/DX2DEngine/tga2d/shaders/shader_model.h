#pragma once

#include "shader.h"
#include "shader_common.h"
#include <tga2d/animation/CAnimation.h>

namespace Tga2D
{
	class CRenderObjectSprite;
	class CTexturedQuad;
	class CShaderModel : public CShader
	{
	public:
		CShaderModel(CEngine* aEngine);
		~CShaderModel();

		bool Init() override;
		bool Init(std::string aPixelShaderFile, std::string aVertexShaderFile, std::string aPixelMainFunction, std::string aVertexMainFunction);
		void Render(CModelShape* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer, ID3D11Buffer* aIndexBuffer);
		bool CreateInputLayout(ID3D10Blob* aVS) override;
	private:
		void SetShaderParameters(CModelShape* aObject, ID3D11Buffer* aObjectBuffer, ID3D11Buffer* aVertexBuffer);
		void UpdateVertexes(CTexturedQuad* aQuad, ID3D11Buffer* aVertexBuffer);

		CAnimation* myAnimation;
		Matrix44 myBones[64];
		struct ID3D11Buffer* myBoneBuffer;
	};

}
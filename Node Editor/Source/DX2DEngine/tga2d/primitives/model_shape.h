#pragma once
#include "tga2d/render/render_object.h"
#include <tga2d/engine_defines.h>
namespace Tga2D
{

	class CModelShape : public CRenderObject
	{
	public:
		CModelShape();
		~CModelShape();

		bool Init(class CLoaderMesh* aModel);
		void Render();

		void Draw(CDirectEngine* aRenderer) override;

		struct ID3D11Buffer* myVertexBuffer;
		struct ID3D11Buffer* myIndexBuffer;

		unsigned int myVertexCount;
		unsigned int myIndexCount;
		unsigned int myVertexStride;
		Matrix44 myBones[64];

		class CShaderModel* myShader = nullptr;
		
	};
}
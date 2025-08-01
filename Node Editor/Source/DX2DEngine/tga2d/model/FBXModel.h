#pragma once

namespace Tga2D
{
	class FBXModel
	{
	public:
		FBXModel();
		~FBXModel();
		bool Init(const std::string& aPath);
		void Render();
	private:
		class CMeshNode* myMesh;
	};

}
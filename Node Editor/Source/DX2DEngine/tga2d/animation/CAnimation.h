#pragma once
#include <vector>
#include <string>

namespace Tga2D
{

	class CAnimation
	{
	public:
		void Init(const char* aRig, std::vector<std::string>& somePathsToAnimations);


		// ANIMATION STUFF
		void BoneTransform(Matrix44* Transforms);
		void BoneTransformWithBlend(Matrix44* Transforms, float aBlendFactor);
		void Step(float aDelta);

		class SceneAnimator* myAnimator;
		class SceneAnimator* myBindPose = nullptr;
		std::vector<int> myActiveAnimations;
		float myTotalAnimationTime = 0;
		float myAnimTime = 0;
		int myAnimSpeed = 60;

		class AnimationController* controller;
	};
}


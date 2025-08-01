#include "stdafx.h"
#include "CAnimation.h"
#include <tga2d/animation/AnimationController.h>

using namespace Tga2D;
void CAnimation::Init(const char* aRig, std::vector<std::string>& somePathsToAnimations)
{
	controller = new AnimationController(aRig);
	controller->Import3DFromFile(aRig);
	for (std::string s : somePathsToAnimations)
	{
		controller->Add3DAnimFromFile(s);
	}
	
	controller->SetAnimIndex(1, true, 0.0f);
	controller->SetAnimIndex(2, true, 5.0f);
}

void CAnimation::BoneTransformWithBlend(Matrix44* Transforms, float aBlendFactor)
{
	std::vector<aiMatrix4x4> trans;
	controller->BoneTransform(trans);
	controller->SetBlendTime(aBlendFactor);

	memcpy(&Transforms[0], &trans[0], (sizeof(float) * 16) * trans.size());
}

void CAnimation::Step(float aDelta)
{
	if (controller->IsDoneBlending())
	{
	//	controller->SetAnimIndex(2, true, 5);
	}

	myTotalAnimationTime += aDelta;
	controller->Update();
}
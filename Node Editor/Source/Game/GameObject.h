#pragma once
#include <memory>
#include "../CommonUtilities/Vector.hpp"

namespace Tga2D
{
	class CSprite;
}

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float aDeltaTime);
	void Render();

	void SetID(int aID);
	int GetID();

	void SetPosition(Tga2D::Vector2<float> aPosition);
	Tga2D::Vector2<float>& GetPosition();

	void SetSprite(const char* aSprite);
	Tga2D::CSprite* GetSprite();

	void SetScale(Tga2D::Vector2f aScale);
	const Tga2D::Vector2f& GetScale() const;

	void AddCollider();
	void SetColliderActive(bool aBool);
	bool HasCollider();
	
	void OnTriggerEnter();
	void OnTriggerExit();

private:
	int myID = 0;
	Tga2D::Vector2f myScale = { 1.f, 1.f };
	Tga2D::Vector2<float> myPosition = { 2,2 };
	std::unique_ptr<Tga2D::CSprite> mySprite = nullptr;
	bool myColliderInited = false;
	bool myHasCollider = false;
};


#pragma once
#include "GameObject.h"
class Collider
{
public:
	Collider(Tga2D::Vector2f aSize, GameObject* aGo);
	void Update();

	const Tga2D::Vector2f& GetSize();
	void SetSize(Tga2D::Vector2f aSize);
	const Tga2D::Vector2f& GetPosition();
	void SetPosition(Tga2D::Vector2f aPosition);
	bool IsInsideAABB2D(GameObject* aGo);
	int GetGameObjectID();

private:
	Tga2D::Vector2f mySize = { 0.f, 0.f };
	Tga2D::Vector2f myPosition = { 0.f, 0.f };
	GameObject* myGameObject = nullptr;
};


#include "stdafx.h"
#include "Collider.h"

Collider::Collider(Tga2D::Vector2f aSize, GameObject* aGo)
{
	mySize = aSize;
	myPosition = aGo->GetPosition();
	myGameObject = aGo;
}

void Collider::Update()
{
	myPosition = myGameObject->GetPosition();
}

const Tga2D::Vector2f& Collider::GetSize()
{
	return mySize;
}

void Collider::SetSize(Tga2D::Vector2f aSize)
{
	mySize = aSize;
}
const Tga2D::Vector2f& Collider::GetPosition()
{
	return myPosition;
}

void Collider::SetPosition(Tga2D::Vector2f aPosition)
{
	myPosition = aPosition;
}

bool Collider::IsInsideAABB2D(GameObject* aGo)
{
	if (aGo->GetPosition().x < myPosition.x + mySize.x &&
		aGo->GetPosition().x > myPosition.x - mySize.x &&
		aGo->GetPosition().y < myPosition.y + mySize.y &&
		aGo->GetPosition().y > myPosition.y - mySize.y)
	{
		return true;
	}
	return false;
}

int Collider::GetGameObjectID()
{
	return myGameObject->GetID();
}


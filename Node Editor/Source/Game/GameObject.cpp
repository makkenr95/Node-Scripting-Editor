#include "stdafx.h"
#include "GameObject.h"
#include "CollisionManager.h"

#include "tga2d/sprite/sprite.h"
#include "Collider.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float aDeltaTime)
{
	if (mySprite != nullptr)
	{
		mySprite->SetPosition(myPosition);
		if (!myColliderInited)
		{
			auto coll = CollisionManager::GetInstance().GetColliderByID(myID);
			coll->SetSize(mySprite->GetSize() / 1024.f);
			myColliderInited = true;
		}
	}
}

void GameObject::Render()
{
	if (mySprite != nullptr)
	{
		mySprite.get()->Render();
	}
}

void GameObject::SetID(int aID)
{
	myID = aID;
}

int GameObject::GetID()
{
	return myID;
}

void GameObject::SetPosition(Tga2D::Vector2<float> aPosition)
{
	myPosition = aPosition;
}

Tga2D::Vector2<float>& GameObject::GetPosition()
{
	return myPosition;
}

void GameObject::SetSprite(const char* aSprite)
{
	mySprite = std::make_unique<Tga2D::CSprite>(aSprite);
	mySprite->SetPivot({ 0.5f, 0.5f });
}

Tga2D::CSprite* GameObject::GetSprite()
{
	return mySprite.get();
}

void GameObject::SetScale(Tga2D::Vector2f aScale)
{
	if (mySprite != nullptr)
	{
		myScale = aScale;
		mySprite->SetSizeRelativeToScreen(aScale);
	}
}

const Tga2D::Vector2f& GameObject::GetScale() const
{
	return myScale;
}

void GameObject::AddCollider()
{
	Collider* coll = new Collider({ 0.f,0.f }, this);
	CollisionManager::GetInstance().AddCollider(coll);
	myHasCollider = true;
}
void GameObject::SetColliderActive(bool aBool)
{

	myHasCollider = aBool;
}

bool GameObject::HasCollider()
{
	return myHasCollider;
}

void GameObject::OnTriggerEnter()
{
}

void GameObject::OnTriggerExit()
{
}



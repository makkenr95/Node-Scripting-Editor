#include "stdafx.h"
#include "GameObjectManager.h"
#include "GraphManager.h"

#include "GameObject.h"

void GameObjectManager::Update(float aDeltaTime)
{
	for (int i = 0; i < myGameObjects.size(); i++ )
	{
		myGameObjects[i]->Update(aDeltaTime);
	}
}

void GameObjectManager::Render()
{
	for (int i = 0; i < myGameObjects.size(); i++ )
	{
		myGameObjects[i]->Render();
	}
}

void GameObjectManager::SetGraphmanager(GraphManager* aGM)
{
	myGraphManager = aGM;
}

GraphManager* GameObjectManager::GetGraphManager()
{
	return myGraphManager;
}

GameObjectManager& GameObjectManager::GetInstance()
{
	  static GameObjectManager gameObjectManager;

    return gameObjectManager;
}
GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}


GameObject* GameObjectManager::AddGameObject(Tga2D::Vector2<float> aPosition)
{
	GameObject* newGameObject= new GameObject();
	newGameObject->SetPosition(aPosition);
	newGameObject->SetID(myIDCount);
	newGameObject->AddCollider();
	myIDCount++;
	myGameObjects.push_back(newGameObject);
	return newGameObject;
}

GameObject* GameObjectManager::GetGameObject(int aID)
{
	for (int i = 0; i < myGameObjects.size(); i++)
	{
		if (aID == myGameObjects[i]->GetID())
		{
			return myGameObjects[i];
		}
	}
	ERROR_PRINT("GameObject ID do not exists");
}

std::vector<GameObject*> GameObjectManager::GetGameObjects()
{
	return myGameObjects;
}

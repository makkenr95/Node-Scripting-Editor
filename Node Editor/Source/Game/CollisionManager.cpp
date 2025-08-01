#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "GraphManager.h"

#include "GameObject.h"
#include "Collider.h"
#include "GameWorld.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Update(float aDeltaTime)
{
	auto gos = GameObjectManager::GetInstance().GetGameObjects();
	for (auto& coll : myColliders)
	{
		// UPDATE COLLIDER
		coll->Update();

		for (auto& go : gos)
		{
			if (coll->GetGameObjectID() != go->GetID())
			{
				auto collisionPair = std::make_pair(coll->GetGameObjectID(), go->GetID());

				//If collisionpair does not exist in set
				if (myCollidedPairs.find(collisionPair) == myCollidedPairs.end())
				{
					if (coll->IsInsideAABB2D(go) && GameObjectManager::GetInstance().GetGameObject(coll->GetGameObjectID())->HasCollider())
					{
						Payload payload;

						auto id1 = coll->GetGameObjectID();
						auto id2 = go->GetID();

						payload.AddData(id1);
						payload.AddData(id2);

						myCollidedPairs.insert(collisionPair);
						GameObjectManager::GetInstance().GetGraphManager()->ExecuteTreeWithPayload("OnTriggerEnter", payload);
					}
				}
				if (myCollidedPairs.find(collisionPair) != myCollidedPairs.end())
				{
					if (!coll->IsInsideAABB2D(go) && GameObjectManager::GetInstance().GetGameObject(coll->GetGameObjectID())->HasCollider())
					{
						Payload payload;

						auto id1 = coll->GetGameObjectID();
						auto id2 = go->GetID();

						payload.AddData(id1);
						payload.AddData(id2);

						myCollidedPairs.erase(collisionPair);
						GameObjectManager::GetInstance().GetGraphManager()->ExecuteTreeWithPayload("OnTriggerExit", payload);
					}
				}
			}
		}
	}
}

CollisionManager& CollisionManager::GetInstance()
{
	static CollisionManager collisionManager;

	return collisionManager;
}

void CollisionManager::AddCollider(Collider* aCollider)
{
	myColliders.push_back(aCollider);
}

Collider* CollisionManager::GetColliderByID(int aID)
{
	for (auto coll : myColliders)
	{
		if (coll->GetGameObjectID() == aID)
		{
			return coll;
		}
	}
	return nullptr;
}

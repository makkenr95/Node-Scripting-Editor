#pragma once
#include <map>
#include <set>
class Collider;

class CollisionManager
{
public:
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;

	void Update(float aDeltaTime);
	void AddCollider(Collider* aCollider);

	Collider* GetColliderByID(int aID);

	static CollisionManager& GetInstance();

private:
	CollisionManager();
	~CollisionManager();

	std::set<std::pair<int, int>> myCollidedPairs;
	std::vector<Collider*> myColliders;
};


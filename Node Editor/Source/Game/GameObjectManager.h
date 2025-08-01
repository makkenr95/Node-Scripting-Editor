#pragma once
class GameObject;
class GraphManager;

class GameObjectManager
{
public:
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;

	void Update(float aDeltaTime);
	void Render();

	void SetGraphmanager(GraphManager* aGM);
	GraphManager* GetGraphManager();

	static GameObjectManager& GetInstance();

	GameObject* AddGameObject(Tga2D::Vector2<float> aPosition);

	GameObject* GetGameObject(int aID);
	std::vector<GameObject*> GetGameObjects();
private:
		GameObjectManager();
	~GameObjectManager();

	GraphManager* myGraphManager = nullptr;

	std::vector<GameObject*> myGameObjects;
	int myIDCount = 0;
};


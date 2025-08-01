#include "stdafx.h"
#include "Graphnode_SetGameObjectSprite.h"


#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_SetGameObjectSprite::Graphnode_SetGameObjectSprite()
{
	CreatePin("Exec", PinDirection::PinDirection_IN);
	CreatePin("ID", PinDirection::PinDirection_IN, DataType::Int);
	CreatePin("SpritePath", PinDirection::PinDirection_IN, DataType::String);
	CreatePin("Out", PinDirection::PinDirection_OUT);
}

int Graphnode_SetGameObjectSprite::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const int id = GetPinData<int>(aNodeInstance, 1);
	const std::string spritePath = GetPinData<std::string>(aNodeInstance, 2);

	auto gameObject = GameObjectManager::GetInstance().GetGameObject(id);
	if (gameObject == nullptr)
	{
		return 3;
	}
	gameObject->SetSprite(spritePath.c_str());
	
	return 3; // If the node doesn't have a flow, return -1 see the print node for reference
}


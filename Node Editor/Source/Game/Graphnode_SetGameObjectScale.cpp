#include "stdafx.h"
#include "Graphnode_SetGameObjectScale.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_SetGameObjectScale::Graphnode_SetGameObjectScale()
{
	CreatePin("Exec", PinDirection::PinDirection_IN);
	CreatePin("ID", PinDirection::PinDirection_IN, DataType::Int);
	CreatePin("X", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Y", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Out", PinDirection::PinDirection_OUT);
}

int Graphnode_SetGameObjectScale::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const int id = GetPinData<int>(aNodeInstance, 1);
	const float x = GetPinData<float>(aNodeInstance, 2);
	const float y = GetPinData<float>(aNodeInstance, 3);

	auto gameObject = GameObjectManager::GetInstance().GetGameObject(id);
	if (gameObject == nullptr)
	{
		return 4;
	}
	gameObject->SetScale({x, y});

	return 4; // If the node doesn't have a flow, return -1 see the print node for reference
}


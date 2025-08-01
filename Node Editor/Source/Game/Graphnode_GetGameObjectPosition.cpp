#include "stdafx.h"
#include "Graphnode_GetGameObjectPosition.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_GetGameObjectPosition::Graphnode_GetGameObjectPosition()
{
	CreatePin("ID", PinDirection::PinDirection_IN, DataType::Int);
	CreatePin("X", PinDirection::PinDirection_OUT, DataType::Float);
	CreatePin("Y", PinDirection::PinDirection_OUT, DataType::Float);
}

int Graphnode_GetGameObjectPosition::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const int input = GetPinData<int>(aNodeInstance, 0);

	auto gameObject = GameObjectManager::GetInstance().GetGameObject(input);
	if (gameObject == nullptr)
	{
		return -1;
	}
	Tga2D::Vector2<float> pos = gameObject->GetPosition();
	
	const float result1 = pos.x;
	const float result2 = pos.y;

	SetPinData(aNodeInstance, 1, result1);
	SetPinData(aNodeInstance, 2, result2);

	return -1; // If the node doesn't have a flow, return -1 see the print node for reference
}


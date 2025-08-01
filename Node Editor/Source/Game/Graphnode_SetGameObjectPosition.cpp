#include "stdafx.h"
#include "Graphnode_SetGameObjectPosition.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_SetGameObjectPosition::Graphnode_SetGameObjectPosition()
{
	CreatePin("Exec", PinDirection::PinDirection_IN);
	CreatePin("ID", PinDirection::PinDirection_IN, DataType::Int);
	CreatePin("X", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Y", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Out", PinDirection::PinDirection_OUT);
}	

int Graphnode_SetGameObjectPosition::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const int input = GetPinData<int>(aNodeInstance, 1);
	const float input2 = GetPinData<float>(aNodeInstance, 2);
	const float input3 = GetPinData<float>(aNodeInstance, 3);

	auto gameObject = GameObjectManager::GetInstance().GetGameObject(input);
	if (gameObject == nullptr)
	{
		return 4;
	}
	Tga2D::Vector2<float> pos = {input2, input3};
	gameObject->SetPosition(pos);

	return 4; // If the node doesn't have a flow, return -1 see the print node for reference
}


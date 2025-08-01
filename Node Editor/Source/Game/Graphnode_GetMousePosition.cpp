#include "stdafx.h"
#include "Graphnode_GetMousePosition.h"

#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_GetMousePosition::Graphnode_GetMousePosition()
{
	CreatePin("X", PinDirection::PinDirection_OUT, DataType::Float);
	CreatePin("Y", PinDirection::PinDirection_OUT, DataType::Float);
}

int Graphnode_GetMousePosition::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const float x = ImGui::GetMousePos().x / 1920.f;
	const float y = ImGui::GetMousePos().y / 1080.f;
	SetPinData(aNodeInstance, 0, x);

	SetPinData(aNodeInstance, 1, y);

	return -1; // If the node doesn't have a flow, return -1 see the print node for reference
}


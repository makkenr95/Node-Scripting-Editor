#include "stdafx.h"
#include "Graphnode_GetDistance.h"
#include "GraphNodeInstance.h"

Graphnode_GetDistance::Graphnode_GetDistance()
{
	CreatePin("X_1", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Y_1", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("X_2", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Y_2", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Distance", PinDirection::PinDirection_OUT, DataType::Float);
}

int Graphnode_GetDistance::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const float x_1 = GetPinData<float>(aNodeInstance, 0);
	const float y_1 = GetPinData<float>(aNodeInstance, 1);
	const float x_2 = GetPinData<float>(aNodeInstance, 2);
	const float y_2 = GetPinData<float>(aNodeInstance, 3);

	const float distanceX = x_2 - x_1;  
	const float distanceY = y_2 - y_1;  
	const float distance = std::sqrtf(distanceX * distanceX + distanceY * distanceY);  

	SetPinData(aNodeInstance, 4, distance);

	return -1; // If the node doesn't have a flow, return -1 see the print node for reference
}


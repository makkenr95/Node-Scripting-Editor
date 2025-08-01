#include "stdafx.h"
#include "Graphnode_Min.h"
#include "GraphNodeInstance.h"

Graphnode_Min::Graphnode_Min()
{
	CreatePin("Input", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Min", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Result", PinDirection::PinDirection_OUT, DataType::Float);
}

int Graphnode_Min::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const float input = GetPinData<float>(aNodeInstance, 0);
	const float min = GetPinData<float>(aNodeInstance, 1);

	float result = input;
	if (input <= min)
	{
		result = min;
	}

	SetPinData(aNodeInstance, 2, result);	

	return -1; // If the node doesn't have a flow, return -1 see the print node for reference
}


#include "stdafx.h"
#include "Graphnode_Max.h"
#include "GraphNodeInstance.h"

Graphnode_Max::Graphnode_Max()
{
	CreatePin("Input", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Max", PinDirection::PinDirection_IN, DataType::Float);
	CreatePin("Result", PinDirection::PinDirection_OUT, DataType::Float);
}

int Graphnode_Max::OnExec(class GraphNodeInstance* aNodeInstance)
{
	const float input = GetPinData<float>(aNodeInstance, 0);
	const float max = GetPinData<float>(aNodeInstance, 1);

	float result = input;
	if (input >= max)
	{
		result = max;
	}

	SetPinData(aNodeInstance, 2, result);	

	return -1; // If the node doesn't have a flow, return -1 see the print node for reference
}


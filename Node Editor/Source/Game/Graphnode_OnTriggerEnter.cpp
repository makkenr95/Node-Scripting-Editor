#include "stdafx.h"
#include "Graphnode_OnTriggerEnter.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphNodeInstance.h"

Graphnode_OnTriggerEnter::Graphnode_OnTriggerEnter()
{
	CreatePin("Out", PinDirection::PinDirection_OUT);
	CreatePin("Source ID", PinDirection::PinDirection_OUT, DataType::Int);
	CreatePin("Target ID", PinDirection::PinDirection_OUT, DataType::Int);
}

int Graphnode_OnTriggerEnter::OnExecWithPayload(GraphNodeInstance* aNodeInstance, Payload& aPayload)
{
	int sourceID = aPayload.GetEntry<int>(0);
	int targetID = aPayload.GetEntry<int>(1);
	
	SetPinData(aNodeInstance, 1, sourceID);
	SetPinData(aNodeInstance, 2, targetID);

	return 0;
}


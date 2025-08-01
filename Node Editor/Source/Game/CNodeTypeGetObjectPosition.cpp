#include "stdafx.h"
#include "CNodeTypeGetObjectPosition.h"

#include "CNodeInstance.h"
#include <iostream>
#include "CGameObjectManager.h"
#include <tga2d/sprite/sprite.h>

CNodeTypeGetObjectPosition::CNodeTypeGetObjectPosition()
{
	myPins.push_back(CPin("ID", CPin::PinTypeInOut::PinTypeInOut_IN, CPin::PinType::Int));
	myPins.push_back(CPin("X", CPin::PinTypeInOut::PinTypeInOut_OUT, CPin::PinType::Float));
	myPins.push_back(CPin("Y", CPin::PinTypeInOut::PinTypeInOut_OUT, CPin::PinType::Float));
}

int CNodeTypeGetObjectPosition::OnEnter(class CNodeInstance* aTriggeringNodeInstance)
{
	CPin::PinType outType;
	NodeDataPtr someData = nullptr;
	size_t outSize = 0;


	GetDataOnPin(aTriggeringNodeInstance, 0, outType, someData, outSize);
	int objectID = NodeData::Get<int>(someData);

	Tga2D::Vector2f pos;
	CGameObject* go = CGameObjectManager::Get()->GetGameObject(objectID);
	if (go)
	{
		if (go->mySprite)
		{
			pos = go->mySprite->GetPosition();
		}
	}

	std::vector<CPin>& pins = aTriggeringNodeInstance->GetPins();
	DeclareDataOnPinIfNecessary<float>(pins[1]);
	memcpy(pins[1].myData, &pos.x, sizeof(float));

	DeclareDataOnPinIfNecessary<float>(pins[2]);
	memcpy(pins[2].myData, &pos.y, sizeof(float));

	return -1;
}

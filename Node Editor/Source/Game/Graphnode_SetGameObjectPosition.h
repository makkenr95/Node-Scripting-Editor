#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"

class Graphnode_SetGameObjectPosition : public GraphNodeBase
{
public:
	Graphnode_SetGameObjectPosition();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "SetGameObjectPosition"; }
	virtual std::string GetNodeTypeCategory() const override { return "GameObject"; }
};




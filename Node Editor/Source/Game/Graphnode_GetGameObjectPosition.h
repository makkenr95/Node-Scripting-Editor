#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"


class Graphnode_GetGameObjectPosition : public GraphNodeBase
{
public:
	Graphnode_GetGameObjectPosition();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "GetGameObjectPosition"; }
	virtual std::string GetNodeTypeCategory() const override { return "GameObject"; }
};




#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"

class Graphnode_SetGameObjectScale : public GraphNodeBase
{
public:
	Graphnode_SetGameObjectScale();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "SetGameObjectScale"; }
	virtual std::string GetNodeTypeCategory() const override { return "GameObject"; }
};




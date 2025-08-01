#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"


class Graphnode_GetMousePosition : public GraphNodeBase
{
public:
	Graphnode_GetMousePosition();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "GetMousePosition"; }
	virtual std::string GetNodeTypeCategory() const override { return "Mouse"; }
};




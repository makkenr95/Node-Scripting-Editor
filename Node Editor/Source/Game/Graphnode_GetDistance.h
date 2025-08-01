#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"


class Graphnode_GetDistance : public GraphNodeBase
{
public:
	Graphnode_GetDistance();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "GetDistance"; }
	virtual std::string GetNodeTypeCategory() const override { return "Math"; }
};




#pragma once
#include "GraphNodeBase.h"

class Graphnode_Branch :
	public GraphNodeBase
{
public:
	Graphnode_Branch();

	int OnExec(GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "Branch"; }
	virtual std::string GetNodeTypeCategory() const override { return "BaseType"; }
};


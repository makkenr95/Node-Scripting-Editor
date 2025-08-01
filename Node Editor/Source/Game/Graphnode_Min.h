#pragma once
#include "GraphNodeBase.h"

class Graphnode_Min : public GraphNodeBase
{
public:
	Graphnode_Min();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "Min"; }
	virtual std::string GetNodeTypeCategory() const override { return "Math"; }
};


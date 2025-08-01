#pragma once
#include "GraphNodeBase.h"

class Graphnode_Max : public GraphNodeBase
{
public:
	Graphnode_Max();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "Max"; }
	virtual std::string GetNodeTypeCategory() const override { return "Math"; }
};


#pragma once
#include "GraphNodeBase.h"
class Graphnode_Timer :
    public GraphNodeBase
{
public:
	Graphnode_Timer();

	int OnExec(GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "Timer"; }
	virtual std::string GetNodeTypeCategory() const override { return "BaseType"; }
	void OnTimerElapsed(class GraphNodeInstance* aNodeInstance);
};


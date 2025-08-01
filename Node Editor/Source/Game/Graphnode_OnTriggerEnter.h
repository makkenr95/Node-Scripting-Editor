#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"

class Graphnode_OnTriggerEnter : public GraphNodeBase
{
public:
	Graphnode_OnTriggerEnter();

	int OnExecWithPayload(GraphNodeInstance* aNodeInstance, Payload& aPayload) override;

	virtual bool IsStartNode() const override { return true; }
	virtual std::string GetNodeName() const override { return "OnTriggerEnter"; }
	virtual std::string GetNodeTypeCategory() const override { return "Collision"; }
private:

};




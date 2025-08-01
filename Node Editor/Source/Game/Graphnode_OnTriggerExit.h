#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"

class Graphnode_OnTriggerExit : public GraphNodeBase
{
public:
	Graphnode_OnTriggerExit();

	int OnExecWithPayload(GraphNodeInstance* aNodeInstance, Payload& aPayload) override;

	virtual bool IsStartNode() const override { return true; }
	virtual std::string GetNodeName() const override { return "OnTriggerExit"; }
	virtual std::string GetNodeTypeCategory() const override { return "Collision"; }
private:

};




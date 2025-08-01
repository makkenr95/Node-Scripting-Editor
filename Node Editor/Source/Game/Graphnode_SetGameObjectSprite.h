#pragma once
#include "GraphNodeBase.h"
#include "NodeTypes.h"


class Graphnode_SetGameObjectSprite : public GraphNodeBase
{
public:
	Graphnode_SetGameObjectSprite();

	int OnExec(class GraphNodeInstance* aNodeInstance) override;

	virtual std::string GetNodeName() const override { return "SetGameObjectSprite"; }
	virtual std::string GetNodeTypeCategory() const override { return "GameObject"; }
};




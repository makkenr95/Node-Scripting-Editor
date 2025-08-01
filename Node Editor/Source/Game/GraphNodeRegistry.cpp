#include "stdafx.h"
#include "GraphNodeRegistry.h"

#include "Graphnode_SetGameObjectPosition.h"
#include "Graphnode_GetDistance.h"
#include "Graphnode_GetGameObjectPosition.h"
#include "Graphnode_GetMousePosition.h"
#include "Graphnode_SetGameObjectSprite.h"
#include "Graphnode_OnTriggerEnter.h"
#include "Graphnode_OnTriggerExit.h"
#include "GraphNode_MathAdd.h"
#include "GraphNode_MathMul.h"
#include "GraphNode_MathSub.h"
#include "Graphnode_Timer.h"
#include "Graphnode_Max.h"
#include "Graphnode_Min.h"
#include "GraphNode_Print.h"
#include "Graphnode_SetGameObjectScale.h"
#include "GraphNode_Start.h"
#include "Graphnode_Branch.h"

void GraphNodeRegistry::PopulateTypes()
{
	RegisterType<GraphNode_Print>();
	RegisterType<GraphNode_Start>();
	RegisterType<GraphNode_MathAdd>();
	RegisterType<GraphNode_MathMul>();
	RegisterType<GraphNode_MathSub>();
	RegisterType<Graphnode_Timer>();
	RegisterType<Graphnode_OnTriggerEnter>();
	RegisterType<Graphnode_OnTriggerExit>();
	RegisterType<Graphnode_GetGameObjectPosition>();
	RegisterType<Graphnode_SetGameObjectPosition>();
	RegisterType<Graphnode_SetGameObjectSprite>();
	RegisterType<Graphnode_GetMousePosition>();
	RegisterType<Graphnode_GetDistance>();
	RegisterType<Graphnode_SetGameObjectScale>();
	RegisterType<Graphnode_Max>();
	RegisterType<Graphnode_Min>();
	RegisterType<Graphnode_Branch>();
}

GraphNodeBase* GraphNodeRegistry::myTypes[128];
unsigned short GraphNodeRegistry::myTypeCounter = 0;
#pragma once

class GraphNodeBase;

class GraphNodeRegistry
{
public:
	static void PopulateTypes();
	static GraphNodeBase* GetNodeTypeFromID(unsigned int aClassID)
	{
		return myTypes[aClassID]; // 1:1 to nodetype enum
	}
	static GraphNodeBase** GetAllNodeTypes()
	{
		return myTypes; // 1:1 to nodetype enum
	}
	static unsigned short GetNodeTypeCount()
	{
		return 	myTypeCounter; // 1:1 to nodetype enum
	}
	template <class T>
	static void RegisterType()
	{
		myTypes[myTypeCounter] = new T;
		myTypes[myTypeCounter]->myID = myTypeCounter;
		myTypeCounter++;
	}
	static GraphNodeBase* myTypes[128];
	static unsigned short myTypeCounter;
};

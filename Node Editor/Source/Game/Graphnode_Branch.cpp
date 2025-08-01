#include "stdafx.h"
#include "Graphnode_Branch.h"
#include "TimerManager.h"
#include "GraphNodeInstance.h"

Graphnode_Branch::Graphnode_Branch()
{
    CreatePin("Exec", PinDirection::PinDirection_IN);
    CreatePin("Condition", PinDirection::PinDirection_IN, DataType::Bool);
    CreatePin("True", PinDirection::PinDirection_OUT);
    CreatePin("False", PinDirection::PinDirection_OUT);
}

int Graphnode_Branch::OnExec(GraphNodeInstance* aNodeInstance)
{
    const bool condition = GetPinData<bool>(aNodeInstance, 1);

    if (condition)
    {
        return 2;
    }
    else
    {
        return 3;
    }

    return -1;
}

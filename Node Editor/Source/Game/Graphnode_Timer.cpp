#include "stdafx.h"
#include "Graphnode_Timer.h"
#include "TimerManager.h"
#include "GraphNodeInstance.h"
Graphnode_Timer::Graphnode_Timer()
{
    CreatePin("Exec", PinDirection::PinDirection_IN);
    CreatePin("Out", PinDirection::PinDirection_OUT);
    CreatePin("Duration", PinDirection::PinDirection_IN, DataType::Float);
    CreatePin("Loop", PinDirection::PinDirection_IN, DataType::Bool);
    CreatePin("On Timer", PinDirection::PinDirection_OUT);
}

int Graphnode_Timer::OnExec(GraphNodeInstance* aNodeInstance)
{
    const float timerDuration = GetPinData<float>(aNodeInstance, 2);
    const bool shouldLoop = GetPinData<bool>(aNodeInstance, 3);

    TimerManager::AddTimer([this, aNodeInstance] { OnTimerElapsed(aNodeInstance); }, timerDuration, shouldLoop);

    return 1;
}

void Graphnode_Timer::OnTimerElapsed(GraphNodeInstance* aNodeInstance)
{
    aNodeInstance->ExitVia(4);
}

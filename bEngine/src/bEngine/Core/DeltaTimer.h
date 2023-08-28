#pragma once
#include "Timestep.h"

namespace bEngine
{
    class DeltaTimer
    {
    public:
        DeltaTimer()
            : m_LastDeltaPoint()
        {}
        
        Timestep SampleDeltaTime();

    private:
        double m_LastDeltaPoint;
    
    };
}


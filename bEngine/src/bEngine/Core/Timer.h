#pragma once
#include "Timestep.h"

namespace bEngine
{
    class Timer
    {
    public:
        Timer()
            : m_LastDeltaPoint()
        {}
        
        Timestep SampleDeltaTime();

    private:
        double m_LastDeltaPoint;
    
    };
}


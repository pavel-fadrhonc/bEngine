#pragma once

#include <chrono>

namespace bEngine
{
    template
    <typename Tfn>
    class Timer
    {
    public:
        using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>; 
        
        Timer(const char* name, Tfn&& func)
            : m_Name(name), m_Func(func)
        {
            Start();
        }

        ~Timer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Start()
        {
            m_StartTimePoint = std::chrono::high_resolution_clock::now();
            m_Stopped = false;
        }

        long long Stop()
        {
            if (m_Stopped)
                return 0;
            
            time_point now = std::chrono::high_resolution_clock::now();
            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();

            float msDuration = (end - start) * 0.001f;
            
            // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - m_StartTimePoint);
            // auto msDuration = duration.count() * 0.001;

            //std::stringstream ss;
            //std::cout << "Duration of " << m_Name << " was " << msDuration << " ms" << '\n';
            //BE_CORE_TRACE(ss.str());

            m_Stopped = true;

            m_Func({m_Name, msDuration});

            return msDuration;
        }

    private:
        const char* m_Name;
        Tfn m_Func;
        bool m_Stopped {true};
        time_point m_StartTimePoint;
    };
}


#pragma once
#include "Core/Timestep.h"
#include "Events/Event.h"

namespace bEngine
{
    class BENGINE_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep dt) {}
        virtual void OnEvent(Event& event) {}
        virtual void OnImGuiRender() {}

        inline const std::string& GetName() {return m_DebugName;}

    private:
        std::string m_DebugName;
    
    };
}


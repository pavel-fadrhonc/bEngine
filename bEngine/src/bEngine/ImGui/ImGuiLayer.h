#pragma once

#include "imgui.h"

#include "bEngine/Layer.h"
#include "bEngine/Events/ApplicationEvent.h"
#include "bEngine/Events/KeyEvent.h"
#include "bEngine/Events/MouseEvent.h"

namespace bEngine
{
    class BENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

        static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key);
        
        enum class ModifierType
        {
            Ctrl = BIT(1),
            Shift = BIT(2),
            Alt = BIT(3),
            Super = BIT(4)
        };

        void ProcessModifier(KeyPressedEvent& keyPressedEvent);
        void ProcessModifier(KeyReleasedEvent& keyPressedEvent);

        void AddModifier(ModifierType modifier);
        void RemoveModifier(ModifierType modifier);
        bool HasModifier(ModifierType modifier);
        
        ModifierType m_modifier;
        float m_Time = 0.0;
    };
}

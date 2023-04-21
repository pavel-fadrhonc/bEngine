#pragma once
#include "bepch.h"

#include "Event.h"

namespace bEngine {

    class BENGINE_API KeyEvent : public Event 
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode) { }
        
        int m_KeyCode;
    };

    class BENGINE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent((keycode)), m_repeatCount(repeatCount) { }

        inline int GetRepeatCount() const { return m_repeatCount; }

        EVENT_CLASS_TYPE(KeyPressed)
        
        std::string ToString() const override
        {

            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_repeatCount;
    };

    class BENGINE_API KeyReleasedEvent : public KeyEvent
    {
        KeyReleasedEvent(int keycode)
            :KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyReleased)
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent";
            return ss.str();
        }

    };
}

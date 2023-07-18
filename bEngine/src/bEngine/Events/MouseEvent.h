#pragma once
#include "bepch.h"

#include "Event.h"

namespace bEngine
{
    class BENGINE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const {return m_MouseX;}
        inline float GetY() const {return m_MouseY;}
        
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        std::string ToString() const override
        {

            std::stringstream ss;
            ss << "MouseMovedEvent: " << " (" << m_MouseX << ", " << m_MouseY << ")";
            return ss.str();
        }

    private:
        float m_MouseX, m_MouseY;
    };

    class BENGINE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const {return m_XOffset;}
        inline float GetYOffset() const {return m_YOffset;}

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << " (" << m_XOffset << ", " << m_YOffset << ")";
            return ss.str();
        }
    
    private:
        float m_XOffset, m_YOffset;
    };
    
    class BENGINE_API MouseButtonEvent : public Event
    {
    public:
        inline int GetButtonCode() const {return m_Button;}
        
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        
    protected:
        MouseButtonEvent(int buttonCode)
            : m_Button(buttonCode) {}

        int m_Button;
    };

    class BENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };

    class BENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
    };
}

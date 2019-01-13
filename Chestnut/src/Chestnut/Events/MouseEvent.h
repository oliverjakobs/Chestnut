#pragma once

#include "Event.h"

namespace chst
{
	class CHESTNUT_API MouseMovedEvent : public Event
	{
	private:
		float m_mouseX, m_mouseY;
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class CHESTNUT_API MouseScrolledEvent : public Event
	{
	private:
		float m_offsetX, m_offsetY;
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_offsetX(xOffset), m_offsetY(yOffset) {}

		inline float getOffsetX() const { return m_offsetX; }
		inline float getOffsetY() const { return m_offsetY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << getOffsetX() << ", " << getOffsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class CHESTNUT_API MouseButtonEvent : public Event
	{
	protected:
		int m_button;
		MouseButtonEvent(int button) : m_button(button) {}
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class CHESTNUT_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CHESTNUT_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
#pragma once

#include "Event.h"

namespace chst 
{
	class CHESTNUT_API WindowResizeEvent : public Event
	{
	private:
		unsigned int m_width, m_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CHESTNUT_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
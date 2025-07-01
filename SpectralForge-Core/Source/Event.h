#pragma once

#include <string>

namespace Badiya
{
	//TODO: Move this to base header
#define BIT(x) (1 << (x))
	
	enum class EventType : std::uint8_t
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	//For Filtering if we need it
	//Using bit field to apply different event types to same category
	enum EventCategory : std::uint8_t
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(0),
		EventCategoryKeyboard = BIT(0),
		EventCategoryMouse = BIT(0),
		EventCategoryMouseButton = BIT(0),

	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
	virtual EventType GetEventType() const override {return GetStaticType(); }\
	virtual const char* GetName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	//Base class for events
	class Event
	{
	public:

		virtual ~Event() = default;

		bool Handled = false;

		[[nodiscard]] virtual EventType GetEventType() const = 0;
		[[nodiscard]] virtual const char* GetName() const = 0; //Debugging use
		[[nodiscard]] virtual int GetCategoryFlags() const = 0;
		[[nodiscard]] virtual std::string ToString() const{ return GetName(); } //debugging use

		//Utility Func
		[[nodiscard]] bool IsInCategory(const EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

	};


	class EventDispatcher
	{
	private:
		Event& m_Event;
	public:
		explicit EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	};

	//For logging library allows for easy logging
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
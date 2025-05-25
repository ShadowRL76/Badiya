#pragma once

#include "Event.h"
#include "KeyCodes.h"

namespace Badiya {

	class KeyEvent : public Event
	{
	protected:
		explicit KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {
		}

		KeyCode m_KeyCode;
	public:
		[[nodiscard]] KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class KeyPressedEvent final : public KeyEvent 
	{
	private:
		bool m_IsRepeat;
	public:
		explicit KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {
		}

		[[nodiscard]] bool IsRepeat() const { return m_IsRepeat; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		//MACRO so we dont have to repeat the same code over and over for the getters
		// Get type, name etc
		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {
		}

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent final : public KeyEvent
	{
	public:
		explicit KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {
		}

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
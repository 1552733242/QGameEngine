#pragma once;

#include"Event.h"




namespace QGame {
	class GAME_API KeyEvent :public Event {
	public:
		inline int GetKeyCode()const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode):m_KeyCode(keycode){}
		int m_KeyCode;
	};

	class GAME_API KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) :KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		inline int GetRepeatCount()const { return m_RepeatCount; }
		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class GAME_API KeyReleaseEvent :public KeyEvent {
	public:
		KeyReleaseEvent(int keycode):KeyEvent(keycode) {}
		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyRelease)
	};

	class GAME_API KeyTypeEvent :public KeyEvent {
	public:
		KeyTypeEvent(int keycode) :KeyEvent(keycode) {}
		
		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyTypeEvent: " << m_KeyCode ;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyType)
	
	};
}
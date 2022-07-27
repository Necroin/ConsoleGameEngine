#pragma once
#ifndef _INPUTEVENTS_H_
#define _INPUTEVENTS_H_
#include <Windows.h>
#include "../Bases/Tag/Tag.h"

namespace CGE::EventSystem::InputEvents {
	class IEvent {
	protected:
		tag_t _tag;
	public:
		tag_t get_tag();

		template<class DerivedEvent>
		const DerivedEvent* as() const {
			if (_tag == get_class_tag<DerivedEvent>()) {
				return static_cast<const DerivedEvent*>(this);
			}
			return nullptr;
		}
	public:
		IEvent(tag_t tag);
	};

	namespace Async {
		namespace Keyboard {
			namespace Buttons {
				using button_t = int;
				inline constexpr button_t W = 0x57;
				inline constexpr button_t S = 0x53;
				inline constexpr button_t A = 0x41;
				inline constexpr button_t D = 0x44;
			};

			inline bool is_button_pressed(Buttons::button_t button) {
				return GetAsyncKeyState(button);
			}


			class KeyboardEvent {
			private:

			public:

			};
		};

		namespace Mouse {
			inline bool is_left_mouse_pressed() {
				return (GetKeyState(VK_LBUTTON) & 0x8000);
			};

			inline bool is_left_mouse_clicked() {
				static bool pressed = false;
				static bool was_pressed = false;
				pressed = is_left_mouse_pressed();
				if (pressed && !was_pressed) {
					return true;
				}
				was_pressed = pressed;
				return false;
			};

			class MouseClickEvent : public IEvent
			{
			private:
				int _x;
				int _y;
			public:
				int get_x() const;
				int get_y() const;
			public:
				MouseClickEvent(int x, int y);
			};
		};
	};
};
#endif
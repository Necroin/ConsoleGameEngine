#pragma once
#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_
#include "../UIObject/UIObject.h"
#include "../../Event System/EventSystem.h"
#include "../../Event System/InputEvents.h"

namespace CGE::UI {

	/**
	PushButton(Renderer& renderer, const std::string text, int color, UIObject* parent = nullptr);
	PushButton(Renderer& renderer,  const std::string text, int color, int x, int y);
	*/
	class PushButton : public UIObject
	{
	private:
		using symbol_type = char;
	private:
		std::string _text;
		EventSystem::Event<> _pressed;
		int _color;
	public:
		PushButton(Renderer& renderer, const std::string text, int color, UIObject* parent = nullptr);
		PushButton(Renderer& renderer,  const std::string text, int color, int x, int y);
		virtual void render() override;
		virtual void event(const CGE::EventSystem::InputEvents::IEvent& event) override;
		void set_text(std::string text);
		EventSystem::IEvent<>& pressed_event();
	};
}
#endif
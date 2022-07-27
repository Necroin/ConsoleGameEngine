#include "PushButton.h"

namespace CGE::UI {
	PushButton::PushButton(Renderer& renderer, const std::string text, int color, UIObject* parent) :
		UIObject(renderer, parent, GameRect{ 0, 0, static_cast<int>(text.size()) + 2, 3 }),
		_text(text),
		_color(color)
	{}

	PushButton::PushButton(Renderer& renderer, const std::string text, int color, int x, int y) :
		UIObject(renderer, nullptr, GameRect{ x, y, static_cast<int>(text.size()) + 2, 3 }),
		_text(text),
		_color(color)
	{}

	void PushButton::render()
	{
		if (!_hidden) {
			_renderer.draw_symbol_absolute(symbol_type(218), _position.x, _position.y, _color);
			_renderer.draw_symbol_absolute(symbol_type(191), _position.x + _position.width - 1, _position.y, _color);
			_renderer.draw_symbol_absolute(symbol_type(192), _position.x, _position.y + _position.height - 1, _color);
			_renderer.draw_symbol_absolute(symbol_type(217), _position.x + _position.width - 1, _position.y + _position.height - 1, _color);

			_renderer.draw_symbol_absolute(symbol_type(196), _position.x + 1, _position.y, _color, _text.size());
			_renderer.draw_symbol_absolute(symbol_type(196), _position.x + 1, _position.y + _position.height - 1, _color, _text.size());

			for (size_t i = 1; i < _position.height - 1; ++i) {
				_renderer.draw_symbol_absolute(symbol_type(179), _position.x, _position.y + i, _color);
				_renderer.draw_symbol_absolute(symbol_type(179), _position.x + _text.size() + 1, _position.y + i, _color);
			}
			_renderer.draw_string_absolute(_text.c_str(), _text.size(), _position.x + 1, _position.y + 1, _color);
		}
	}

	void PushButton::event(const CGE::EventSystem::InputEvents::IEvent& event)
	{
		if (auto mouse_event = event.as<CGE::EventSystem::InputEvents::Async::Mouse::MouseClickEvent>()) {
			if (mouse_event->get_x() >= _position.x && mouse_event->get_x() < _position.x + _position.width &&
				mouse_event->get_y() >= _position.y && mouse_event->get_y() < _position.y + _position.height)
			{
				_pressed();
			}
		}
	}

	void PushButton::set_text(std::string text)
	{
		int prev_width = _position.width;
		_text = text;
		int new_width = _text.size() + 2;
		if (prev_width != new_width) {
			add_width_to_parents(new_width - prev_width);
			decltype(auto) update_position_fucntion = &PushButton::UIObject::update_position;
			(root()->*update_position_fucntion)();
		}
	}

	EventSystem::IEvent<>& PushButton::pressed_event()
	{
		return _pressed;
	}
}
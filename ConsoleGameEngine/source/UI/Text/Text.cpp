#include "Text.h"

namespace CGE::UI {
	Text::Text(Renderer& renderer, const std::string text, int color, UIObject* parent) :
		UIObject(renderer, parent, GameRect{ 0, 0, static_cast<int>(text.size()), 1 }),
		_text(text),
		_color(color)
	{}

	Text::Text(Renderer& renderer, const std::string text, int color, int x, int y) :
		UIObject(renderer, nullptr, GameRect{ x, y, static_cast<int>(text.size()), 1 }),
		_text(text),
		_color(color)
	{}

	const std::string& Text::text() const
	{
		return _text;
	}

	void Text::set_text(std::string text)
	{
		int prev_width = _position.width;
		_text = text;
		int new_width = _text.size();
		if (prev_width != new_width) {
			add_width_to_parents(new_width - prev_width);
			decltype(auto) update_position_fucntion = &Text::UIObject::update_position;
			(root()->*update_position_fucntion)();
		}
	}

	void Text::render()
	{
		if(!_hidden) _renderer.draw_string_absolute(_text.c_str(), _position.width, _position.x, _position.y, _color);
	}
}
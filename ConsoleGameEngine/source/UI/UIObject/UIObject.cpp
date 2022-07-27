#include "UIObject.h"

namespace CGE::UI {
	void UIObject::update_position() {}

	void UIObject::add_height_to_parents(int additional_height)
	{
		_position.height += additional_height;
		if (_parent) {
			_parent->add_height_to_parents(additional_height);
		}
	}

	void UIObject::add_width_to_parents(int additional_width)
	{
		_position.width += additional_width;
		if (_parent) {
			_parent->add_width_to_parents(additional_width);
		}
	}

	UIObject* UIObject::root()
	{
		UIObject* root = this;
		while (root->_parent) {
			root = root->_parent;
		}
		return root;
	}

	UIObject::UIObject(Renderer& renderer, UIObject* parent, const GameRect& position) :
		_parent(parent),
		_position(position),
		_renderer(renderer)
	{}

	UIObject::~UIObject() {}

	void UIObject::show() const
	{
		_hidden = false;
	}

	void UIObject::hide() const
	{
		_hidden = true;
	}

	const bool UIObject::is_hidden() const
	{
		return _hidden;
	}

	void UIObject::event(const CGE::EventSystem::InputEvents::IEvent& event) {}

	int UIObject::x() const noexcept
	{
		return _position.x;
	}

	int UIObject::y() const noexcept
	{
		return _position.y;
	}

	int UIObject::width() const noexcept
	{
		return _position.width;
	}

	int UIObject::height() const noexcept
	{
		return _position.height;
	}

	const GameRect& UIObject::position() const noexcept
	{
		return _position;
	}
}
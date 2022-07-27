#pragma once
#ifndef _FRAME_H_
#define _FRAME_H_
#include "../UIObject/UIObject.h"

namespace CGE::UI {
	template<class _UIObject>
	class Frame : public UIObject
	{
	private:
		using symbol_type = char;
	private:
		std::unique_ptr<_UIObject> _framed_object;
		int _color;

		virtual void update_position() override {
			_position.width = 2;
			_position.height = 2;
			decltype(auto) object = _framed_object.get();
			decltype(auto) object_position = &Frame<_UIObject>::UIObject::_position;

			if (_framed_object) {
				(*object.*object_position).x = _position.x + 1;
				(*object.*object_position).y = _position.y + 1;
			}

			if (_framed_object) {
				decltype(auto) update_positiion_function = &Frame<_UIObject>::UIObject::update_position;
				((*object).*update_positiion_function)();
				_position.width += (*object.*object_position).width;
				_position.height += (*object.*object_position).height;
			}
		}
	public:
		Frame(Renderer& renderer, int color, int x, int y) :
			UIObject(renderer, nullptr, { x, y, 2, 2 }),
			_color(color)
		{}

		Frame(Renderer& renderer, UIObject* parent, int color) :
			UIObject(renderer, parent, { x, y, 2, 2 }),
			_color(color)
		{}
	public:
		virtual void show() const override {
			_hidden = false;
			_framed_object->show();
		}
		virtual void hide() const override {
			_hidden = true;
			_framed_object->hide();
		}

		virtual void render() override {
			if (!_hidden) {
				_renderer.draw_symbol_absolute(symbol_type(218), _position.x, _position.y, _color);
				_renderer.draw_symbol_absolute(symbol_type(191), _position.x + _position.width - 1, _position.y, _color);
				_renderer.draw_symbol_absolute(symbol_type(192), _position.x, _position.y + _position.height - 1, _color);
				_renderer.draw_symbol_absolute(symbol_type(217), _position.x + _position.width - 1, _position.y + _position.height - 1, _color);

				_renderer.draw_symbol_absolute(symbol_type(196), _position.x + 1, _position.y, _color, _position.width - 2);
				_renderer.draw_symbol_absolute(symbol_type(196), _position.x + 1, _position.y + _position.height - 1, _color, _position.width - 2);

				for (size_t i = 1; i < _position.height - 1; ++i) {
					_renderer.draw_symbol_absolute(symbol_type(179), _position.x, _position.y + i, _color);
					_renderer.draw_symbol_absolute(symbol_type(179), _position.x + _position.width - 1, _position.y + i, _color);
				}
				
				if (_framed_object) _framed_object->render();
			}
		}

		virtual void event(const CGE::EventSystem::InputEvents::IEvent& event) override {
			if (_framed_object) _framed_object->event(event);
		}

		template<class... Args>
		_UIObject& set(Args&&... args) {
			_framed_object = std::make_unique<_UIObject>(std::forward<Args>(args)...);

			if (!_parent) {
				decltype(auto) object = _framed_object.get();
				decltype(auto) object_position = &Frame::_position;
				(*object.*object_position).x = _position.x + 1;
				(*object.*object_position).y = _position.y + 1;
				_position.width = (*object.*object_position).width + 2;
				_position.height = (*object.*object_position).height + 2;
			}
			else {
				decltype(auto) update_position_fucntion = &Frame<_UIObject>::UIObject::update_position;
				(root()->*update_position_fucntion)();
			}
			return *_framed_object;
		}

		_UIObject& get_object() {
			return *_framed_object;
		}
	};
}
#endif
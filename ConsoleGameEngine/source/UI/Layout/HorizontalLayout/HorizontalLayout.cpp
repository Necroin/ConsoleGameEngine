#include "HorizontalLayout.h"

namespace CGE::UI {
	void HorizontalLayout::update_position()
	{
		bool first_object_flag = true;
		decltype(auto) object_position = &HorizontalLayout::_position;
		_position.width = 0;
		for (auto&& object : _objects) {
			decltype(auto) update_position_fucntion = &HorizontalLayout::UIObject::update_position;
			if (first_object_flag) {
				(*object.*object_position).x = _position.x;
				_position.width += (*object.*object_position).width;
				first_object_flag = false;
			}
			else {
				(*object.*object_position).x = _position.x + _position.width + _step;
				_position.width += ((*object.*object_position).width + _step);
			}
			if (_model == Model::up) {
				(*object.*object_position).y = _position.y;
			}
			if (_model == Model::centre) {
				(*object.*object_position).y = (_position.y * 2 + _position.height - 1) / 2 - object->height() / 2;
			}
			if (_model == Model::down) {
				(*object.*object_position).y = (_position.y + _position.height - 1) - object->height();
			}
			((*object).*update_position_fucntion)();
		}
	}

	HorizontalLayout::HorizontalLayout(Renderer& renderer, int x, int y, int step, Model model) :
		Layout(renderer, nullptr, x, y, step),
		_model(model)
	{}

	HorizontalLayout::HorizontalLayout(Renderer& renderer, UIObject* parent, int step, Model model) :
		Layout(renderer, parent, 0, 0, step),
		_model(model)
	{}

	void HorizontalLayout::set_model(Model model)
	{
		_model = model;
		decltype(auto) root_update_position = &HorizontalLayout::UIObject::update_position;
		(root()->*root_update_position)();
	}
}
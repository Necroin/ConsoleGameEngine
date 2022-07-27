#pragma once
#ifndef _VERTICALLAYOUT_H_
#define _VERTICALLAYOUT_H_
#include "../Layout.h"

namespace CGE::UI {
	/**
	VerticalLayout(Renderer& renderer, int x, int y, int step = 1, Model model = Model::centre)
	VerticalLayout(Renderer& renderer, UIObject* parent, int step = 1, Model mode = Model::centre)
	*/
	class VerticalLayout : public Layout
	{
	public:
		enum class Model {
			left,
			centre,
			right
		};
	private:
		virtual void update_position() override;
		Model _model;
	public:
		VerticalLayout(Renderer& renderer, int x, int y, int step = 1, Model model = Model::centre);
		VerticalLayout(Renderer& renderer, UIObject* parent, int step = 1, Model mode = Model::centre);
		template<class _UIObject, class... Args>
		_UIObject& add_object(Args&&... args) {
			_objects.emplace_back(std::make_unique<_UIObject>(std::forward<Args>(args)...));
			decltype(auto) object = *_objects.back();
			auto current_step = _step * bool(_objects.size() - 1);
			if (object.width() > _position.width) {
				add_width_to_parents(object.width() - _position.width);
			}
			add_height_to_parents(object.height() + _step);
			decltype(auto) update_position_fucntion = &VerticalLayout::UIObject::update_position;
			(root()->*update_position_fucntion)();

			return static_cast<_UIObject&>(object);
		}

		void set_model(Model model);
	};
}
#endif
#pragma once
#ifndef _HORIZONTALLAYOUT_H_
#define _HORIZONTALLAYOUT_H_
#include "../Layout.h"

namespace CGE::UI {
	/**
	HorizontalLayout(Renderer& renderer, int x, int y, int step = 1, Model objects_model = Model::centre)
	HorizontalLayout(Renderer& renderer, UIObject* parent, int step = 1, Model objects_model = Model::centre)
	*/
	class HorizontalLayout : public Layout
	{
	public:
		enum class Model {
			up,
			centre,
			down
		};
	private:
		virtual void update_position() override;
		Model _model;
	public:
		HorizontalLayout(Renderer& renderer, int x, int y, int step = 1, Model objects_model = Model::centre);
		HorizontalLayout(Renderer& renderer, UIObject* parent, int step = 1, Model objects_model = Model::centre);
		template<class _UIObject, class... Args>
		_UIObject& add_object(Args&&... args) {
			_objects.emplace_back(std::make_unique<_UIObject>(std::forward<Args>(args)...));
			decltype(auto) object = *_objects.back();
			auto current_step = _step * bool(_objects.size() - 1);
			if (object.height() > _position.height) {
				add_height_to_parents(_position.height - object.height());
			}
			add_width_to_parents(object.width() + current_step);
			decltype(auto) update_position_fucntion = &HorizontalLayout::UIObject::update_position;
			(root()->*update_position_fucntion)();
			return static_cast<_UIObject&>(object);
		}

		void set_model(Model model);
	};
}
#endif
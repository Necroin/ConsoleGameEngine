#pragma once
#ifndef _LAYOUT_H_
#define _LAYOUT_H_
#include "../UIObject/UIObject.h"

namespace CGE::UI {
	class Layout : public UIObject
	{
	protected:
		std::vector<std::unique_ptr<UIObject>> _objects;
		int _step;
	public:
		Layout(Renderer& renderer, UIObject* parent, int x, int y, int step);
		virtual ~Layout();
	public:
		virtual void show() const;
		virtual void hide() const;
		virtual void render() override;
		virtual void event(const CGE::EventSystem::InputEvents::IEvent& event) override;
		std::unique_ptr<UIObject>& operator[](std::size_t index);
	};
}
#endif
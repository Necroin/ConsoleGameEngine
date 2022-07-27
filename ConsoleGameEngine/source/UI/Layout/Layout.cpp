#include "Layout.h"

namespace CGE::UI {
	Layout::Layout(Renderer& renderer, UIObject* parent, int x, int y, int step) :
		UIObject(renderer, parent, GameRect{ x, y, 0 ,0 }),
		_step(step)
	{}

	Layout::~Layout() {}

	void Layout::show() const
	{
		_hidden = false;
		for (auto&& object : _objects) {
			object->show();
		}
	}

	void Layout::hide() const
	{
		_hidden = true;
		for (auto&& object : _objects) {
			object->hide();
		}
	}

	void Layout::render()
	{
		if (!_hidden) {
			for (auto&& object : _objects) {
				object->render();
			}
		}
	}

	void Layout::event(const CGE::EventSystem::InputEvents::IEvent& event)
	{
		for (auto&& object : _objects) {
			object->event(event);
		}
	}

	std::unique_ptr<UIObject>& Layout::operator[](std::size_t index)
	{
		return _objects[index];
	}
}
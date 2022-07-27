#include "InputEvents.h"

namespace CGE::EventSystem::InputEvents {
	tag_t IEvent::get_tag()
	{
		return _tag;
	}

	IEvent::IEvent(tag_t tag) :
		_tag(tag)
	{}

	namespace Async::Mouse {
		int MouseClickEvent::get_x() const
		{
			return _x;
		}

		int MouseClickEvent::get_y() const
		{
			return _y;
		}

		MouseClickEvent::MouseClickEvent(int x, int y) :
			IEvent(get_class_tag<MouseClickEvent>()),
			_x(x),
			_y(y)
		{}
	};
};
#pragma once
#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_
#include "../../Bases/Bases_include.h"
#include "../../Renderer/Renderer.h"
#include "../../Event System/InputEvents.h"

namespace CGE::UI {
	class UIObject {
	protected:
		GameRect _position;
		UIObject* _parent;
		Renderer& _renderer;
		mutable bool _hidden = true;
	protected:
		virtual void update_position();
		void add_height_to_parents(int additional_height);
		void add_width_to_parents(int additional_width);
		UIObject* root();
	public:
		UIObject(Renderer& renderer, UIObject* parent, const GameRect& position);
		virtual ~UIObject();
	public:
		virtual void show() const;
		virtual void hide() const;
		const bool is_hidden() const;
		virtual void render() = 0;
		virtual void event(const CGE::EventSystem::InputEvents::IEvent& event);
		int x() const noexcept;
		int y() const noexcept;
		int width() const noexcept;
		int height() const noexcept;
		const GameRect& position() const noexcept;
	};
}
#endif
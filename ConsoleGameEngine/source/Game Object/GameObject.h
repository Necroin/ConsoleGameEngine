#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "../std_includes.h"
#include "../Bases/Bases_include.h"
#include <map>
#include <functional>

namespace CGE {
	class GameObject {
	public:
		template<class _Object>
		using pointer_type = std::shared_ptr<_Object>;
		template<class _Object>
		using TemplateObjectList = std::list<pointer_type<_Object>>;
		template<class _Object>
		using TemplateObjectMap = std::map<tag_t, TemplateObjectList<_Object>>;
		using self_pointer_type = pointer_type<GameObject>;
		using ObjectList = TemplateObjectList<GameObject>;
		using ObjectMap = TemplateObjectMap<GameObject>;
	protected:
		GameRect _position;
		tag_t _tag;
		std::function<void()> _destructor;
	public:
		const GameRect& get_position() const;
		tag_t get_tag() const;
		void move_to(GameRect new_position);
	public:
		GameObject(GameRect position, tag_t tag);
		virtual void action(ObjectMap& _objects) {}
		virtual void update() {}
		virtual void render() {}
		virtual ~GameObject() { _destructor(); }
	};
};
#endif
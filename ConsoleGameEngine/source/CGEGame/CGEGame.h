#pragma once
#ifndef _CGE_GAME_H_
#define _CGE_GAME_H_

#include "../Renderer/Renderer.h"

namespace CGE {
	template<class _DerivedGameClass>
	class CGEGame {
	private:
		_DerivedGameClass& _game;
	protected:
		int _FPS;
		bool _is_active = true;
		Renderer _renderer;
		CGE::GameObject::ObjectMap _game_objects;
	public:
		CGEGame(_DerivedGameClass& game, int game_FPS) :
			_FPS(game_FPS),
			_game(game)
		{}
	protected:
		virtual void event() {}
		virtual void action() {}
		virtual void update() {}
		virtual void render() {}
	private:
		void do_frame_interation() {
			_renderer.swap_surfaces();
			_game.event();
			_game.action();
			_game.update();
			_game.render();
			_renderer.render();
		}
	public:
		void execute() {
			std::chrono::milliseconds frame_delay{ 1000 / _FPS };
			while (_is_active) {
				decltype(auto) frame_start = std::chrono::steady_clock::now();
				do_frame_interation();
				decltype(auto) frame_time = std::chrono::steady_clock::now() - frame_start;
				if (frame_delay > frame_time) {
					std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(frame_delay - frame_time));
				}
			}
		}
	protected:
		template<class _Object, class... _Args>
		void insert_game_object(_Args&&... args) {
			tag_t object_key = get_class_tag<_Object>();
			decltype(auto) object = static_cast<GameObject::self_pointer_type>(std::make_shared<_Object>(std::forward<_Args>(args)...));
			decltype(auto) object_list_it = _game_objects.find(get_class_tag<_Object>());

			if (object_list_it != _game_objects.end()) {
				object_list_it->second.push_back(object);
			}
			else {
				_game_objects.insert(std::pair<tag_t, GameObject::ObjectList>{
					object_key,
						GameObject::ObjectList{ object }
				});
			}
		}
		template<class _Object>
		decltype(auto) get_objects_list() {
			return _game_objects.find(get_class_tag<_Object>());
		}
	};
};
#endif
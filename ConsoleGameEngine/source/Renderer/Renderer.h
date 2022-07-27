#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "../Camera/Camera.h"

namespace CGE {
	class Renderer {
	private:
		inline static constexpr int _surfaces_count = 2;
		std::array<HANDLE, _surfaces_count> _surfaces;
		HANDLE _current_surface;
		int _current_surface_index;
		Camera _camera;
		int _max_width;
		int _max_height;
	private:
		void clear_surface(HANDLE surface);
	public:
		Renderer();
		~Renderer();
	public:
		void draw_symbol(char symbol, int x, int y, int color);
		void draw_symbol(char symbol, int x, int y, int color, size_t count);
		void draw_string(const char* string, size_t length, int x, int y, int color);

		void draw_symbol_absolute(char symbol, int x, int y, int color);
		void draw_symbol_absolute(char symbol, int x, int y, int color, size_t count);
		void draw_string_absolute(const char* string, size_t length, int x, int y, int color);
	public:
	public:
		void draw_symbol(wchar_t symbol, int x, int y, int color);
		void draw_symbol(wchar_t symbol, int x, int y, int color, size_t count);
		void draw_string(const wchar_t* string, size_t length, int x, int y, int color);

		void draw_symbol_absolute(wchar_t symbol, int x, int y, int color);
		void draw_symbol_absolute(wchar_t symbol, int x, int y, int color, size_t count);
		void draw_string_absolute(const wchar_t* string, size_t length, int x, int y, int color);
	public:
		void swap_surfaces();
		void render();
	public:
		Camera& get_camera();
	public:
		COORD get_mouse_position();
	};
};
#endif
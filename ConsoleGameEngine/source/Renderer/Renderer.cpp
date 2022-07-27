#include "Renderer.h"

namespace CGE {
	Renderer::Renderer() :
		_current_surface_index(0)
	{
		for (auto&& surface : _surfaces) {
			surface = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		}
		if (_surfaces[0] == INVALID_HANDLE_VALUE ||
			_surfaces[1] == INVALID_HANDLE_VALUE)
		{
			throw std::exception("CreateConsoleScreenBuffer failed - (%d)");
		}

		DWORD console_prev_mode;
		GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &console_prev_mode);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), console_prev_mode & ~ENABLE_QUICK_EDIT_MODE);

		for (auto&& surface : _surfaces) {
			SetConsoleActiveScreenBuffer(surface);
			int font_size = 10;
			CONSOLE_FONT_INFOEX font_info;
			COORD new_font_size{ font_size, font_size };
			font_info.cbSize = sizeof(font_info);

			//GetCurrentConsoleFontEx(surface, TRUE, &font_info);
			//font_info.dwFontSize = new_font_size;
			//font_info.FontFamily = FF_DONTCARE;
			//font_info.FontWeight = FW_NORMAL;
			//SetCurrentConsoleFontEx(surface, TRUE, &font_info);

			COORD largest_size = GetLargestConsoleWindowSize(surface);
			SMALL_RECT windowSize = { 0, 0, largest_size.X - 1, largest_size.Y - 1 };
			SetConsoleScreenBufferSize(surface, largest_size);
			SetConsoleWindowInfo(surface, TRUE, &windowSize);
			SetConsoleDisplayMode(surface, CONSOLE_FULLSCREEN_MODE, &largest_size);

			//GetCurrentConsoleFontEx(surface, TRUE, &font_info);
			//font_info.dwFontSize = new_font_size;
			//font_info.FontFamily = FF_DONTCARE;
			//font_info.FontWeight = FW_NORMAL;
			//SetCurrentConsoleFontEx(surface, TRUE, &font_info);

			CONSOLE_CURSOR_INFO cursor_info;
			GetConsoleCursorInfo(surface, &cursor_info);
			cursor_info.bVisible = false;
			SetConsoleCursorInfo(surface, &cursor_info);
		}

		HWND current_console_window = GetConsoleWindow();
		ShowScrollBar(current_console_window, SB_BOTH, FALSE);
		EnableScrollBar(current_console_window, SB_BOTH, ESB_DISABLE_BOTH);
		_current_surface = _surfaces[_current_surface_index];
		SetConsoleActiveScreenBuffer(_current_surface);

		CONSOLE_SCREEN_BUFFER_INFO buffer_info;
		GetConsoleScreenBufferInfo(_current_surface, &buffer_info);
		_max_width = buffer_info.dwSize.X;
		_max_height = buffer_info.dwSize.Y;
		_camera.set_position({ 0,0, buffer_info.dwSize.X, buffer_info.dwSize.Y });
	}

	Renderer::~Renderer()
	{
		for (auto&& surface : _surfaces) {
			CloseHandle(surface);
		}
	}

	void Renderer::clear_surface(HANDLE surface)
	{
		DWORD written;
		CONSOLE_SCREEN_BUFFER_INFO buf_info;
		GetConsoleScreenBufferInfo(surface, &buf_info);
		int cell_count = buf_info.dwSize.X * buf_info.dwSize.Y;
		FillConsoleOutputCharacterA(surface, ' ', cell_count, COORD{ 0,0 }, &written);
	}

	void Renderer::draw_symbol(char symbol, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ _camera.translate_x_coordinate(x), _camera.translate_y_coordinate(y) };
		FillConsoleOutputAttribute(_current_surface, (WORD)color, 1, coordinates, &written);
		FillConsoleOutputCharacterA(_current_surface, static_cast<CHAR>(symbol), 1, coordinates, &written);
	}

	void Renderer::draw_symbol(char symbol, int x, int y, int color, size_t count)
	{
		DWORD written;
		COORD coordinates{ _camera.translate_x_coordinate(x), _camera.translate_y_coordinate(y) };
		decltype(auto) camera_pos = _camera.get_position();
		if ((x + count - 1) >= (camera_pos.x + camera_pos.width)) {
			count -= ((x + count) - (camera_pos.x + camera_pos.width));
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, count, coordinates, &written);
		FillConsoleOutputCharacterA(_current_surface, static_cast<CHAR>(symbol), count, coordinates, &written);
	}

	void Renderer::draw_string(const char* string, size_t length, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		decltype(auto) camera_pos = _camera.get_position();
		if ((x + length - 1) >= (camera_pos.x + camera_pos.width)) {
			length -= ((x + length) - (camera_pos.x + camera_pos.width));
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, length, coordinates, &written);
		WriteConsoleOutputCharacterA(_current_surface, string, length, coordinates, &written);
	}

	void Renderer::draw_symbol_absolute(char symbol, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		FillConsoleOutputAttribute(_current_surface, (WORD)color, 1, coordinates, &written);
		FillConsoleOutputCharacterA(_current_surface, static_cast<CHAR>(symbol), 1, coordinates, &written);
	}

	void Renderer::draw_symbol_absolute(char symbol, int x, int y, int color, size_t count)
	{
		DWORD written;
		COORD coordinates{ x, y };
		if ((x + count - 1) >= _max_width) {
			count -= ((x + count) - _max_width);
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, count, coordinates, &written);
		FillConsoleOutputCharacterA(_current_surface, static_cast<CHAR>(symbol), count, coordinates, &written);
	}

	void Renderer::draw_string_absolute(const char* string, size_t length, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		if ((x + length - 1) >= _max_width) {
			length -= ((x + length) - _max_width);
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, length, coordinates, &written);
		WriteConsoleOutputCharacterA(_current_surface, string, length, coordinates, &written);
	}

	void Renderer::draw_symbol(wchar_t symbol, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ _camera.translate_x_coordinate(x), _camera.translate_y_coordinate(y) };
		FillConsoleOutputAttribute(_current_surface, (WORD)color, 1, coordinates, &written);
		FillConsoleOutputCharacterW(_current_surface, static_cast<WCHAR>(symbol), 1, coordinates, &written);
	}

	void Renderer::draw_symbol(wchar_t symbol, int x, int y, int color, size_t count)
	{
		DWORD written;
		COORD coordinates{ _camera.translate_x_coordinate(x), _camera.translate_y_coordinate(y) };
		decltype(auto) camera_pos = _camera.get_position();
		if ((x + count - 1) >= (camera_pos.x + camera_pos.width)) {
			count -= ((x + count) - (camera_pos.x + camera_pos.width));
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, count, coordinates, &written);
		FillConsoleOutputCharacterW(_current_surface, static_cast<WCHAR>(symbol), count, coordinates, &written);
	}

	void Renderer::draw_string(const wchar_t* string, size_t length, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		decltype(auto) camera_pos = _camera.get_position();
		if ((x + length - 1) >= (camera_pos.x + camera_pos.width)) {
			length -= ((x + length) - (camera_pos.x + camera_pos.width));
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, length, coordinates, &written);
		WriteConsoleOutputCharacterW(_current_surface, string, length, coordinates, &written);
	}

	void Renderer::draw_symbol_absolute(wchar_t symbol, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		FillConsoleOutputAttribute(_current_surface, (WORD)color, 1, coordinates, &written);
		FillConsoleOutputCharacterW(_current_surface, static_cast<WCHAR>(symbol), 1, coordinates, &written);
	}

	void Renderer::draw_symbol_absolute(wchar_t symbol, int x, int y, int color, size_t count)
	{
		DWORD written;
		COORD coordinates{ x, y };
		if ((x + count - 1) >= _max_width) {
			count -= ((x + count) - _max_width);
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, count, coordinates, &written);
		FillConsoleOutputCharacterW(_current_surface, static_cast<WCHAR>(symbol), count, coordinates, &written);
	}

	void Renderer::draw_string_absolute(const wchar_t* string, size_t length, int x, int y, int color)
	{
		DWORD written;
		COORD coordinates{ x, y };
		if ((x + length - 1) >= _max_width) {
			length -= ((x + length) - _max_width);
		}
		FillConsoleOutputAttribute(_current_surface, (WORD)color, length, coordinates, &written);
		WriteConsoleOutputCharacterW(_current_surface, string, length, coordinates, &written);
	}


	Camera& Renderer::get_camera()
	{
		return _camera;
	}

	COORD Renderer::get_mouse_position()
	{
		POINT pt;
		GetCursorPos(&pt);
		HWND hwnd = GetConsoleWindow();

		RECT rc;
		GetClientRect(hwnd, &rc);
		ScreenToClient(hwnd, &pt);

		CONSOLE_SCREEN_BUFFER_INFO buffer_info;
		GetConsoleScreenBufferInfo(_current_surface, &buffer_info);

		COORD coord = { 0, 0 };
		coord.X = MulDiv(pt.x, buffer_info.srWindow.Right, rc.right);
		coord.Y = MulDiv(pt.y, buffer_info.srWindow.Bottom, rc.bottom);
		return coord;
	}

	void Renderer::swap_surfaces()
	{
		++_current_surface_index %= _surfaces_count;
		_current_surface = _surfaces[_current_surface_index];
	}

	void Renderer::render()
	{
		SetConsoleActiveScreenBuffer(_current_surface);
		clear_surface(_surfaces[(_current_surface_index + 1) % _surfaces_count]);
	}
};
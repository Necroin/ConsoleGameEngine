#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include"../Game Object/GameObject.h"

namespace CGE {
	class Camera : public GameObject {
	public:
		Camera();
	public:
		int translate_x_coordinate(int x);
		int translate_y_coordinate(int y);
		GameRect translate_coordinates(int x, int y);
		GameRect translate_coordinates(GameRect position);
	public:
		void move_left(unsigned step = 1);
		void move_right(unsigned step = 1);
		void move_up(unsigned step = 1);
		void move_down(unsigned step = 1);
		void move_to(int x_centre, int y_centre);
		void set_position(GameRect position);
	};
};
#endif
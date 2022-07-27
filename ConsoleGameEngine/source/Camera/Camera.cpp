#include "Camera.h"

namespace CGE {
	Camera::Camera() :
		GameObject({ 0,0,0,0 }, get_class_tag<Camera>())
	{}

	int Camera::translate_x_coordinate(int x) {
		return x - _position.x;
	}

	int Camera::translate_y_coordinate(int y) {
		return y - _position.y;
	}

	GameRect Camera::translate_coordinates(int x, int y) {
		return { translate_x_coordinate(x), translate_y_coordinate(y) };
	}

	GameRect Camera::translate_coordinates(GameRect position) {
		position.x = translate_x_coordinate(position.x);
		position.y = translate_y_coordinate(position.y);
		return position;
	}

	void Camera::move_left(unsigned step) {
		_position.x -= step;
	}

	void Camera::move_right(unsigned step) {
		_position.x += step;
	}

	void Camera::move_up(unsigned step) {
		_position.y -= step;
	}

	void Camera::move_down(unsigned step) {
		_position.y += step;
	}

	void Camera::move_to(int x_centre, int y_centre) {
		_position.x = x_centre - _position.width / 2 + 1;
		_position.y = y_centre - _position.height / 2 + 1;
	}

	void Camera::set_position(GameRect position) {
		_position = position;
	}
};
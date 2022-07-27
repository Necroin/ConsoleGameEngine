#pragma once
#ifndef _GAMERECT_H_
#define _GAMERECT_H_

namespace CGE {
	struct GameRect {
		GameRect(int x, int y, int width, int height);
		GameRect(int x, int y);
		GameRect();
		int x;
		int y;
		int width;
		int height;

		bool operator==(const GameRect& other) const {
			return x == other.x && y == other.y && width == other.width && height == other.height;
		}
		bool operator!=(const GameRect& other) const {
			return !(*this == other);
		}
	};
};
#endif
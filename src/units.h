#pragma once
#include <cmath>

namespace units {

	typedef int MS; //Milliseconds

	typedef float position; //Position in the game world

	typedef int pixel; //Unit of pixel

	typedef float acceleration; // position / MS^2
	typedef float velocity; //position / MS

	inline pixel positionToPixel(position pos) {
		return round(pos);
	}

} 
#pragma once
#include <iostream>
#include <chrono>
#define LOG(x) std::cout << x << std::endl

namespace globals {

	//Target fps
	const int TARGET_FPS= 60;

	//Target maximum frame time
	const auto MAX_FRAME_TIME = std::chrono::milliseconds(1000 / TARGET_FPS);

	//Resolution width
	const int RES_WIDTH = 640;

	//Resolution height
	const int RES_HEIGHT = 480;

	enum verticalFacing{LEFT, RIGHT};


}
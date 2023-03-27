#include "core/timer.hh"

#include <SDL2/SDL.h>

namespace core {

timer::timer(unsigned max_tps) {
	this->max_tps = max_tps;
	tp_start = tp_prev_start = tp_prev_end = std::chrono::system_clock::now();
}

void timer::start() {
	tp_start = std::chrono::system_clock::now();
}

void timer::end() {
	auto end = std::chrono::system_clock::now();
	tp_prev_start = tp_start;
	tp_prev_end = end;

	auto dur = end - tp_start;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
	SDL_Delay(1000.0 / static_cast<double>(max_tps) - ms.count());
}

std::chrono::milliseconds timer::last_delta() {
	auto dur = tp_prev_end - tp_prev_start;
	return std::chrono::duration_cast<std::chrono::milliseconds>(dur);
}

}
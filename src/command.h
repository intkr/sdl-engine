#pragma once
#include <vector>
// intentionally included no delete pls ty :3
// I just want GitHub to see this file as c++
// so the language bar thing becomes 100% c++

enum CommandType {
	_CMD_NONE = 0, _CMD_TRANSITION, _CMD_STATE
};

struct Command {
	CommandType type;
	int value;
	Command() : type(_CMD_NONE), value(0) {}
	Command(CommandType t, int v) : type(t), value(v) {}
};

// _INTRO, _IDLE, _OUTRO, _END
enum TimelineType { _INTRO, _IDLE, _OUTRO, _END };

inline TimelineType operator++(TimelineType& a) {
	if (a == _END) return a;
	a = static_cast<TimelineType>(a + 1);
	return a;
}
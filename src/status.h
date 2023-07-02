#pragma once

// _INTRO, _IDLE, _OUTRO, _END
enum StatusType { _INTRO, _IDLE, _OUTRO, _END };

inline StatusType operator++(StatusType& a) {
	if (a == _END) return a;
	a = static_cast<StatusType>(a + 1);
	return a;
}
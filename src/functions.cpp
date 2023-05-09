#include "functions.h"

void randomizeString(std::string* s, int n) {
	int l = s->size();
	s->resize(l + n);
	for (; l < s->size(); l++) {
		(*s)[l] = rand() % 26 + (rand() % 2 ? 65 : 97);
	}
}
#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <Windows.h>

#include "jsoncpp/json.h"

#include "core.h"

class Player {
public:
	friend class Core;

	Player(Core* core);
	~Player();
	void saveData();

private:
	void init();
	void newData();
	void readData();

	std::string path;
	Json::Value data;

	std::fstream stream;

	Core* core;
};
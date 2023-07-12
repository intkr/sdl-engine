#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <Windows.h>

#include "jsoncpp/json.h"

class Core;

class Player {
public:
	Player(Core* core);
	~Player();
	void save();

	Json::Value getValue(std::string name, bool temporary);
	bool setValue(std::string name, Json::Value value, bool temporary);
private:
	void init();
	void reset();
	void load();

	std::string savepath;
	std::fstream stream;

	Json::Value tmpData;
	Json::Value saveData;


	Core* core;
};
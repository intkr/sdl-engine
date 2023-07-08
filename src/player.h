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
	void saveData();

	Json::Value getValue(std::string name);
	bool setValue(std::string name, Json::Value value);
private:
	void init();
	void newData();
	void readData();

	std::string path;
	Json::Value data;

	std::fstream stream;

	Core* core;
};
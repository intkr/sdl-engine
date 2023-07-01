#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <Windows.h>

#include "jsoncpp/json.h"

class Player {
public:
	Player(std::string path);
	~Player();
	void saveData();

private:
	void init();
	void newData();
	void readData();

	std::string path;
	Json::Value data;

	std::fstream stream;
};
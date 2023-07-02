#include "player.h"


Player::Player(Core* _core) : core(_core) {
	init();
}

Player::~Player() {}

void Player::init() {
	path = "data.json";
	stream.open(path, std::fstream::in);
	if (stream.is_open()) readData();
	else newData();
}

void Player::readData() {
	std::stringstream ss;
	stream >> ss.rdbuf();

	Json::Reader reader;
	std::string str = ss.str();

	reader.parse(str, data);

	int i = data.get("int", 0).asInt();
	// wide char example
	// 
	//str = data.get("kr", "").asString();
	//int len = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), 0, 0);
	//std::wstring wstr(len, 0);
	//MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], len);
	//wstr.assign(str.begin(), str.end());
    stream.close();
}

void Player::newData() {
	data["int"] = 1;

	// wide char example
	// 
	//std::wstring wstr = L"°¡³ª´Ù";
	//int len = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), 0, 0, NULL, NULL);
	//std::string str(len, 0);
	//WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], len, NULL, NULL);
	//data["kr"] = str;
}

void Player::saveData() {
	Json::StyledWriter writer;
	std::string str = writer.write(data);

	stream.open(path, std::fstream::out | std::fstream::trunc);
	stream << str;
	stream.close();
}
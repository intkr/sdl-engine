#include "player.h"

#include "core.h"

Player::Player(Core* _core) : core(_core) {
	init();
}

Player::~Player() {}

void Player::init() {
	savepath = "saveData.json";
	stream.open(savepath, std::fstream::in);
	if (stream.is_open()) load();
	else reset();
}

void Player::load() {
	std::stringstream ss;
	stream >> ss.rdbuf();

	Json::Reader reader;
	std::string str = ss.str();

	reader.parse(str, saveData);

	int i = saveData.get("selectedGame", 0).asInt();
	// wide char example
	// 
	//str = saveData.get("kr", "").asString();
	//int len = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), 0, 0);
	//std::wstring wstr(len, 0);
	//MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], len);
	//wstr.assign(str.begin(), str.end());
    stream.close();
}

void Player::reset() {
	saveData["selectedGame"] = -1;

	// wide char example
	// 
	//std::wstring wstr = L"°¡³ª´Ù";
	//int len = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), 0, 0, NULL, NULL);
	//std::string str(len, 0);
	//WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], len, NULL, NULL);
	//saveData["kr"] = str;
}

void Player::save() {
	Json::StyledWriter writer;
	std::string str = writer.write(saveData);

	stream.open(savepath, std::fstream::out | std::fstream::trunc);
	stream << str;
	stream.close();
}

Json::Value Player::getValue(std::string name, bool temporary) {
	Json::Value& data = temporary ? tmpData : saveData;
	if (data.isMember(name)) {
		return data[name];
	}
	return 0;
}

bool Player::setValue(std::string name, Json::Value value, bool temporary) {
	(temporary ? tmpData[name] : saveData[name]) = value;
	return true;
}
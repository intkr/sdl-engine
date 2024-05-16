#include <exception>

class GameException : public std::exception;

class DuplicateItemException : public GameException {
public:
	DuplicateItemException(std::string name, std::string type) : itemName(name), typeName(type) {
		errorMsg = "Error - Duplicate " + typeName + " : " + itemName;
	}
	const char* what() const override {
		return errorMsg.c_str();
	}
	
private:
	std::string itemName;
	std::string typeName;
	std::string errorMsg;
};

class InvalidItemException : public GameException {
public:
	InvalidItemException(std::string name, std::string type) : itemName(name), typeName(type) {
		errorMsg = "Error - Invalid " + typeName + " : " + itemName;
	const char* what() const override {
		return errorMsg.c_str();
	}
	
private:
	std::string itemName;
	std::string typeName;
	std::string errorMsg;
}
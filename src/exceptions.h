#include <exception>

class GameException : public std::exception;

class DuplicateItemException : public GameException {
public:
	DuplicateItemException(std::string name, std::string type) {
		errorMsg = "Error - Duplicate " + type + " : " + name;
	}
	const char* what() const override {
		return errorMsg.c_str();
	}
	
private:
	std::string errorMsg;
};

class InvalidItemException : public GameException {
public:
	InvalidItemException(std::string name, std::string type) {
		errorMsg = "Error - Invalid " + type + " : " + name;
	const char* what() const override {
		return errorMsg.c_str();
	}
	
private:
	std::string errorMsg;
}
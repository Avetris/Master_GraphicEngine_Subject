#include <engine\managers\messageManager.hpp>

void MessageManager::addMessage(std::string system, std::string key, std::string value)
{
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>::const_iterator exist = _messageList.find(system);
	std::unordered_map<std::string, std::string> map;
	std::pair<std::string, std::string> keyValue(key, value);
	if (exist != _messageList.end()) {
		map = exist->second;
	}
	map.insert(keyValue);
	_messageList[system] = map;
}

std::unordered_map<std::string, std::string> MessageManager::getMessages(std::string system, bool remove)
{
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>::const_iterator exist = _messageList.find(system);
	std::unordered_map<std::string, std::string> messages;
	if (remove && exist != _messageList.end()) {
		messages = exist->second;
		_messageList.erase(system);
	}
	return messages;
}

void MessageManager::resetMessages(std::string system, std::string key, std::string value)
{
	_messageList.clear();
}

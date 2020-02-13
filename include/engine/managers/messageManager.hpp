#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include <cstdint>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class MessageManager{
    public:
        static MessageManager* instance() {
            static MessageManager i;
            return &i;
        }

        void addMessage(std::string system, std::string key, std::string value);
        std::unordered_map<std::string, std::string> getMessages(std::string system, bool remove = false);
        void resetMessages(std::string system, std::string key, std::string value);

    private:
        MessageManager();
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _messageList;
};
#endif
    
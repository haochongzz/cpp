#ifndef FOLDER_H_
#define FOLDER_H_

#include <set>
#include <string>

// forward declaration
class Message;

class Folder {
public:
    explicit Folder(const std::string &s = "") : name_(s) {}

    Folder(const Folder &f) = delete;
    Folder &operator=(const Folder &f) = delete;

    ~Folder() = default; 

    void AddMessage(Message *message);
    void RemoveMessage(Message *message);

private:
    std::string name_;
    std::set<Message*> messages_;
};

void Folder::AddMessage(Message *message) {
    messages_.insert(message);
}

void Folder::RemoveMessage(Message *message) {
    messages_.erase(message);
}


#endif

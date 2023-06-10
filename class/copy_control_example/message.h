#ifndef EMAIL_H_
#define EMAIL_H_

#include <set>
#include <string>

#include "folder.h"

class Message {
public:
    // 有一个默认参数，因此也是默认构造函数.
    explicit Message(const std::string &s = "") : content_(s) {} 

    Message(const Message &m);

    Message(Message &&);

    Message &operator=(const Message &m);

    Message &operator=(Message &&);
    
    ~Message();

    // 从给定Folder中添加/删除本条message
    void Save(Folder &folder);
    void Remove(Folder &folder);

private:
    std::string content_;
    std::set<Folder*> folders_;

    // 工具函数，used by copy constructor, copy-assignment operator and destructor
    void AddToFolders(const Message &m);
    void RemoveFromFolders();
    void MoveFolders(Message *);

    friend void swap(Message &lhs, Message &rhs);
};

#endif
#include "message.h"

Message::Message(const Message &m)
    : content_(m.content_), folders_(m.folders_) {
    AddToFolders(m);
}

Message::Message(Message &&m) : content_(std::move(m.content_)) {
    MoveFolders(&m);
}

Message &Message::operator=(const Message &m) {
    RemoveFromFolders();
    content_ = m.content_;
    folders_ = m.folders_;
    AddToFolders(m);
    return *this;
}

Message &Message::operator=(Message &&m) {
    if (this != &m) {
        RemoveFromFolders();
        content_ = std::move(m.content_);
        MoveFolders(&m);
    }
    return *this;
}

Message::~Message() {
    RemoveFromFolders();
    folders_.clear();
}

void Message::Save(Folder &folder) {
    folder.AddMessage(this);
    folders_.insert(&folder);
}

void Message::Remove(Folder &folder) {
    folder.RemoveMessage(this);
    folders_.erase(&folder);
}

void Message::AddToFolders(const Message &m) {
    for (auto folder : m.folders_) {
        folder->AddMessage(this);
    }
}

void Message::RemoveFromFolders() {
    for (auto folder : folders_) {
        folder->RemoveMessage(this);
    }
}

void Message::MoveFolders(Message *m) {
    folders_ = std::move(m->folders_);

    for (auto f : folders_) {
        f->RemoveMessage(m);
        f->AddMessage(this);
    }
    // ensure that destroying m is harmless.
    m->folders_.clear();
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    // remove pointers to each Message from their respective Folders
    for (auto f : lhs.folders_) f->RemoveMessage(&lhs);
    for (auto f : rhs.folders_) f->RemoveMessage(&rhs);
    // swap the contents and Folder pinter sets
    swap(lhs.folders_, rhs.folders_);
    swap(lhs.content_, rhs.content_);
    for (auto f : lhs.folders_) f->AddMessage(&lhs);
    for (auto f : rhs.folders_) f->AddMessage(&rhs);
}

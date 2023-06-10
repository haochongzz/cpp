#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>

class Screen {
public:
    typedef std::string::size_type pos;

    Screen() = default;

    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}

    char get() const 
        { return contents[cursor]; }

    /* implicitly inline function */
    char get(pos r, pos c) const {
        pos row = r * width;
        return contents[row + c];
    }

    Screen &set(char c) {
        contents[cursor] = c;
        return *this;
    }

    Screen &set(pos r, pos c, char ch) {
        contents[r * width + c] = ch;
        return *this;
    }

    Screen &move(pos r, pos c) {
        pos row = r * width;
        cursor = row + c;
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

#endif 
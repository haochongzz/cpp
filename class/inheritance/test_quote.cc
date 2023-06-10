#include "disc_quote.h"

class B {
public:
    virtual int fct() { return 0; }
};

class D : public B {
public:
    int fct(int x) { return 2 * x; }
};

class D1 : public D {
public:
};

int main(int argc, char **argv) {
    // Quote basic("abc", 5.5);
    // DiscQuote disc("abc", 5.5, 5, 0.2);

    // basic.debug(std::cout) << std::endl;
    // disc.debug(std::cout) << std::endl;

    D d;
    d.fct(4);
    B *bptr = &d;
    bptr->fct();
    D1 d1;
    bptr = &d1;
    bptr->fct();

    return 0;
}
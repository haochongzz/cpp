#ifndef DISCQUOTE_H_
#define DISCQUOTE_H_

#include "quote.h"

class DiscQuote : public Quote {
   public:
    DiscQuote() = default;
    DiscQuote(const std::string &book, double pri, std::size_t qty, double disc)
        : Quote(book, pri), quantity(qty), discount(disc) {}

    DiscQuote(const DiscQuote &);
    DiscQuote(DiscQuote &&);

    DiscQuote &operator=(const DiscQuote &);
    DiscQuote &operator=(DiscQuote &&);

    double net_price(std::size_t n) const = 0;

    std::ostream &debug(std::ostream &os) const override {
        Quote::debug(os) << " DiscQuote::quantity " << quantity
                         << " DiscQuote::discount " << discount;
        return os;
    }

   protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

DiscQuote::DiscQuote(const DiscQuote &rhs)
    : Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) {}

DiscQuote::DiscQuote(DiscQuote &&rhs)
    : Quote(std::move(rhs)), quantity(rhs.quantity), discount(rhs.discount) {
    rhs.quantity = rhs.discount = 0;
}

DiscQuote &DiscQuote::operator=(const DiscQuote &rhs) {
    if (this != &rhs) {
        Quote::operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
    }
    return *this;
}

DiscQuote &DiscQuote::operator=(DiscQuote &&rhs) {
    if (this != &rhs) {
        Quote::operator=(std::move(rhs));
        quantity = rhs.quantity;
        discount = rhs.discount;
        discount = quantity = 0;
    }
    return *this;
}

#endif
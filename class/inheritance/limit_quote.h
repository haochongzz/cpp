#ifndef LIMITQUOTE_H_
#define LIMITQUOTE_H_

#include "disc_quote.h"

class LimitQuote : public DiscQuote {
   public:
    LimitQuote() = default;
    LimitQuote(const std::string &book, double pri, std::size_t qty,
               double disc);

    double net_price(std::size_t n) const override;
};

#endif
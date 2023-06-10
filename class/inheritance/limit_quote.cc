#include "limit_quote.h"

LimitQuote::LimitQuote(const std::string &book, double pri, std::size_t qty,
                       double disc)
    : DiscQuote(book, pri, qty, disc) {}

double LimitQuote::net_price(std::size_t n) const {
    if (n <= quantity)
        return n * price * (1 - discount);
    else
        return (n - quantity) * price + quantity * price * (1 - discount);
}
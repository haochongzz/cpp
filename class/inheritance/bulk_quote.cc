#include "bulk_quote.h"

BulkQuote::BulkQuote(const std::string &book, double pri, std::size_t qty,
                     double disc)
    : DiscQuote(book, pri, qty, disc) {}

double BulkQuote::net_price(size_t n) const {
    if (n >= quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}
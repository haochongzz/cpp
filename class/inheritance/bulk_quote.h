#ifndef BULKQUOTE_H_
#define BULKQUOTE_H_

#include <string>

#include "disc_quote.h"

class BulkQuote : public DiscQuote {
   public:
    BulkQuote() = default;
    BulkQuote(const std::string &book, double pri, std::size_t qty,
              double disc);

    double net_price(std::size_t n) const override;
};

#endif
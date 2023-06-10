cc_library(
    name = "quote",
    srcs = ["quote.cc"],
    hdrs = ["quote.h"],
)

cc_library(
    name = "disc_quote",
    hdrs = ["disc_quote.h"],
    deps = [
        ":quote",
    ],
)

cc_library(
    name = "bulk_quote",
    srcs = ["bulk_quote.cc"],
    hdrs = ["bulk_quote.h"],
    deps = [
        ":disc_quote",
    ],
)

cc_library(
    name = "limit_quote",
    srcs = ["limit_quote.cc"],
    hdrs = ["limit_quote.h"],
    deps = [
        ":disc_quote",
    ],
)

cc_binary(
    name = "test_quote",
    srcs = ["test_quote.cc"],
    deps = [
        ":limit_quote",
    ],
)

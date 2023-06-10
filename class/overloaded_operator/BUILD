cc_library(
    name = "StrBlob",
    srcs = ["StrBlob.cc"],
    hdrs = ["StrBlob.h"],
    deps = [
        ":ConstStrBlobPtr",
        ":StrBlobPtr",
    ],
)

cc_library(
    name = "StrBlobPtr",
    srcs = [
        "StrBlob.h",
        "StrBlobPtr.cc",
    ],
    hdrs = ["StrBlobPtr.h"],
)

cc_library(
    name = "ConstStrBlobPtr",
    srcs = [
        "ConstStrBlobPtr.cc",
        "StrBlob.h",
    ],
    hdrs = ["ConstStrBlobPtr.h"],
)

cc_binary(
    name = "TestStrBlob",
    srcs = ["TestStrBlob.cc"],
    deps = [
        ":StrBlob",
    ],
)

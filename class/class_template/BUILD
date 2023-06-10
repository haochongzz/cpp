cc_library(
    name = "Blob",
    srcs = [],
    hdrs = ["Blob.h"],
    deps = [
        # ":BlobPtr",
        # ":ConstBlobPtr",
    ]
)

cc_library(
    name = "BlobPtr",
    srcs = [],
    hdrs = ["BlobPtr.h"],
)

cc_library(
    name = "ConstBlobPtr",
    srcs = [],
    hdrs = ["ConstBlobPtr.h"],
)

cc_binary(
    name = "TestBlob",
    srcs = ["TestBlob.cc"],
    deps = [
        ":Blob",
        ":BlobPtr",
        ":ConstBlobPtr",
    ]
)

cc_library(
    name = "function_template",
    srcs = [],
    hdrs = ["exercise.h"],
)

cc_binary(
    name = "test",
    srcs = ["test.cc"],
    deps = [
        ":function_template",
    ]
)
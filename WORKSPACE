load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Google's gtest tool has a BUILD.bazel file defining @gtest and @gtest_main.
# So there is no need to define a local `build_file:`
#
git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    branch = "v1.10.x",
)

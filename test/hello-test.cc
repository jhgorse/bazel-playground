// Bazel stylizes includes as coming from explicitly named `deps`
// in the BAZEL.build file.  You can't #include `../main/hello-greet.h`
// because that reaches outside the compilation unit, and you also
// cannot add compilation options like `-I../`
//
#include "gtest/gtest.h"  // needs deps: "@gtest//:gtest"
#include "main/hello-greet.h"  // needs deps: "//main:hello-greet"

TEST(HelloTest, GetGreet) {
    EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");
}

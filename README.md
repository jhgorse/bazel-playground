# Bazel example

### Include multiple targets and deps

In this stage we step it up and showcase how to integrate multiple ```cc_library``` targets from different packages.

Below, we see a similar configuration from Stage 2, except that this BUILD file is in a subdirectory called lib. In Bazel, subdirectories containing BUILD files are known as packages. The new property ```visibility``` will tell Bazel which package(s) can reference this target, in this case the ```//main``` package can use ```hello-time``` library.

```
cc_library(
    name = "hello-time",
    srcs = ["hello-time.cc"],
    hdrs = ["hello-time.h"],
    visibility = ["//main:__pkg__"],
)
```

To use our ```hello-time``` libary, an extra dependency is added in the form of //path/to/package:target_name, in this case, it's ```//lib:hello-time```

```
cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":hello-greet",
        "//lib:hello-time",
    ],
)
```

To build this example you use (notice that 3 slashes are required in windows)
```
bazel build //main:hello-world

# In Windows, note the three slashes

bazel build ///main:hello-world
```

This example is referred from [bazel document](https://docs.bazel.build/versions/master/tutorial/cpp.html)

### External dependency and gtest example

In this step we will see how to include external dependency, for example `gtest`.

Let's write a test `test/hello-test.cc` for testing `get_greet()` function.

```cc
#include "gtest/gtest.h"
#include "main/hello-greet.h"

TEST(HelloTest, GetGreet) {
    EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");
}
```

Now lets create `test/BUILD`
```
cc_test(
    name = "hello-test",
    srcs = ["hello-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:gtest-main",
        "//main:hello-greet",
    ]
)

```

Observe how `copts` is used to include `gtest/include`. Bravo but where is `gtest-main` dependnecy ha?
i.e `"@gtest//:gtest-main"` ?

In `WORKSPACE` specify external repositiry to use in this project usiing `new` repository.
```
new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "external-deps/gtest.BUILD",
    strip_prefix = "googletest-release-1.7.0",
)
```

In `external-deps/gtest.BUILD` we will define `BUILD` target for `gtest` as follow
```
cc_library(
    name = "gtest-main",
    srcs = glob(
        ["src/*.cc"],
        exclude = ["src/gtest-all.cc"]
    ),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h"
    ]),
    copts = ["-Iexternal/gtest/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

```


now run

```
bazel test //test:hello-test
```

Yaay!!

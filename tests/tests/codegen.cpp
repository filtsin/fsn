#include <doctest.h>
#include <fsn/codegen.h>

namespace {
struct Foo {
    void foo();
    int bar(int);
};
}  // namespace

struct FooObj;
consteval { fsn::makeVtable<Foo>(^^FooObj); }

TEST_CASE("Methods generation") {
    FooObj foo{.foo = []() {}, .bar = [](int a) -> int { return a; }};

    CHECK(foo.bar(1) == 1);
}

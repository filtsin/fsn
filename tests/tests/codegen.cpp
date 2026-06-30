#include <doctest.h>

#include <fsn/codegen.hpp>

constexpr const char* myZ = "222";

namespace {
struct Foo {
    void foo() noexcept;
    int bar(int) const;

    [[= fsn::FnOptions{.name = "myname"}]] void zet();
};
}  // namespace

struct FooObj;
consteval { fsn::makeVtable<Foo>(^^FooObj); }

TEST_CASE("Methods generation") {
    FooObj foo{.foo = []() noexcept {}, .bar = [](int a) -> int { return a; }, .myname = []() {}};

    INFO(fsn::details::debugAggregate<FooObj>());
    CHECK(foo.bar(1) == 2);
}

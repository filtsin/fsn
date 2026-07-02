#include <doctest.h>

#include <fsn/interface.hpp>

namespace {
struct Interface {
    int random() const noexcept;
    [[= fsn::FnOptions{.name = "randomInt2"}]] int random(int a) const noexcept;
};

struct Interface2 : public Interface {
    int get42();
    [[= fsn::FnOptions{.name = "randomInt3"}]] int random(int a) const noexcept;
};

struct Random1 {
    int random() const noexcept { return 5; }
    int random(int a) const noexcept { return a; }
};

struct Random2 {
    int random() const noexcept { return 6; }
    int random(int a) const noexcept { return a; }
    int get42() { return 42; }
};

}  // namespace

TEST_CASE("Interface instance") {
    fsn::Interface<Interface> i(Random1{});

    CHECK(i->random() == 5);
}

TEST_CASE("Interface2 instance") {
    fsn::Interface<Interface2> i{Random2{}};

    CHECK(i->random() == 6);
    CHECK(i->randomInt2(6) == 6);
    CHECK(i->randomInt3(6) == 6);
    CHECK(i->get42() == 42);
}

namespace {

struct Interface1 {
    void foo();
};

struct Interface3 {
    void foo();
};

struct Int : Interface1, Interface3 {};

struct Foo {
    void foo() {}
};

TEST_CASE("Deduplication same methods") { fsn::Interface<Int> i = Foo{}; }

}  // namespace

#include <doctest.h>

#include <fsn/interface.hpp>

namespace {
struct Interface {
    int random() const noexcept;
};

struct Interface2 : public Interface {
    int get42();
};

struct Random1 {
    int random() const noexcept { return 5; }
};

struct Random2 {
    int random() const noexcept { return 6; }
    int get42() {
        return 42;
    }
};

}  // namespace

TEST_CASE("Interface instance") {
    fsn::Interface<Interface> i(Random1{});

    CHECK(i->random() == 5);
}

TEST_CASE("Interface2 instance") {
    fsn::Interface<Interface2> i { Random2{} };

    CHECK(i->random() == 6);
    CHECK(i->get42() == 42);
}

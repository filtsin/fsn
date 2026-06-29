#include <doctest.h>

#include <fsn/interface.hpp>

namespace {
struct Interface {
    int random() const;
};

struct Random1 {
    int random() const { return 5; }
};

}  // namespace

TEST_CASE("Interface instance") {
    fsn::Interface<Interface> i(Random1{});

    CHECK(i->random() == 5);
}

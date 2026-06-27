import codegen;

#include <meta>
#include <string>
#include <doctest.h>

constexpr auto result = fsn::genVtable<int>();
TEST_CASE("Vtable string interpolation") {
}

#include <meta>
#include <string>
#include <doctest.h>
#include <fsn/codegen.h>

constexpr auto result = fsn::genVtable<int>();
TEST_CASE("Vtable string interpolation") {
}

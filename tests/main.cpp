#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>
#include <meta>

namespace {
int docMain() {
    doctest::Context context;

    int res = context.run();

    return res;
}
}  // namespace

int main() { return docMain(); }

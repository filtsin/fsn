#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <meta>

namespace {
int docMain(int argc, char** argv) {
    doctest::Context context(argc, argv);

    int res = context.run();

    return res;
}
}  // namespace

int main(int argc, char** argv) { return docMain(argc, argv); }

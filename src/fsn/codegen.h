#include <meta>
#include <string>

namespace fsn {

/**
 * @brief Generate vtable for I interface
 *
 * @code
 * struct I {
 *    void foo();
 *    int bar(int z);
 *    [[="rename(fooInt)"]] void foo(int a);
 * };
 * @endcode
 *
 * this vtable must be generated
 *
 * @code
 * struct vtable {
 *      std::copyable_function<void()> foo;
 *      std::copyable_function<int(int)> bar;
 *      std::copyable_function<void(int)> fooInt;
 * };
 * @endcode
 *
 * Due to reflection of c++26 we can't generate methods, so this struct generate aggregate with
 * `copyable_function`. Due to soo `copyable_function` in gcc doesn't allocate memory for "small" lambdas.
 *
 * @tparam I - "Interface" like struct/class with methods declaration
 * @return meta descriptor of generated vtable
 */
#if defined(__GNUC__) && !defined(__clang__)
template <typename I>
consteval auto genVtable() {
    struct Foo {
        std::string s;
        int b;
        int a;
    };
    return ^^Foo;
}
#else
template <typename I>
consteval int genVtable() {
    return 0;
}
#endif

}  // namespace fsn

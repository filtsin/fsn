module;

#include <meta>
#include <functional>

export module codegen;

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
struct Foo {
    std::string s;
    int b;
    int a;
};
export template <typename I>
consteval std::meta::info genVtable() {
    return ^^Foo;
}

}  // namespace fsn

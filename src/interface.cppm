module;

export module fsn:interface;

import std;
import codegen;

//https://gcc.gnu.org/bugzilla/show_bug.cgi?id=124582 fixed in 16.2
//import std;

namespace fsn {

/**
 * @brief Go-like interface, accepts any types with all methods specified in I
 * type.
 *
 * @tparam I - should be a struct with required methods of interface
 */
export template <typename I>
requires std::is_class_v<I>
struct Interface {
    template <typename T>
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    Interface(T _) {}
};


}  // namespace fsn

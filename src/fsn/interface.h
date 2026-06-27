#include <type_traits>
#include <fsn/codegen.h>

namespace fsn {

/**
 * @brief Go-like interface, accepts any types with all methods specified in I
 * type.
 *
 * @tparam I - should be a struct with required methods of interface
 */
template <typename I>
requires std::is_class_v<I>
struct Interface {
    template <typename T>
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    Interface(T _) {
    }

#if defined(__GNUC__) && !defined(__clang__)
    typename [:genVtable<I>():] vtable;
#else
    struct VT {} vtable;
#endif
};

}  // namespace fsn

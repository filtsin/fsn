#include <memory>
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
    Interface([[maybe_unused]] T x) : ptr(std::make_shared<T>(std::move(x))) {
#if defined(__GNUC__) && !defined(__clang__)
        fsn::fillVTable<I>(vtable, static_cast<T*>(ptr.get()));
#endif
    }

private:
#if defined(__GNUC__) && !defined(__clang__)
    struct VTable;
    consteval {
        fsn::makeVtable<I>(^^VTable);
    }
#else
    struct VTable {};
#endif
    VTable vtable;

public:
    VTable* operator->() {
        return &vtable;
    }
    const VTable* operator->() const {
        return &vtable;
    }

private:
    std::shared_ptr<void> ptr;

};

}  // namespace fsn

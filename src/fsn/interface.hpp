#pragma once

#include <fsn/codegen.hpp>
#include <memory>
#include <type_traits>

namespace fsn {

template <typename I>
requires std::is_class_v<I>
struct InterfaceView;

template <typename T, typename I>
concept IsInterfaceView = std::same_as<std::remove_reference_t<T>, InterfaceView<I>>;

// NOLINTBEGIN(hicpp-explicit-conversions)
template <typename I>
requires std::is_class_v<I>
struct InterfaceView final {
#if defined(__GNUC__) && !defined(__clang__)
    struct VTable;
    consteval { fsn::makeVtable<I>(^^VTable); }
#else
    struct VTable {};
#endif

    InterfaceView() = delete;

    template <typename T>
    requires(!IsInterfaceView<T, I>)
    InterfaceView(T& obj) : InterfaceView(std::addressof(obj)) {}

    template <typename T>
    requires(!IsInterfaceView<T, I>)
    InterfaceView([[maybe_unused]] T* obj) {
#if defined(__GNUC__) && !defined(__clang__)
        fsn::fillVTable<I>(vtable, obj);
#else
        static_assert(false, "Interface supported only in gcc16> with reflection support");
#endif
    }

    // TODO
    template <typename U>
    InterfaceView(const InterfaceView<U>& u) = delete;

    VTable* operator->() { return &vtable; }
    VTable const* operator->() const { return &vtable; }

    VTable& vt() { return vtable; }
    VTable const& vt() const { return vtable; }

private:
    VTable vtable;
};

/**
 * @brief Go-like interface, accepts any types with all methods specified in I
 * type.
 *
 * @tparam I - should be a struct with required methods of interface
 */
template <typename I>
requires std::is_class_v<I>
struct Interface final {
    template <typename T>
    Interface(T x) : ptr(std::make_shared<T>(std::move(x)))
                   , view(std::make_shared<InterfaceView<I>>(static_cast<T*>(ptr.get()))) {}

    InterfaceView<I>::VTable* operator->() { return &view->vt(); }
    InterfaceView<I>::VTable const* operator->() const { return &view->vt(); }

    operator InterfaceView<I>&() { return *view.get(); }
    operator InterfaceView<I> const&() const { return *view.get(); }

private:
    // Note: Maybe I need to move these 2 fields in one allocation, but currently I don't like double
    // indirection for ptr

    std::shared_ptr<void> ptr;
    // Move view to heap because generated vtable can have big sizeof (40 bytes for each method in gcc 16.1 std)
    std::shared_ptr<InterfaceView<I>> view;
};
// NOLINTEND(hicpp-explicit-conversions)

}  // namespace fsn

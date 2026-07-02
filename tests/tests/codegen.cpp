#include <doctest.h>

#include <fsn/codegen.hpp>
#include <fsn/reflection_utils.hpp>
#include <functional>

TEST_CASE("VTable sizeof depends on count of methods in interface") {
    constexpr size_t methodsCount = 3;
    struct Interface {
        void foo1();
        void foo2();
        void foo3();
    };

    struct VTable;
    consteval { fsn::makeVtable<Interface>(^^VTable); }
    INFO(fsn::details::debugAggregate<VTable>());

    CHECK(sizeof(VTable) == sizeof(std::copyable_function<void()>) * methodsCount);
}

TEST_CASE("Renaming methods via FnOptions") {
    struct Interface {
        [[= fsn::FnOptions{.name = "fooInt"}]] int foo(int);
    };

    struct VTable;
    consteval { fsn::makeVtable<Interface>(^^VTable); }
    INFO(fsn::details::debugAggregate<VTable>());

    VTable vtable{
        [](int x) { return x + 1; },
    };
    CHECK(vtable.fooInt(1) == 2);
}

// compile-time test to be sure that VTable is generated
TEST_CASE("Interface compiles with different methods") {
    struct Interface {
        void foo();
        void foo1() const;
        void foo2() const noexcept;
        void foo3() &;
        void foo4() &&;
        void foo5() const&;
        void foo6() const& noexcept;
    };

    struct VTable;
    consteval { fsn::makeVtable<Interface>(^^VTable); }
    INFO(fsn::details::debugAggregate<VTable>());

    CHECK(1 == 1);
}

TEST_CASE("Interface inheritance generate all base methods") {
    struct BaseInterface {
        void foo();
    };

    struct Interface : BaseInterface {
        void bar();
    };

    struct VTable;
    consteval { fsn::makeVtable<Interface>(^^VTable); }
    INFO(fsn::details::debugAggregate<VTable>());

    VTable vt;
    vt.foo = [] {};
    vt.bar = [] {};

    CHECK(1 == 1);
}

TEST_CASE("Multiple inheritance with same methods") {
    struct BaseInterface1 {
        void foo();
        [[= fsn::FnOptions{.name = "bar1"}]] void bar();
    };

    struct BaseInterface2 {
        void foo();
        [[= fsn::FnOptions{.name = "bar2"}]] void bar();
    };

    struct Interface : BaseInterface1, BaseInterface2 {};

    struct VTable;
    consteval { fsn::makeVtable<Interface>(^^VTable); }
    INFO(fsn::details::debugAggregate<VTable>());

    VTable vt;
    vt.foo = [] {};
    vt.bar1 = [] {};
    vt.bar2 = [] {};

    CHECK(1 == 1);
}

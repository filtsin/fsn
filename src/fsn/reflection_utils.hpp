#include <meta>

namespace fsn::details {
#if defined(__GNUC__) && !defined(__clang__)
namespace meta = std::meta;
consteval std::vector<meta::info> memberFunctions(meta::info obj) {
    constexpr auto ctx = meta::access_context::unchecked();
    auto members = std::define_static_array(meta::members_of(obj, ctx));
    std::vector<meta::info> result;

    for (auto m : members) {
        if (!meta::is_function(m) || meta::is_constructor(m) || meta::is_destructor(m) ||
            meta::is_conversion_function(m) || !meta::has_identifier(m)) {
            continue;
        }
        result.emplace_back(m);
    }
    return result;
}

consteval meta::info findDataMemberByName(meta::info obj, std::string_view name) {
    constexpr auto ctx = meta::access_context::unchecked();
    for (auto m : meta::nonstatic_data_members_of(obj, ctx)) {
        if (meta::identifier_of(m) == name) {
            return m;
        }
    }
}

struct MemberFunctionError {};

// Find function in `obj` with `name` and type `fnType`. `fnType` includes const, noexcept etc.
consteval meta::info findMemberFunction(meta::info obj, std::string_view name, [[maybe_unused]] meta::info fnType) {
    for (auto m : memberFunctions(obj)) {
        if (meta::identifier_of(m) == name && meta::type_of(m) == fnType) {
            return m;
        }
    }

    // propagate error to fillVTable to print error message
    return ^^MemberFunctionError;
}

template <typename O>
std::string debugAggregate() {
    constexpr auto ctx = meta::access_context::unchecked();
    std::string result;
    template for (constexpr auto m : std::define_static_array(meta::nonstatic_data_members_of(^^O, ctx))) {
        template for (constexpr auto a : std::define_static_array(meta::annotations_of(m))) {
            result += meta::display_string_of(a);
            result += ' ';
        }

        result += meta::display_string_of(meta::type_of(m));
        result += " ";
        result += meta::identifier_of(m);
        result += ";\n";
    }
    return result;
}
#endif
}  // namespace fsn::details

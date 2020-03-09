#pragma once
#include <variant>

#define match(x) std::visit([&](auto&& x)
#define ret_match(x) return std::visit([&](auto&& x)
#define case(x,t) if constexpr (std::is_same_v<std::decay_t<decltype(x)>, t>)
#define case_expr(x,t) case(x,t) return
#define else_expr else return
#define match_end(x)  ,x )

namespace teaGameLib {
	template<typename ...Args>
	using Variant = std::variant<Args...>;
}


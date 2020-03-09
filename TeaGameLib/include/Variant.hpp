#pragma once
#include <variant>
#include <tuple>

#define match(x) teaGameLib::visit(x,[&](auto&& x)
#define match2(x1,x2) teaGameLib::visit(x1,x2,[&](auto&& x1,auto&& x2)
#define ret_match(x) return match(x)
#define ret_match2(x1,x2) return match2(x1,x2)
#define case(x,t) if constexpr (std::is_same_v<std::decay_t<decltype(x)>, t>)
#define case_expr(x,t) case(x,t) return
#define case2(x1,x2,t1,t2) \
	if constexpr (std::is_same_v<std::decay_t<decltype(x1)>, t1> && \
	std::is_same_v<std::decay_t<decltype(x2)>, t2>)
#define case_expr2(x1,x2,t1,t2) case2(x1,x2,t1,t2) return
#define else_expr else return
#define match_end )

namespace teaGameLib {

	template<typename ...Args>
	using Variant = std::variant<Args...>;

	template<typename ...Args, std::size_t ...I>
	decltype(auto) visit_impl(std::index_sequence<I...>, Args&&... args) {
		auto argTuple = std::forward_as_tuple(std::forward<Args>(args)...);
		return std::visit(
			std::get<sizeof...(I)>(argTuple),
			std::get<I>(argTuple)...
		);
	}

	template<typename ...Args>
	decltype(auto) visit(Args&& ...args) {
		return visit_impl(
			std::make_index_sequence<sizeof...(Args) - 1>{},
			std::forward<Args>(args)...
		);
	}
}


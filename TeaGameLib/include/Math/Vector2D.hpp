#pragma once
#include <functional> 
#include <cmath>

namespace teaGameLib::math {
	template<typename T>
	class Vector2D {
	public:
		T x;
		T y;

		constexpr Vector2D() {}
		constexpr Vector2D(T x, T y) :x(x), y(y) {}

		template<typename F>
		constexpr Vector2D<T> Zip(const F f, const Vector2D<T>& rhs)const noexcept {
			return { f(x , rhs.x), f(y , rhs.y) };
		}

		template<typename F>
		constexpr Vector2D<std::invoke_result_t<F, T>> Map(const F f)const noexcept {
			return { f(x), f(y) };
		}

		constexpr Vector2D<T> operator+(const Vector2D<T>& rhs)const noexcept {
			return Zip(std::plus<T>{}, rhs);
		}

		constexpr Vector2D<T>& operator+=(const Vector2D<T>& rhs)noexcept {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		constexpr Vector2D<T> operator-(const Vector2D<T>& rhs)const noexcept {
			return Zip(std::minus<T>{}, rhs);
		}

		constexpr Vector2D<T>& operator-=(const Vector2D<T>& rhs)noexcept {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		constexpr Vector2D<T> operator*(const T& rhs)const noexcept {
			return Map([&](T lhs) {return lhs * rhs; });
		}

		constexpr Vector2D<T> operator/(const T& rhs)const noexcept {
			return Map([&](T lhs) {return lhs / rhs; });
		}

		constexpr Vector2D<T> Swap()const noexcept {
			return { y,x };
		}

		void SwapSelf()noexcept {
			T& tmp = x;
			x = y;
			y = tmp;
		}

		static constexpr Vector2D<T> Zero()noexcept { return Vector2D<int>{0,0}.StaticCast<T>(); };
		static constexpr Vector2D<T> Up()noexcept { return Vector2D<int>{ 0, -1 }.StaticCast<T>(); };
		static constexpr Vector2D<T> Down()noexcept { return Vector2D<int>{ 0, 1 }.StaticCast<T>(); };
		static constexpr Vector2D<T> Left()noexcept { return Vector2D<int>{ -1, 0 }.StaticCast<T>(); };
		static constexpr Vector2D<T> Right()noexcept { return Vector2D<int>{ 1, 0 }.StaticCast<T>(); };

		constexpr auto LengthSq()const noexcept {
			return x * x + y * y;
		}

		float Length()const noexcept {
			return std::sqrtf(static_cast<float>(LengthSq()));
		}

		Vector2D<T> Normalize()const noexcept
		{
			return (*this) / Length();
		}

		void NormalizeSelf()noexcept {
			float length = Length();
			x /= length;
			y /= length;
		}

		constexpr auto Dot(const Vector2D<T>& rhs)
		{
			return (x * rhs.x + y * rhs.y);
		}

		template<typename U>
		constexpr Vector2D<U> StaticCast() const noexcept {
			return Map([](const auto& a) {return static_cast<U>(a); });
		}
	};
}
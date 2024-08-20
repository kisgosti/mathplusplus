/*

Copyright (c) 2024, Augustus Klein
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in
	  the documentation and/or other materials provided with the distribution.
	* Neither the name of the author nor the names of its
	  contributors may be used to endorse or promote products derived
	  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#pragma once

#ifdef MATHPLUSPLUS_EXPORTS
#define MATHPLUSPLUS_API _declspec(dllexport)
#else
#define MATHPLUSPLUS_API _declspec(dllimport)
#endif // MATHPLUSPLUS_EXPORTS

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "basics.h"

namespace math {

	class MATHPLUSPLUS_API bad_complex_init_list : public std::runtime_error {
	public:
		bad_complex_init_list();
	};

	template<typename T>
	class MATHPLUSPLUS_API complex {
	public:
		T re, im;
		constexpr complex();
		template<typename U>
		constexpr complex(const U& r);
		template<typename U>
		constexpr complex(const U& r, const U& i);
		template<typename U>
		constexpr complex(const std::initializer_list<U>& buf);
		template<typename U>
		constexpr complex(const complex<U>& x);

		[[nodiscard]] constexpr inline const complex<T> comp() const;
		[[nodiscard]] inline const auto norm() const;
		[[nodiscard]] inline const auto snorm() const;
		[[nodiscard]] inline const auto arg() const;

		template<typename U>
		[[nodiscard]] constexpr inline const bool operator==(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const bool operator!=(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const bool operator<(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const bool operator>(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const bool operator<=(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const bool operator>=(const complex<U>& x) const;

		template<typename U>
		constexpr inline complex<T>& operator=(const U& x);
		template<typename U>
		constexpr inline complex<T>& operator=(const complex<U>& x);
		template<typename U>
		constexpr inline complex<T>& operator+=(const U& x);
		template<typename U>
		constexpr inline complex<T>& operator+=(const complex<U>& x);
		template<typename U>
		constexpr inline complex<T>& operator-=(const U& x);
		template<typename U>
		constexpr inline complex<T>& operator-=(const complex<U>& x);
		template<typename U>
		constexpr inline complex<T>& operator*=(const U& x);
		template<typename U>
		constexpr inline complex<T>& operator*=(const complex<U>& x);
		template<typename U>
		constexpr inline complex<T>& operator/=(const U& x);
		template<typename U>
		constexpr inline complex<T>& operator/=(const complex<U>& x);

		template<typename U>
		[[nodiscard]] constexpr inline const auto operator+(const U& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator+(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator-(const U& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator-(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator*(const U& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator*(const complex<U>& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator/(const U& x) const;
		template<typename U>
		[[nodiscard]] constexpr inline const auto operator/(const complex<U>& x) const;

		constexpr static const complex<T> i = complex<T>(0, 1);
	};

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator+(const T& x, const complex<U>& y);
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator-(const T& x, const complex<U>& y);
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const T& x, const complex<U>& y);
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator/(const T& x, const complex<U>& y);

	template<typename T>
	struct MATHPLUSPLUS_API cxType {
		using type = complex<T>;
	};

	template<typename T>
	struct MATHPLUSPLUS_API cxType<complex<T>> {
		using type = complex<T>;
	};

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const complex<T> cxFromPolar(const T& r, const U& theta);

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const complex<T> cxSqrt(const complex<T>& x);

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const complex<T> cxCbrt(const complex<T>& x);

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const complex<T> abs(const complex<T>& x);

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const complex<T>& b, const U& e);

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const T& b, const complex<U>& e);

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const complex<T>& b, const complex<U>& e);
}

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sqrt(const math::complex<T>& x);

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cbrt(const math::complex<T>& x);

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const math::complex<T>& b, const U& e);

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const T& b, const math::complex<U>& e);

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const math::complex<T>& b, const math::complex<U>& e);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log2(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log10(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sin(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cos(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto tan(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asin(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acos(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto atan(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sinh(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cosh(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto tanh(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asinh(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acosh(const math::complex<T>& b);

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto atanh(const math::complex<T>& b);

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] const string to_string(const math::complex<T>& x);
}

template<typename T>
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::complex<T>& x);

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

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "basics.h"

namespace math {

	class bad_complex_init_list : public std::runtime_error {
	public:
		bad_complex_init_list();
	};

	template<typename T>
	class complex {
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

		_NODISCARD constexpr inline const complex<T> comp() const;
		_NODISCARD inline const T norm() const;
		_NODISCARD inline const T snorm() const;
		_NODISCARD inline const T arg() const;
		_NODISCARD inline const T sarg() const;

		template<typename U>
		_NODISCARD constexpr inline const bool operator==(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const bool operator!=(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const bool operator<(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const bool operator>(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const bool operator<=(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const bool operator>=(const complex<U>& x) const;

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
		_NODISCARD constexpr inline const auto operator+(const U& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator+(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator-(const U& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator-(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator*(const U& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator*(const complex<U>& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator/(const U& x) const;
		template<typename U>
		_NODISCARD constexpr inline const auto operator/(const complex<U>& x) const;
	};

	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator+(const T& x, const complex<U>& y);
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator-(const T& x, const complex<U>& y);
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator*(const T& x, const complex<U>& y);
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator/(const T& x, const complex<U>& y);

	template<typename T>
	struct cxType {
		using type = complex<T>;
	};

	template<typename T>
	struct cxType<complex<T>> {
		using type = complex<T>;
	};

	template<typename T, typename U>
	_NODISCARD constexpr inline const complex<T> cxFromPolar(const T& r, const U& theta);

	template<typename T>
	_NODISCARD constexpr inline const complex<T> cxSqrt(const complex<T>& x);

	template<typename T>
	_NODISCARD constexpr inline const complex<T> abs(const complex<T>& x);

	template<typename T, typename U>
	_NODISCARD constexpr inline const complex<T> cxPow(const complex<T>& b, const U& e);
}

namespace std {

	template<typename T>
	_NODISCARD const string to_string(const math::complex<T>& x);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const math::complex<T>& x);
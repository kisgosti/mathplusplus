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

#include <vector>
#include <iostream>
#include <exception>
#include <initializer_list>
#include <array>
#include "complex.h"

#ifndef _MX_SIZE_T_
#define _MX_SIZE_T_ uint8_t
#endif // !_MX_SIZE_T_

namespace math {

	template<typename T>
	class polynom {
	private:
		std::vector<T> buf;
	public:
		MATHPLUSPLUS_API constexpr polynom();
		template<typename U, _MX_SIZE_T_ _N>
		MATHPLUSPLUS_API constexpr polynom(const std::array<U, _N>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr polynom(const std::initializer_list<U>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr polynom(const polynom<U>& x);

		MATHPLUSPLUS_API constexpr inline void pop();
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const _MX_SIZE_T_ order() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::vector<typename cxType<T>::type> solve() const;

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& operator[](const _MX_SIZE_T_& n);

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& operator[](const _MX_SIZE_T_& n) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T operator()(const U& x) const;

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const polynom<U>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const polynom<U>& x) const;

		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator=(const polynom<U>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator+=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator+=(const polynom<U>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator-=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator-=(const polynom<U>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator*=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator*=(const polynom<U>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator/=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator/=(const polynom<U>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline polynom<T>& operator%=(const polynom<U>& x);

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator+(const U& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator+(const polynom<U>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator-(const U& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator-(const polynom<U>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const U& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const polynom<U>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator/(const U& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator/(const polynom<U>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator%(const polynom<U>& x) const;
	};
}
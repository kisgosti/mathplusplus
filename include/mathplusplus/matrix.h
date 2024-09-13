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

#include <stdint.h>
#include <array>
#include <vector>
#include <initializer_list>

#ifndef _MX_SIZE_T_
#define _MX_SIZE_T_ uint8_t
#endif // !_MX_SIZE_T_

namespace math {

	template<typename T, _MX_SIZE_T_ _N>
	class sqMatrix;

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	class matrix {
		static_assert(_H > 0, "Height of math::matrix must be non-zero.");
		static_assert(_W > 0, "Width of math::matrix must benon-zero.");
	protected:
		std::array<std::array<T, _W>, _H> buf;
	public:
		MATHPLUSPLUS_API constexpr matrix();
		template<typename U>
		MATHPLUSPLUS_API constexpr matrix(const std::array<std::array<U, _W>, _H>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr matrix(const std::initializer_list<std::initializer_list<U>>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr matrix(const matrix<U, _H, _W>& x);

		template<typename U>
		MATHPLUSPLUS_API matrix<T, _H, _W>& mask(matrix<U, _H, _W> x);

		MATHPLUSPLUS_API [[nodiscard]] const matrix<T, _W, _H> trans() const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] const auto masked(matrix<U, _H, _W> x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] const matrix<U, _H, _W> map(U(*f)()) const;

		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator begin();
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator end();
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator rbegin();
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator rend();

		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator begin() const;
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator end() const;
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator rbegin() const;
		MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator rend() const;

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline std::array<T, _W>& operator[](const _MX_SIZE_T_& h);
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::array<T, _W>& operator[](const _MX_SIZE_T_& h) const;

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const matrix<U, _H, _W>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const matrix<U, _H, _W>& x) const;

		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator=(const matrix<U, _H, _W>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator+=(const matrix<U, _H, _W>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator-=(const matrix<U, _H, _W>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator*=(const U& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator*=(const sqMatrix<U, _W>& x);
		template<typename U>
		MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& operator/=(const U& x);

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline  const auto operator+(const matrix<U, _H, _W>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator-(const matrix<U, _H, _W>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const U& x) const;
		template<typename U, _MX_SIZE_T_ _V>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const matrix<U, _W, _V>& x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator/(const U& x) const;
	};

	template<typename U, typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const U& x, const matrix<T, _H, _W>& m);

	template<typename T>
	struct cxType;

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	struct cxType<matrix<T, _H, _W>> {
		using type = matrix<typename cxType<T>::type, _H, _W>;
		using base = matrix<typename cxType<T>::base, _H, _W>;
	};

	template<typename T, _MX_SIZE_T_ _N>
	class sqMatrix : public matrix<T, _N, _N> {
	public:
		MATHPLUSPLUS_API constexpr sqMatrix();
		template<typename U>
		MATHPLUSPLUS_API constexpr sqMatrix(const std::array<std::array<U, _N>, _N>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr sqMatrix(const std::initializer_list<std::initializer_list<U>>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr sqMatrix(const sqMatrix<U, _N>& x);

		MATHPLUSPLUS_API constexpr inline const sqMatrix<T, _N> trans();

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T det() const;

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline static const sqMatrix<T, _N> idMatrix();
	};

	template<typename T, _MX_SIZE_T_ _N>
	struct cxType<sqMatrix<T, _N>> {
		using type = sqMatrix<typename cxType<T>::type, _N>;
		using base = sqMatrix<typename cxType<T>::base, _N>;
	};
}
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

#include <stdexcept>
#include "matrix.h"

namespace math {

	class null_vector_norm_2d : public std::runtime_error {
	public:
		MATHPLUSPLUS_API null_vector_norm_2d();
	};

	class vague_eigen_data : public std::runtime_error {
	public:
		MATHPLUSPLUS_API vague_eigen_data();
	};

	template<typename T>
	class vec2 : public matrix<T, 2, 1> {
	public:
		using matrix<T, 2, 1>::buf;

		MATHPLUSPLUS_API constexpr vec2();
		template<typename U>
		MATHPLUSPLUS_API constexpr vec2(std::array<U, 2>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec2(std::initializer_list<U>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec2(const U& x, const U& y);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec2(const vec2<U>& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& x();
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& y();
		MATHPLUSPLUS_API constexpr inline vec2<T>& normalize();
		template<typename U>
		MATHPLUSPLUS_API constexpr inline vec2<T>& project(vec2<U> x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& x() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& y() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec2<T> norm() const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto projection(vec2<U> x) const;

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator^(vec2<U> x) const;
	};

	template<typename T>
	struct cxType;

	template<typename T>
	struct cxType<vec2<T>> {
		using type = vec2<typename cxType<T>::type>;
		using base = vec2<typename cxType<T>::base>;
	};

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] std::vector<typename cxType<T>::type> eValue(const sqMatrix<T, 2>& x);

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] std::vector<vec2<typename cxType<T>::type>> eVector(const sqMatrix<T, 2>& x);

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] sqMatrix<T, 2> fromEigen2(std::vector<T> val, std::vector<vec2<T>> vec);
}

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::string to_string(const math::vec2<T>& x);
}

template<typename T>
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::vec2<T>& x);
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

	class null_vector_norm_3d : public std::runtime_error {
	public:
		MATHPLUSPLUS_API null_vector_norm_3d();
	};

	template<typename T>
	class vec3 : public matrix<T, 3, 1> {
	public:
		using matrix<T, 3, 1>::buf;

		MATHPLUSPLUS_API constexpr vec3();
		template<typename U>
		MATHPLUSPLUS_API constexpr vec3(const std::array<U, 3>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec3(const std::initializer_list<U>& buff);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec3(const U& x, const U& y, const U& z);
		template<typename U>
		MATHPLUSPLUS_API constexpr vec3(const vec3<U>& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& x();
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& y();
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& z();
		MATHPLUSPLUS_API constexpr inline vec3<T>& normalize();
		template<typename U>
		MATHPLUSPLUS_API constexpr inline vec3<T>& project(vec3<U> x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& x() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& y() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& z() const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec3<T> norm() const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec3<T> projection(vec3<U> x) const;

		template<typename U>
		MATHPLUSPLUS_API constexpr inline vec3<T>& operator*=(vec3<U> x);

		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator^(vec3<U> x) const;
		template<typename U>
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(vec3<U> x) const;
	};

	template<typename T>
	struct cxType;

	template<typename T>
	struct cxType<vec3<T>> {
		using type = vec3<typename cxType<T>::type>;
		using base = vec3<typename cxType<T>::base>;
	};
}

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::string to_string(const math::vec3<T>& x);
}

template<typename T>
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::vec3<T>& x);

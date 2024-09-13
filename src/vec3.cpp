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

#include "vec3.h"

#include <iostream>

namespace math {

	MATHPLUSPLUS_API null_vector_norm_3d::null_vector_norm_3d() : std::runtime_error("Cannot normalize 3d null-vector") {}

	template<typename T>
	MATHPLUSPLUS_API constexpr vec3<T>::vec3() : matrix<T, 3, 1>() {}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec3<T>::vec3(const std::array<U, 3>& buff) : matrix<T, 3, 1>() {
		buf[0][0] = buff[0];
		buf[1][0] = buff[1];
		buf[2][0] = buff[2];
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec3<T>::vec3(const std::initializer_list<U>& buff) : matrix<T, 3, 1>() {
		buf[0][0] = buff.size() > 0 ? *(buff.begin()) : 0;
		buf[1][0] = buff.size() > 1 ? *(buff.begin() + 1) : 0;
		buf[2][0] = buff.size() > 2 ? *(buff.begin() + 2) : 0;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec3<T>::vec3(const U& x, const U& y, const U& z) : matrix<T, 3, 1>() {
		buf[0][0] = x;
		buf[1][0] = y;
		buf[2][0] = z;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec3<T>::vec3(const vec3<U>& x) : matrix<T, 3, 1>(x) {}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& vec3<T>::x() {
		return buf[0][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& vec3<T>::y() {
		return buf[1][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& vec3<T>::z() {
		return buf[2][0];
	}
	template<typename T>
	MATHPLUSPLUS_API constexpr inline vec3<T>& vec3<T>::normalize() {
		return (*this) /= abs(*this);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline vec3<T>& vec3<T>::project(vec3<U> x) {
		return (*this) = (((*this) * x) / (x * x)) * x;
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& vec3<T>::x() const {
		return buf[0][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& vec3<T>::y() const {
		return buf[1][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& vec3<T>::z() const {
		return buf[2][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec3<T> vec3<T>::norm() const {
		return (*this) / abs(*this);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec3<T> vec3<T>::projection(vec3<U> x) const {
		return (((*this) * x) / (x * x)) * x;
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline vec3<T>& vec3<T>::operator*=(vec3<U> x) {
		return (*this) = vec3<T>(y() * x.z() - z() * x.y(), z() * x.x() - x() * x.z(), x() * x.y() - y() * x.x());
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto vec3<T>::operator^(vec3<U> x) const {
		return (buf[0][0] * x[0][0]) + (buf[1][0] * x[1][0]);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto vec3<T>::operator*(vec3<U> x) const {
		using V = decltype(T()* U());
		return vec3<V>(y() * x.z() - z() * x.y(), z() * x.x() - x() * x.z(), x() * x.y() - y() * x.x());
	}
}

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::string to_string(const math::vec3<T>& x) {
		return "{ " + to_string(x.x()) + ", " + to_string(x.y()) + ", " + to_string(x.z()) + " }";
	}
}

template<typename T>
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::vec3<T>& x) {
	return os << "{ " << x.x() << ", " << x.y() << ", " << x.z() << " }";
}
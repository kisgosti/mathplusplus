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

#include "vec2.h"

#include <iostream>

namespace math {

	MATHPLUSPLUS_API null_vector_norm_2d::null_vector_norm_2d() : std::runtime_error("Cannot normalize 2d null-vector") {}

	MATHPLUSPLUS_API vague_eigen_data::vague_eigen_data() : std::runtime_error("Eigen-data provided is too vague, matrix cannot be constructed") {}

	template<typename T>
	MATHPLUSPLUS_API constexpr vec2<T>::vec2() : matrix<T, 2, 1>() {}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec2<T>::vec2(std::array<U, 2>& buff) : matrix<T, 2, 1>() {
		buf[0][0] = buff[0];
		buf[1][0] = buff[1];
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec2<T>::vec2(std::initializer_list<U>& buff) : matrix<T, 2, 1>() {
		buf[0][0] = buff.size() > 0 ? *(buff.begin()) : 0;
		buf[1][0] = buff.size() > 1 ? *(buff.begin() + 1) : 0;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec2<T>::vec2(const U& x, const U& y) : matrix<T, 2, 1>() {
		buf[0][0] = x;
		buf[1][0] = y;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr vec2<T>::vec2(const vec2<U>& x) : matrix<T, 2, 1>(x) {}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& vec2<T>::x() {
		return buf[0][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& vec2<T>::y() {
		return buf[1][0];
	}
	template<typename T>
	MATHPLUSPLUS_API constexpr inline vec2<T>& vec2<T>::normalize() {
		return (*this) /= abs(*this);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline vec2<T>& vec2<T>::project(vec2<U> x) {
		return (*this) = (((*this) * x) / (x * x)) * x;
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& vec2<T>::x() const {
		return buf[0][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& vec2<T>::y() const {
		return buf[1][0];
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const vec2<T> vec2<T>::norm() const {
		return (*this) / abs(*this);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto vec2<T>::projection(vec2<U> x) const {
		return (((*this) * x) / (x * x)) * x;
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto vec2<T>::operator^(vec2<U> x) const {
		return (buf[0][0] * x[0][0]) + (buf[1][0] * x[1][0]);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] std::vector<typename cxType<T>::type> eValue(const sqMatrix<T, 2>& x) {
		using U = typename cxType<T>::type;
		U dis = pow(x[0][0] + x[1][1], 2) - 4 * (x[0][0] * x[1][1] - x[0][1] * x[1][0]);
		if (dis == (U)0) return { (x[0][0] + x[1][1]) / 2 };
		if (x[1][0] == 0) return { x[0][0], x[1][1] };
		return { (cxSqrt(dis) + x[0][0] + x[1][1]) / 2, (cxSqrt(dis) - x[0][0] - x[1][1]) / -2 };
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] std::vector<vec2<typename cxType<T>::type>> eVector(const sqMatrix<T, 2>& x) {
		using U = typename cxType<T>::type;
		if (x[0][1] == 0 && x[1][0] == 0 && x[0][0] == x[1][1]) return { };
		U dis = pow(x[0][0] + x[1][1], 2) - 4 * (x[0][0] * x[1][1] - x[0][1] * x[1][0]);
		if (dis == (U)0) {
			if (x[1][0] == 0) return { { (U)1, (U)0 } };
			return { { (U)((x[0][0] - x[1][1]) / (2 * x[1][0])) , (U)1 } };
		}
		if (x[1][0] == 0) return { { (U)1, (U)0 }, { (U)(x[0][1] / (x[1][1] - x[0][0])), (U)1 } };
		return { { (cxSqrt(dis) + x[0][0] - x[1][1]) / (2 * x[1][0]), (U)1 },
			{ (cxSqrt(dis) - x[0][0] + x[1][1]) / (-2 * x[1][0]), (U)1 } };
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] sqMatrix<T, 2> fromEigen2(std::vector<T> val, std::vector<vec2<T>> vec) {
		if (vec.size() == 0) return { { val[0], (T)0 }, { (T)0, val[0] } };
		if (vec.size() == 1) throw vague_eigen_data();
		if (vec[0].y() == 0) return { { val[0], vec[1].x() * (val[1] - val[0]) }, { 0, val[1] } };
		auto r = (val[0] - val[1]) / (vec[0].x() - vec[1].x());
		auto p = ((val[0] + val[1]) + r * (vec[0].x() + vec[1].x())) / 2, s = ((val[0] + val[1]) - r * (vec[0].x() + vec[1].y())) / 2;
		auto q = ((pow(val[0] - val[1], 2) - pow(p + s, 2)) / 4 + p * s) / r;
		return { { p, q }, { r, s } };
	}
}

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::string to_string(const math::vec2<T>& x) {
		return "{ " + to_string(x.x()) + ", " + to_string(x.y()) + " }";
	}
}

template<typename T>
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::vec2<T>& x) {
	return os << "{ " << x.x() << ", " << x.y() << " }";
}
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

#include "matrix.h"


namespace math {

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API constexpr matrix<T, _H, _W>::matrix() {
		for (auto& r : buf)
			r.fill(0);
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr matrix<T, _H, _W>::matrix(const std::array<std::array<U, _W>, _H>& buff) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] = buff[i][j];
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr matrix<T, _H, _W>::matrix(const std::initializer_list<std::initializer_list<U>>& buff) {
		_MX_SIZE_T_ i = 0;
		for (auto& row : buff) {
			_MX_SIZE_T_ j = 0;
			for (auto& elem : row) {
				buf[i][j] = elem;
				j++;
			}
			i++;
		}
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr matrix<T, _H, _W>::matrix(const matrix<U, _H, _W>& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] = x[i][j];
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API matrix<T, _H, _W>& matrix<T, _H, _W>::mask(matrix<U, _H, _W> x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] *= x[i][j];
		return *this;
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] const matrix<T, _W, _H> matrix<T, _H, _W>::trans() const {
		matrix<T, _W, _H> res;
		for (_MX_SIZE_T_ i = 0; i < _W; i++)
			for (_MX_SIZE_T_ j = 0; j < _H; j++)
				res[i][j] = buf[j][i];
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] const auto matrix<T, _H, _W>::masked(matrix<U, _H, _W> x) const {
		using V = decltype(T()* U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = buf[i][j] * x[i][j];
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] const matrix<U, _H, _W> matrix<T, _H, _W>::map(U(*f)()) const {
		matrix<U, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = f(buf[i][j], i, j);
		return res;
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator matrix<T, _H, _W>::begin() {
		return buf.begin();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator matrix<T, _H, _W>::end() {
		return buf.end();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator matrix<T, _H, _W>::rbegin() {
		return buf.rbegin();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::iterator matrix<T, _H, _W>::rend() {
		return buf.rend();
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator matrix<T, _H, _W>::begin() const {
		return buf.begin();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator matrix<T, _H, _W>::end() const {
		return buf.end();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator matrix<T, _H, _W>::rbegin() const {
		return buf.rbegin();
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] inline typename std::array<std::array<T, _W>, _H>::const_iterator matrix<T, _H, _W>::rend() const {
		return buf.rend();
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline std::array<T, _W>& matrix<T, _H, _W>::operator[](const _MX_SIZE_T_& h) {
		return buf[h];
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::array<T, _W>& matrix<T, _H, _W>::operator[](const _MX_SIZE_T_& h) const {
		return buf[h];
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool matrix<T, _H, _W>::operator==(const matrix<U, _H, _W>& x) const {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				if (buf[i][j] == x[i][j]) return false;
		return true;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool matrix<T, _H, _W>::operator!=(const matrix<U, _H, _W>& x) const {
		return !(*this == x);
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator=(const matrix<U, _H, _W>& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] = x[i][j];
		return *this;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator+=(const matrix<U, _H, _W>& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] += x[i][j];
		return *this;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator-=(const matrix<U, _H, _W>& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] -= x[i][j];
		return *this;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator*=(const U& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] *= x;
		return *this;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator*=(const sqMatrix<U, _W>& x) {
		matrix<T, _H, _W> tmp;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				for (_MX_SIZE_T_ k = 0; k < _W; k++)
					tmp[i, j] += buf[i][k] * x[k][j];
		return *this = tmp;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline matrix<T, _H, _W>& matrix<T, _H, _W>::operator/=(const U& x) {
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				buf[i][j] /= x;
		return *this;
	}

	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto matrix<T, _H, _W>::operator+(const matrix<U, _H, _W>& x) const {
		using V = decltype(T() + U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = buf[i][j] + x[i][j];
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto matrix<T, _H, _W>::operator-(const matrix<U, _H, _W>& x) const {
		using V = decltype(T() - U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = buf[i][j] - x[i][j];
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto matrix<T, _H, _W>::operator*(const U& x) const {
		using V = decltype(T()* U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = buf[i][j] * x;
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U, _MX_SIZE_T_ _V>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto matrix<T, _H, _W>::operator*(const matrix<U, _W, _V>& x) const {
		using V = decltype(T()* U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _V; j++)
				for (_MX_SIZE_T_ k = 0; k < _W; k++)
					res[i][j] += buf[i][k] * x[k][j];
		return res;
	}
	template<typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto matrix<T, _H, _W>::operator/(const U& x) const {
		using V = decltype(T()* U());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = buf[i][j] / x;
		return res;
	}

	template<typename U, typename T, _MX_SIZE_T_ _H, _MX_SIZE_T_ _W>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const U& x, const matrix<T, _H, _W>& m) {
		using V = decltype(U()* T());
		matrix<V, _H, _W> res;
		for (_MX_SIZE_T_ i = 0; i < _H; i++)
			for (_MX_SIZE_T_ j = 0; j < _W; j++)
				res[i][j] = x * m[i][j];
		return res;
	}

	template<typename T, _MX_SIZE_T_ _N>
	MATHPLUSPLUS_API constexpr sqMatrix<T, _N>::sqMatrix() : matrix<T, _N, _N>() {}
	template<typename T, _MX_SIZE_T_ _N>
	template<typename U>
	MATHPLUSPLUS_API constexpr sqMatrix<T, _N>::sqMatrix(const std::array<std::array<U, _N>, _N>& buff) : matrix<T, _N, _N>(buff) {}
	template<typename T, _MX_SIZE_T_ _N>
	template<typename U>
	MATHPLUSPLUS_API constexpr sqMatrix<T, _N>::sqMatrix(const std::initializer_list<std::initializer_list<U>>& buff) : matrix<T, _N, _N>(buff) {}
	template<typename T, _MX_SIZE_T_ _N>
	template<typename U>
	MATHPLUSPLUS_API constexpr sqMatrix<T, _N>::sqMatrix(const sqMatrix<U, _N>& x) : matrix<T, _N, _N>(x) {}

	template<typename T, _MX_SIZE_T_ _N>
	MATHPLUSPLUS_API constexpr inline const sqMatrix<T, _N> sqMatrix<T, _N>::trans() {
		sqMatrix<T, _N> res;
		for (_MX_SIZE_T_ i = 0; i < _N; i++)
			for (_MX_SIZE_T_ j = 0; j < _N; j++)
				res[i][j] = matrix<T, _N, _N>::buf[j][i];
		return res;
	}

	template<typename T, _MX_SIZE_T_ _N>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T sqMatrix<T, _N>::det() const {
		sqMatrix<T, _N> tmp = *this;
		short s = 1;
		T res = 1;
		for (_MX_SIZE_T_ i = 0; i + 1 < _N; i++) {
			_MX_SIZE_T_ piv = i;
			for (short j = i; j < _N; j++)
				if (abs(tmp[i][j]) > abs(tmp[i][piv])) piv = j;
			if (tmp[i][piv] == 0) return 0;
			if (piv != i) {
				for (short j = i; j < _N; j++)
					std::swap(tmp[j][i], tmp[j][piv]);
				s = 0 - s;
			}
			for (short j = i + 1; j < _N; j++) {
				T d = tmp[j][i] / tmp[i][i];
				for (short k = i; k < _N; k++)
					tmp[j][k] -= tmp[i][k] * d;
			}
			res *= tmp[i][i];
		}
		return res * tmp[_N - 1][_N - 1] * s;
	}

	template<typename T, _MX_SIZE_T_ _N>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const sqMatrix<T, _N> sqMatrix<T, _N>::idMatrix() {
		sqMatrix<T, _N> res;
		for (_MX_SIZE_T_ i = 0; i < _N; i++)
			res[i][i] = 1;
		return res;
	}
}
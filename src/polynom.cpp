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

#include "polynom.h"

namespace math {

	template<typename T>
	MATHPLUSPLUS_API constexpr inline void polynom<T>::pop() {
		while (buf[buf.size() - 1] == 0 && buf.size() > 1)
			buf.pop_back();
	}
	template<typename T>
	MATHPLUSPLUS_API constexpr polynom<T>::polynom() {
		buf.clear();
	}
	template<typename T>
	template<typename U, _MX_SIZE_T_ _N>
	MATHPLUSPLUS_API constexpr polynom<T>::polynom(const std::array<U, _N>& buff) {
		buf.clear();
		for (auto c : buff)
			buf.push_back((T)c);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr polynom<T>::polynom(const std::initializer_list<U>& buff) {
		buf.clear();
		for (auto c : buff)
			buf.push_back((T)c);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr polynom<T>::polynom(const polynom<U>& x) {
		buf.clear();
		for (_MX_SIZE_T_ i = 0; i < x.order(); i++)
			buf.push_back((T)x[i]);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const _MX_SIZE_T_ polynom<T>::order() const {
		return buf.size() - 1;
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const std::vector<typename cxType<T>::type> polynom<T>::solve() const {
		polynom<T> x(*this);
		x.pop();
		if (x.order() == 0) return { };
		using U = typename cxType<T>::type;
		std::vector<U> res;
		U r = pow(abs(x[0] / x[x.order()]), 1 / x.order());
		U n1 = -cxPow((T)-1, 1 / (x.order() + 1)), n2 = -cxPow((T)-1, 1 / x.order());
		for (_MX_SIZE_T_ i = 0; i <= x.order(); i++)
			res.push_back(n1 * pow(n2, i));
		std::vector<U> tmp;
		bool flag = true;
		while (flag) {
			tmp = res;
			for (_MX_SIZE_T_ i = 0; i <= x.order(); i++) {
				U t = 1;
				for (_MX_SIZE_T_ j = 0; j <= x.order(); j++)
					if (i != j) t *= tmp[i] - tmp[j];
				res[i] -= x(tmp[i]) / t;
			}
			for (_MX_SIZE_T_ i = 0; i <= x.order(); i++)
				flag &= (res[i] == tmp[i]);
			flag = !flag;
		}
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline T& polynom<T>::operator[](const _MX_SIZE_T_& n) {
		return buf[n];
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T& polynom<T>::operator[](const _MX_SIZE_T_& n) const {
		return buf[n];
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const T polynom<T>::operator()(const U& x) const {
		T res = 0;
		for (_MX_SIZE_T_ i = 0; i <= order(); i++)
			res += buf[i] * pow(x, i);
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool polynom<T>::operator==(const polynom<U>& x) const {
		if (order() != x.order()) return false;
		for (_MX_SIZE_T_ i = 0; i <= order(); i++)
			if (buf[i] != x[i]) return false;
		return true;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool polynom<T>::operator!=(const polynom<U>& x) const {
		if (order() != x.order()) return true;
		for (_MX_SIZE_T_ i = 0; i <= order(); i++)
			if (buf[i] != x[i]) return true;
		return false;
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator=(const U& x) {
		buf.clear();
		buf.push_back((T)x);
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator=(const polynom<U>& x) {
		buf.clear();
		for (_MX_SIZE_T_ i = 0; i <= x.order(); i++)
			buf.push_back((T)x[i]);
		pop();
		return *this; 
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator+=(const U& x) {
		buf[0] += x;
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator+=(const polynom<U>& x) {
		for (_MX_SIZE_T_ i = 0; i <= min(x.order(), order()); i++)
			buf[i] += x[i];
		if (order() < x.order()) {
			for (_MX_SIZE_T_ i = order() + 1; i <= x.order(); i++)
				buf.push_back((T)x[i]);
		}
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator-=(const U& x) {
		buf[0] -= x;
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator-=(const polynom<U>& x) {
		for (_MX_SIZE_T_ i = 0; i <= min(x.order(), order()); i++)
			buf[i] -= x[i];
		if (order() < x.order()) {
			for (_MX_SIZE_T_ i = order() + 1; i <= x.order(); i++)
				buf.push_back(-(T)x[i]);
		}
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator*=(const U& x) {
		for (auto& e : buf)
			e *= x;
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator*=(const polynom<U>& x) {
		polynom<T> res;
		for (_MX_SIZE_T_ i = 0; i <= x.order() + order(); i++) {
			res.buf.push_back(0);
			for (_MX_SIZE_T_ j = max(0, i - x.order()); j <= min(i, order()); j++)
				res.buf[i] += buf[j] * x[i - j];
		}
		res.pop();
		return operator=(res);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator/=(const U& x) {
		for (auto& e : buf)
			e /= x;
		pop();
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator/=(const polynom<U>& x) {
		polynom<T> tmp(*this), res;
		res.buf.push_back(0);
		for (_MX_SIZE_T_ i = x.order(); i <= order(); i++)
			res.buf.push_back(0);
		for (_MX_SIZE_T_ i = order() - x.order(); i >= 0; i--) {
			res[i] = tmp[i + x.order()] / x[x.order() - 1];
			for (_MX_SIZE_T_ j = 0; j < x.order(); j++)
				tmp[order() - j] -= res[i] * x[x.order() - j];
		}
		res.pop();
		return operator=(res);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline polynom<T>& polynom<T>::operator%=(const polynom<U>& x) {
		polynom<T> tmp(*this);
		operator-=(tmp /= x);
		pop();
		return *this;
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator+(const U& x) const {
		polynom<T> res(*this);
		res += x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator+(const polynom<U>& x) const {
		polynom<T> res(*this);
		res += x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator-(const U& x) const {
		polynom<T> res(*this);
		res -= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator-(const polynom<U>& x) const {
		polynom<T> res(*this);
		res -= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator*(const U& x) const {
		polynom<T> res(*this);
		res *= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator*(const polynom<U>& x) const {
		polynom<T> res(*this);
		res *= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator/(const U& x) const {
		polynom<T> res(*this);
		res /= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator/(const polynom<U>& x) const {
		polynom<T> res(*this);
		res /= x;
		res.pop();
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto polynom<T>::operator%(const polynom<U>& x) const {
		polynom<T> res(*this);
		res %= x;
		res.pop();
		return res;
	}
}
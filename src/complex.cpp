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

#define MATHPLUSPLUS_EXPORTS

#include "pch.h"
#include "math++.h"
#include "complex.h"
#include "basics.h"

namespace math {

	bad_complex_init_list::bad_complex_init_list() : std::runtime_error("Size of initializer list must be exactly 2 to construct math::complex") {}

	template<typename T>
	constexpr complex<T>::complex() : re(0), im(0) {}
	template<typename T>
	template<typename U>
	constexpr complex<T>::complex(const U& r) : re(r), im(0) {}
	template<typename T>
	template<typename U>
	constexpr complex<T>::complex(const U& r, const U& i) : re(r), im(i) {}
	template<typename T>
	template<typename U>
	constexpr complex<T>::complex(const std::initializer_list<U>& buf) {
		if (buf.size() > 2) throw bad_complex_init_list();
		re = buf.size() > 0 ? *(buf.begin()) : 0;
		im = buf.size() > 1 ? *(buf.begin() + 1) : 0;
	}
	template<typename T>
	template<typename U>
	constexpr complex<T>::complex(const complex<U>& x) {
		re = x.re;
		im = x.im;
	}

	template<typename T>
	_NODISCARD constexpr inline const complex<T> complex<T>::comp() const {
		return complex<T>(re, -1 * im);
	}
	template<typename T>
	_NODISCARD inline const T complex<T>::norm() const {
		return sqrt(abs(re) * abs(re) + abs(im) * abs(im));
	}
	template<typename T>
	_NODISCARD inline const T complex<T>::snorm() const {
		return im == 0 ? abs(re) * re : (*this).norm() * sgn(im);
	}
	template<typename T>
	_NODISCARD inline const T complex<T>::arg() const {
		return im == 0 ? re == 0 ? 0 : M_PI * (1 - sgn(re)) / 2 : re == 0 ? M_PI_2 * (2 - sgn(im)) : M_PI * ((2 - sgn(im) * (sgn(re) + 1)) / 2) + sgn(re) * sgn(im) * atan2(abs(im), abs(re));
	}
	template<typename T>
	_NODISCARD inline const T complex<T>::sarg() const {
		return im == 0 ? ((1 - sgn(re)) / 2) * M_PI : M_PI * ((1 - sgn(re) * sgn(im)) / 2) + sgn(re) * sgn(im) * atan2(abs(im), abs(re));
	}

	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator==(const complex<U>& x) const {
		return re == x.re && im == x.im;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator!=(const complex<U>& x) const {
		return !(*this == x);
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator<(const complex<U>& x) const {
		return (*this).snorm() == x.snorm() ? sarg() < x.sarg() : snorm() < x.snorm();
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator>(const complex<U>& x) const {
		return x < *this;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator<=(const complex<U>& x) const {
		return !(x < *this);
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const bool complex<T>::operator>=(const complex<U>& x) const {
		return !(*this < x);
	}

	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator=(const U& x) {
		re = x;
		im = 0;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator=(const complex<U>& x) {
		re = x.re;
		im = x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator+=(const U& x) {
		re += x;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator+=(const complex<U>& x) {
		re += x.re;
		im += x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator-=(const U& x) {
		re -= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator-=(const complex<U>& x) {
		re -= x.re;
		im -= x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator*=(const U& x) {
		re *= x;
		im *= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator*=(const complex<U>& x) {
		T tmp = re * x.re - im * x.im;
		im = re * x.im + x.re * im;
		re = tmp;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator/=(const U& x) {
		re /= x;
		im /= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	constexpr inline complex<T>& complex<T>::operator/=(const complex<U>& x) {
		T tmp = (x.re * re + x.im * im) / (x.re * x.re + x.im * x.im);
		im = (x.re * im - re * x.im) / (x.re * x.re + x.im * x.im);
		re = tmp;
		return *this;
	}

	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator+(const U& x) const {
		using V = decltype(T() + U());
		complex<V> res(re + x, im);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator+(const complex<U>& x) const {
		using V = decltype(T() + U());
		complex<V> res(re + x.re, im + x.im);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator-(const U& x) const {
		using V = decltype(T() - U());
		complex<V> res(re - x, im);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator-(const complex<U>& x) const {
		using V = decltype(T() - U());
		complex<V> res(re - x.re, im - x.im);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator*(const U& x) const {
		using V = decltype(T()* U());
		complex<V> res(re * x, im * x);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator*(const complex<U>& x) const {
		using V = decltype(T()* U());
		complex<V> res(re * x.re - im * x.im, re * x.im + x.re * im);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator/(const U& x) const {
		using V = decltype(T() / U());
		complex<V> res(re / x, im / x);
		return res;
	}
	template<typename T>
	template<typename U>
	_NODISCARD constexpr inline const auto complex<T>::operator/(const complex<U>& x) const {
		using V = decltype(T() / U());
		complex<V> res((x.re * re + x.im * im) / (x.re * x.re + x.im * x.im), (x.re * im - re * x.im) / (x.re * x.re + x.im * x.im));
		return res;
	}

	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator+(const T& x, const complex<U>& y) {
		using V = decltype(T() + U());
		complex<V> res(x + y.re, y.im);
		return res;
	}
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator-(const T& x, const complex<U>& y) {
		using V = decltype(T() - U());
		complex<V> res(x - y.re, -y.im);
		return res;
	}
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator*(const T& x, const complex<U>& y) {
		using V = decltype(T()* U());
		complex<V> res(x * y.re, x * y.im);
		return res;
	}
	template<typename T, typename U>
	_NODISCARD constexpr inline const auto operator/(const T& x, const complex<U>& y) {
		using V = decltype(T() / U());
		complex<V> res(x * y.re / y.norm(), -x * y.im / y.norm());
		return res;
	}

	template<typename T, typename U>
	_NODISCARD constexpr inline const complex<T> cxFromPolar(const T& r, const U& theta) {
		complex<T> res(r * cos(theta), r * sin(theta));
		return res;
	}

	template<typename T>
	_NODISCARD constexpr inline const complex<T> cxSqrt(const complex<T>& x) {
		return cxFromPolar(sqrt(x.norm()), x.arg() / 2);
	}

	template<typename T>
	_NODISCARD constexpr inline const complex<T> abs(const complex<T>& x) {
		return x.norm();
	}

	template<typename T, typename U>
	_NODISCARD constexpr inline const complex<T> cxPow(const complex<T>& b, const U& e) {
		return cxFromPolar(pow(b.norm(), e), b.arg() * e);
	}
}

namespace std {

	template<typename T>
	_NODISCARD const string to_string(const math::complex<T>& x) {
		std::string res = "";
		if (x.re != 0 || x.im == 0) res += to_string(x.re);
		if (x.re != 0 && x.im > 0) res += "+";
		if (x.im < 0) res += "-";
		if (x.im != 0 && x.im != 1 && x.im != -1) res += to_string(abs(x.im));
		if (x.im != 0) res += "i";
		return res;
	}
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const math::complex<T>& x) {
	if (x.re != 0 || x.im == 0) os << x.re;
	if (x.re != 0 && x.im > 0) os << "+";
	if (x.im < 0) os << "-";
	if (x.im != 0 && x.im != 1 && x.im != -1) os << abs(x.im);
	if (x.im != 0) os << "i";
	return os;
}

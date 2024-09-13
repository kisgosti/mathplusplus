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

#include "complex.h"

namespace math {

	template<typename T>
	MATHPLUSPLUS_API constexpr complex<T>::complex() : re(0), im(0) {}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr complex<T>::complex(const U& r) : re(r), im(0) {}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr complex<T>::complex(const U& r, const U& i) : re(r), im(i) {}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr complex<T>::complex(const std::initializer_list<U>& buf) {
		re = buf.size() > 0 ? *(buf.begin()) : 0;
		im = buf.size() > 1 ? *(buf.begin() + 1) : 0;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr complex<T>::complex(const complex<U>& x) {
		re = x.re;
		im = x.im;
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const complex<T> complex<T>::comp() const {
		return complex<T>(re, -1 * im);
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] inline const auto complex<T>::norm() const {
		return sqrt(re * re + im * im);
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] inline const auto complex<T>::snorm() const {
		return im == 0 ? abs(re) * re : norm() * sgn(im);
	}
	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] inline const auto complex<T>::arg() const {
		return im == 0 ? re < 0 ? M_PI : 0 : re == 0 ? M_PI_2 * (2 - sgn(im)) : atan2(im, re);
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator==(const complex<U>& x) const {
		return re == x.re && im == x.im;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator!=(const complex<U>& x) const {
		return !(*this == x);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator<(const complex<U>& x) const {
		return snorm() == x.snorm() ? arg() < x.arg() : snorm() < x.snorm();
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator>(const complex<U>& x) const {
		return x < *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator<=(const complex<U>& x) const {
		return !(x < *this);
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool complex<T>::operator>=(const complex<U>& x) const {
		return !(*this < x);
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator=(const U& x) {
		re = x;
		im = 0;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator=(const complex<U>& x) {
		re = x.re;
		im = x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator+=(const U& x) {
		re += x;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator+=(const complex<U>& x) {
		re += x.re;
		im += x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator-=(const U& x) {
		re -= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator-=(const complex<U>& x) {
		re -= x.re;
		im -= x.im;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator*=(const U& x) {
		re *= x;
		im *= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator*=(const complex<U>& x) {
		T tmp = re * x.re - im * x.im;
		im = re * x.im + x.re * im;
		re = tmp;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator/=(const U& x) {
		re /= x;
		im /= x;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API constexpr inline complex<T>& complex<T>::operator/=(const complex<U>& x) {
		T tmp = (x.re * re + x.im * im) / (x.re * x.re + x.im * x.im);
		im = (x.re * im - re * x.im) / (x.re * x.re + x.im * x.im);
		re = tmp;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator+(const U& x) const {
		using V = decltype(T() + U());
		complex<V> res(re + x, im);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator+(const complex<U>& x) const {
		using V = decltype(T() + U());
		complex<V> res(re + x.re, im + x.im);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator-(const U& x) const {
		using V = decltype(T() - U());
		complex<V> res(re - x, im);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator-(const complex<U>& x) const {
		using V = decltype(T() - U());
		complex<V> res(re - x.re, im - x.im);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator*(const U& x) const {
		using V = decltype(T()* U());
		complex<V> res(re * x, im * x);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator*(const complex<U>& x) const {
		using V = decltype(T()* U());
		complex<V> res(re * x.re - im * x.im, re * x.im + x.re * im);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator/(const U& x) const {
		using V = decltype(T() / U());
		complex<V> res(re / x, im / x);
		return res;
	}
	template<typename T>
	template<typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto complex<T>::operator/(const complex<U>& x) const {
		using V = decltype(T() / U());
		complex<V> res((x.re * re + x.im * im) / (x.re * x.re + x.im * x.im), (x.re * im - re * x.im) / (x.re * x.re + x.im * x.im));
		return res;
	}

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator+(const T& x, const complex<U>& y) {
		using V = decltype(T() + U());
		complex<V> res(x + y.re, y.im);
		return res;
	}
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator-(const T& x, const complex<U>& y) {
		using V = decltype(T() - U());
		complex<V> res(x - y.re, -y.im);
		return res;
	}
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator*(const T& x, const complex<U>& y) {
		using V = decltype(T()* U());
		complex<V> res(x * y.re, x * y.im);
		return res;
	}
	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto operator/(const T& x, const complex<U>& y) {
		using V = decltype(T() / U());
		complex<V> res(x * y.re / y.norm(), -x * y.im / y.norm());
		return res;
	}

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxFromPolar(const T& r, const U& theta) {
		complex<T> res(r * cos(theta), r * sin(theta));
		return res;
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxSqrt(const complex<T>& x) {
		return cxFromPolar(sqrt(x.norm()), x.arg() / 2);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxCbrt(const complex<T>& x) {
		return cxFromPolar(cbrt(x.norm()), x.arg() / 3);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto abs(const complex<T>& x) {
		return x.norm();
	}

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const complex<T>& b, const U& e) {
		return cxFromPolar(pow(b.norm(), e), b.arg() * e);
	}

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const T& b, const complex<U>& e) {
		return complex<U>(cos(e.im), sin(e.im)) * pow(b, e.re);
	}

	template<typename T, typename U>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cxPow(const complex<T>& b, const complex<U>& e) {
		return complex<U>(cos(e.im), sin(e.im)) * cxPow(b, e.re);
	}
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto exp(const math::complex<T>& x) {
	return (math::complex<T>::i * sin(x.im) + cos(x.im)) * exp(x.re);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sqrt(const math::complex<T>& x) {
	return math::cxSqrt(x);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cbrt(const math::complex<T>& x) {
	return math::cxCbrt(x);
}

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const math::complex<T>& b, const U& e) {
	return math::cxPow(b, e);
}

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const T& b, const math::complex<U>& e) {
	return math::cxPow(b, e);
}

template<typename T, typename U>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto pow(const math::complex<T>& b, const math::complex<U>& e) {
	return math::cxPow(b, e);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log(const math::complex<T>& x) {
	return log(x.norm()) + math::complex<T>::i * x.arg();
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log2(const math::complex<T>& x) {
	return log(x) / log(2);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto log10(const math::complex<T>& x) {
	return log(x) / log(10);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sin(const math::complex<T>& x) {
	return sin(x.re) * cosh(x.im) + math::complex<T>::i * cos(x.re) * sinh(x.im);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cos(const math::complex<T>& x) {
	return cos(x.re) * cosh(x.im) - math::complex<T>::i * sin(x.re) * sinh(x.im);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto tan(const math::complex<T>& x) {
	return sin(x) / cos(x);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asin(const math::complex<T>& x) {
	return -math::complex<T>::i * log(math::complex<T>::i * x + math::cxSqrt(1 - x * x));
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acos(const math::complex<T>& x) {
	return -math::complex<T>::i * log(x + math::cxSqrt(x * x - 1));
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto atan(const math::complex<T>& x) {
	return -0.5 * math::complex<T>::i * (log(math::complex<T>::i - x) - log(math::complex<T>::i + x));
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sinh(const math::complex<T>& x) {
	return sinh(x.re) * cos(x.im) + math::complex<T>::i * cosh(x.re) * sin(x.im);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto cosh(const math::complex<T>& x) {
	return cosh(x.re) * cos(x.im) + math::complex<T>::i * sinh(x.re) * sin(x.im);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto tanh(const math::complex<T>& x) {
	return sinh(x) / cosh(x);
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asinh(const math::complex<T>& x) {
	return log(x * math::cxSqrt(x * x + 1));
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acosh(const math::complex<T>& x) {
	return log(x + math::cxSqrt(x * x - 1));
}

template<typename T>
MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto atanh(const math::complex<T>& x) {
	return 0.5 * (log(1 + x) - log(1 - x));
}

namespace std {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const string to_string(const math::complex<T>& x) {
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
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::complex<T>& x) {
	if (x.re != 0 || x.im == 0) os << x.re;
	if (x.re != 0 && x.im > 0) os << "+";
	if (x.im < 0) os << "-";
	if (x.im != 0 && x.im != 1 && x.im != -1) os << abs(x.im);
	if (x.im != 0) os << "i";
	return os;
}
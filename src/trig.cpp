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

#include "trig.h"

namespace math {

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto ctg(const T& x) {
		return cos(x) / sin(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sec(const T& x) {
		return 1.0 / cos(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto csc(const T& x) {
		return 1.0 / sin(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto actg(const T& x) {
		return atan(1.0 / x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asec(const T& x) {
		return acos(1.0 / x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acsc(const T& x) {
		return asin(1.0 / x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto ctgh(const T& x) {
		return 1.0 / tanh(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto sech(const T& x) {
		return 1.0 / cosh(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto csch(const T& x) {
		return 1.0 / sinh(x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto actgh(const T& x) {
		return atanh(1.0 / x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto asech(const T& x) {
		return acosh(1.0 / x);
	}

	template<typename T>
	MATHPLUSPLUS_API [[nodiscard]] constexpr inline const auto acsch(const T& x) {
		return asinh(1.0 / x);
	}
}
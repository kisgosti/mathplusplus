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

#include <array>
#include <iostream>

namespace math {

	class uint128_t {
	private:
		std::array<uint32_t, 4> buf;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		MATHPLUSPLUS_API constexpr uint128_t();
		MATHPLUSPLUS_API constexpr uint128_t(const uint64_t& x);
		MATHPLUSPLUS_API constexpr uint128_t(const uint128_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<=(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>=(const uint128_t& x) const;

		MATHPLUSPLUS_API constexpr inline uint128_t& operator=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator|=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator^=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator&=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator>>=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator<<=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator+=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator-=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator*=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator/=(const uint128_t& x);
		MATHPLUSPLUS_API constexpr inline uint128_t& operator%=(const uint128_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator|(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator^(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator&(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator>>(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator<<(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator+(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator-(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator*(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator/(const uint128_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint128_t operator%(const uint128_t& x) const;

		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint64_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint32_t() const;

		friend class uint256_t;
		friend class uint512_t;
		friend class uint1024_t;
	};

	class uint256_t {
	private:
		std::array<uint32_t, 8> buf;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		MATHPLUSPLUS_API constexpr uint256_t();
		MATHPLUSPLUS_API constexpr uint256_t(const uint64_t& x);
		MATHPLUSPLUS_API constexpr uint256_t(const uint128_t& x);
		MATHPLUSPLUS_API constexpr uint256_t(const uint256_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<=(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>=(const uint256_t& x) const;

		MATHPLUSPLUS_API constexpr inline uint256_t& operator=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator|=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator^=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator&=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator>>=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator<<=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator+=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator-=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator*=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator/=(const uint256_t& x);
		MATHPLUSPLUS_API constexpr inline uint256_t& operator%=(const uint256_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator|(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator^(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator&(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator>>(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator<<(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator+(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator-(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator*(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator/(const uint256_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint256_t operator%(const uint256_t& x) const;

		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint128_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint64_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint32_t() const;

		friend class uint512_t;
		friend class uint1024_t;
	};

	class uint512_t {
	private:
		std::array<uint32_t, 16> buf;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		MATHPLUSPLUS_API constexpr uint512_t();
		MATHPLUSPLUS_API constexpr uint512_t(const uint64_t& x);
		MATHPLUSPLUS_API constexpr uint512_t(const uint128_t& x);
		MATHPLUSPLUS_API constexpr uint512_t(const uint256_t& x);
		MATHPLUSPLUS_API constexpr uint512_t(const uint512_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<=(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>=(const uint512_t& x) const;

		MATHPLUSPLUS_API constexpr inline uint512_t& operator=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator|=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator^=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator&=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator>>=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator<<=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator+=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator-=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator*=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator/=(const uint512_t& x);
		MATHPLUSPLUS_API constexpr inline uint512_t& operator%=(const uint512_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator|(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator^(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator&(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator>>(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator<<(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator+(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator-(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator*(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator/(const uint512_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint512_t operator%(const uint512_t& x) const;

		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint256_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint128_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint64_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint32_t() const;

		friend class uint1024_t;
	};

	class uint1024_t {
	private:
		std::array<uint32_t, 32> buf;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		MATHPLUSPLUS_API constexpr uint1024_t();
		MATHPLUSPLUS_API constexpr uint1024_t(const uint64_t& x);
		MATHPLUSPLUS_API constexpr uint1024_t(const uint128_t& x);
		MATHPLUSPLUS_API constexpr uint1024_t(const uint256_t& x);
		MATHPLUSPLUS_API constexpr uint1024_t(const uint512_t& x);
		MATHPLUSPLUS_API constexpr uint1024_t(const uint1024_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator==(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator!=(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator<=(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const bool operator>=(const uint1024_t& x) const;

		MATHPLUSPLUS_API constexpr inline uint1024_t& operator=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator|=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator^=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator&=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator>>=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator<<=(const int& n);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator+=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator-=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator*=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator/=(const uint1024_t& x);
		MATHPLUSPLUS_API constexpr inline uint1024_t& operator%=(const uint1024_t& x);

		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator|(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator^(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator&(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator>>(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator<<(const int& n) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator+(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator-(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator*(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator/(const uint1024_t& x) const;
		MATHPLUSPLUS_API [[nodiscard]] constexpr inline const uint1024_t operator%(const uint1024_t& x) const;

		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint512_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint256_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint128_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint64_t() const;
		MATHPLUSPLUS_API [[nodiscard]] explicit operator uint32_t() const;
	};
}

namespace std {

	MATHPLUSPLUS_API [[nodiscard]] const string to_string(const math::uint128_t& x);
	MATHPLUSPLUS_API [[nodiscard]] const string to_string(const math::uint256_t& x);
	MATHPLUSPLUS_API [[nodiscard]] const string to_string(const math::uint512_t& x);
	MATHPLUSPLUS_API [[nodiscard]] const string to_string(const math::uint1024_t& x);
}

MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::uint128_t& x);
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::uint256_t& x);
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::uint512_t& x);
MATHPLUSPLUS_API inline std::ostream& operator<<(std::ostream& os, const math::uint1024_t& x);

#undef	UINT128_MAX
#define	UINT128_MAX			(static_cast<math::uint128_t>0 - 1)
#define	UINT256_MAX			(static_cast<math::uint256_t>0 - 1)
#define	UINT512_MAX			(static_cast<math::uint512_t>0 - 1)
#define	UINT1024_MAX		(static_cast<math::uint1024_t>0 - 1)
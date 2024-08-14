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

#include <array>
#include <iostream>

namespace math {

	class MATHPLUSPLUS_API uint128_t {
	private:
		std::array<uint32_t, 4> buf;
		_NODISCARD constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		constexpr uint128_t();
		constexpr uint128_t(const uint64_t& x);
		constexpr uint128_t(const uint128_t& x);

		_NODISCARD constexpr inline const bool operator==(const uint128_t& x) const;
		_NODISCARD constexpr inline const bool operator!=(const uint128_t& x) const;
		_NODISCARD constexpr inline const bool operator<(const uint128_t& x) const;
		_NODISCARD constexpr inline const bool operator>(const uint128_t& x) const;
		_NODISCARD constexpr inline const bool operator<=(const uint128_t& x) const;
		_NODISCARD constexpr inline const bool operator>=(const uint128_t& x) const;

		constexpr inline uint128_t& operator=(const uint128_t& x);
		constexpr inline uint128_t& operator|=(const uint128_t& x);
		constexpr inline uint128_t& operator^=(const uint128_t& x);
		constexpr inline uint128_t& operator&=(const uint128_t& x);
		constexpr inline uint128_t& operator>>=(const int& n);
		constexpr inline uint128_t& operator<<=(const int& n);
		constexpr inline uint128_t& operator+=(const uint128_t& x);
		constexpr inline uint128_t& operator-=(const uint128_t& x);
		constexpr inline uint128_t& operator*=(const uint128_t& x);
		constexpr inline uint128_t& operator/=(const uint128_t& x);
		constexpr inline uint128_t& operator%=(const uint128_t& x);

		_NODISCARD constexpr inline const uint128_t operator|(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator^(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator&(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator>>(const int& n) const;
		_NODISCARD constexpr inline const uint128_t operator<<(const int& n) const;
		_NODISCARD constexpr inline const uint128_t operator+(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator-(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator*(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator/(const uint128_t& x) const;
		_NODISCARD constexpr inline const uint128_t operator%(const uint128_t& x) const;

		_NODISCARD operator uint64_t();
		_NODISCARD operator uint32_t();

		friend class uint256_t;
		friend class uint512_t;
		friend class uint1024_t;
	};

	class MATHPLUSPLUS_API uint256_t {
	private:
		std::array<uint32_t, 8> buf;
		_NODISCARD constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		constexpr uint256_t();
		constexpr uint256_t(const uint64_t& x);
		constexpr uint256_t(const uint128_t& x);
		constexpr uint256_t(const uint256_t& x);

		_NODISCARD constexpr inline const bool operator==(const uint256_t& x) const;
		_NODISCARD constexpr inline const bool operator!=(const uint256_t& x) const;
		_NODISCARD constexpr inline const bool operator<(const uint256_t& x) const;
		_NODISCARD constexpr inline const bool operator>(const uint256_t& x) const;
		_NODISCARD constexpr inline const bool operator<=(const uint256_t& x) const;
		_NODISCARD constexpr inline const bool operator>=(const uint256_t& x) const;

		constexpr inline uint256_t& operator=(const uint256_t& x);
		constexpr inline uint256_t& operator|=(const uint256_t& x);
		constexpr inline uint256_t& operator^=(const uint256_t& x);
		constexpr inline uint256_t& operator&=(const uint256_t& x);
		constexpr inline uint256_t& operator>>=(const int& n);
		constexpr inline uint256_t& operator<<=(const int& n);
		constexpr inline uint256_t& operator+=(const uint256_t& x);
		constexpr inline uint256_t& operator-=(const uint256_t& x);
		constexpr inline uint256_t& operator*=(const uint256_t& x);
		constexpr inline uint256_t& operator/=(const uint256_t& x);
		constexpr inline uint256_t& operator%=(const uint256_t& x);

		_NODISCARD constexpr inline const uint256_t operator|(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator^(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator&(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator>>(const int& n) const;
		_NODISCARD constexpr inline const uint256_t operator<<(const int& n) const;
		_NODISCARD constexpr inline const uint256_t operator+(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator-(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator*(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator/(const uint256_t& x) const;
		_NODISCARD constexpr inline const uint256_t operator%(const uint256_t& x) const;

		_NODISCARD operator uint128_t();
		_NODISCARD operator uint64_t();
		_NODISCARD operator uint32_t();

		friend class uint512_t;
		friend class uint1024_t;
	};

	class MATHPLUSPLUS_API uint512_t {
	private:
		std::array<uint32_t, 16> buf;
		_NODISCARD constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		constexpr uint512_t();
		constexpr uint512_t(const uint64_t& x);
		constexpr uint512_t(const uint128_t& x);
		constexpr uint512_t(const uint256_t& x);
		constexpr uint512_t(const uint512_t& x);

		_NODISCARD constexpr inline const bool operator==(const uint512_t& x) const;
		_NODISCARD constexpr inline const bool operator!=(const uint512_t& x) const;
		_NODISCARD constexpr inline const bool operator<(const uint512_t& x) const;
		_NODISCARD constexpr inline const bool operator>(const uint512_t& x) const;
		_NODISCARD constexpr inline const bool operator<=(const uint512_t& x) const;
		_NODISCARD constexpr inline const bool operator>=(const uint512_t& x) const;

		constexpr inline uint512_t& operator=(const uint512_t& x);
		constexpr inline uint512_t& operator|=(const uint512_t& x);
		constexpr inline uint512_t& operator^=(const uint512_t& x);
		constexpr inline uint512_t& operator&=(const uint512_t& x);
		constexpr inline uint512_t& operator>>=(const int& n);
		constexpr inline uint512_t& operator<<=(const int& n);
		constexpr inline uint512_t& operator+=(const uint512_t& x);
		constexpr inline uint512_t& operator-=(const uint512_t& x);
		constexpr inline uint512_t& operator*=(const uint512_t& x);
		constexpr inline uint512_t& operator/=(const uint512_t& x);
		constexpr inline uint512_t& operator%=(const uint512_t& x);

		_NODISCARD constexpr inline const uint512_t operator|(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator^(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator&(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator>>(const int& n) const;
		_NODISCARD constexpr inline const uint512_t operator<<(const int& n) const;
		_NODISCARD constexpr inline const uint512_t operator+(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator-(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator*(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator/(const uint512_t& x) const;
		_NODISCARD constexpr inline const uint512_t operator%(const uint512_t& x) const;

		_NODISCARD operator uint256_t();
		_NODISCARD operator uint128_t();
		_NODISCARD operator uint64_t();
		_NODISCARD operator uint32_t();

		friend class uint1024_t;
	};

	class MATHPLUSPLUS_API uint1024_t {
	private:
		std::array<uint32_t, 32> buf;
		_NODISCARD constexpr inline const uint32_t operator[](int16_t n) const;
	public:
		constexpr uint1024_t();
		constexpr uint1024_t(const uint64_t& x);
		constexpr uint1024_t(const uint128_t& x);
		constexpr uint1024_t(const uint256_t& x);
		constexpr uint1024_t(const uint512_t& x);
		constexpr uint1024_t(const uint1024_t& x);

		_NODISCARD constexpr inline const bool operator==(const uint1024_t& x) const;
		_NODISCARD constexpr inline const bool operator!=(const uint1024_t& x) const;
		_NODISCARD constexpr inline const bool operator<(const uint1024_t& x) const;
		_NODISCARD constexpr inline const bool operator>(const uint1024_t& x) const;
		_NODISCARD constexpr inline const bool operator<=(const uint1024_t& x) const;
		_NODISCARD constexpr inline const bool operator>=(const uint1024_t& x) const;

		constexpr inline uint1024_t& operator=(const uint1024_t& x);
		constexpr inline uint1024_t& operator|=(const uint1024_t& x);
		constexpr inline uint1024_t& operator^=(const uint1024_t& x);
		constexpr inline uint1024_t& operator&=(const uint1024_t& x);
		constexpr inline uint1024_t& operator>>=(const int& n);
		constexpr inline uint1024_t& operator<<=(const int& n);
		constexpr inline uint1024_t& operator+=(const uint1024_t& x);
		constexpr inline uint1024_t& operator-=(const uint1024_t& x);
		constexpr inline uint1024_t& operator*=(const uint1024_t& x);
		constexpr inline uint1024_t& operator/=(const uint1024_t& x);
		constexpr inline uint1024_t& operator%=(const uint1024_t& x);

		_NODISCARD constexpr inline const uint1024_t operator|(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator^(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator&(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator>>(const int& n) const;
		_NODISCARD constexpr inline const uint1024_t operator<<(const int& n) const;
		_NODISCARD constexpr inline const uint1024_t operator+(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator-(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator*(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator/(const uint1024_t& x) const;
		_NODISCARD constexpr inline const uint1024_t operator%(const uint1024_t& x) const;

		_NODISCARD operator uint512_t();
		_NODISCARD operator uint256_t();
		_NODISCARD operator uint128_t();
		_NODISCARD operator uint64_t();
		_NODISCARD operator uint32_t();
	};
}

std::ostream& operator<<(std::ostream& os, const math::uint128_t& x);

#undef	UINT128_MAX
#define	UINT128_MAX			(static_cast<math::uint128_t>0 - 1)
#define	UINT256_MAX			(static_cast<math::uint256_t>0 - 1)
#define	UINT512_MAX			(static_cast<math::uint512_t>0 - 1)
#define	UINT1024_MAX		(static_cast<math::uint1024_t>0 - 1)
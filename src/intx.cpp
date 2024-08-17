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

#include "intx.h"

#include <string>
#include <stdint.h>

namespace math {
	
	[[nodiscard]] constexpr inline const uint32_t uint128_t::operator[](int16_t n) const {
		return 0 <= n && n < 4 ? buf[n] : 0;
	}
	constexpr uint128_t::uint128_t() : buf({ 0 }) {}
	constexpr uint128_t::uint128_t(const uint64_t& x) : buf{ 0, 0, static_cast<uint32_t>(x >> 32), static_cast<uint32_t>(x) } {}
	constexpr uint128_t::uint128_t(const uint128_t& x) : buf(x.buf) {}

	[[nodiscard]] constexpr inline const bool uint128_t::operator==(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return false;
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint128_t::operator!=(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return true;
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint128_t::operator<(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint128_t::operator>(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint128_t::operator<=(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint128_t::operator>=(const uint128_t& x) const {
		for (short i = 0; i < 4; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return true;
	}
	constexpr inline uint128_t& uint128_t::operator=(const uint128_t& x) {
		for (short i = 0; i < 4; i++)
			buf[i] = x[i];
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator|=(const uint128_t& x) {
		for (short i = 0; i < 4; i++)
			buf[i] |= x[i];
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator^=(const uint128_t& x) {
		for (short i = 0; i < 4; i++)
			buf[i] ^= x[i];
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator&=(const uint128_t& x) {
		for (short i = 0; i < 4; i++)
			buf[i] &= x[i];
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator>>=(const int& n) {
		for (short i = 0; i < 4; i++)
			buf[i] = (buf[i - (n >> 3)] >> (n % 8)) | (buf[i + 1 - (n >> 3)] << (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator<<=(const int& n) {
		for (short i = 0; i < 4; i++)
			buf[i] = (buf[i + (n >> 3)] << (n % 8)) | (buf[i + 1 + (n >> 3)] >> (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator+=(const uint128_t& x) {
		uint64_t tmp = 0;
		for (short i = 3; i >= 0; i--) {
			tmp += buf[i] + x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator-=(const uint128_t& x) {
		uint64_t tmp = 0;
		for (short i = 3; i >= 0; i--) {
			tmp = tmp + 0xffffffff + buf[i] - x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator*=(const uint128_t& x) {
		uint64_t tmp = 0;
		for (short i = 3; i >= 0; i--) {
			for (short j = 0; j <= i; j++)
				tmp += (uint64_t)buf[3 - j] * (uint64_t)x[3 - i + j];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint128_t& uint128_t::operator/=(const uint128_t& x) {
		uint128_t res, one = 1;
		int16_t s = 0, m = 63, e = 127;
		while (e > 0) {
			uint128_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = res | (one << m);
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		return *this = res;
	}
	constexpr inline uint128_t& uint128_t::operator%=(const uint128_t& x) {
		uint128_t res, one = 1;
		int16_t s = 0, m = 63, e = 127;
		while (e > 0) {
			uint128_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = 0;
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		res *= x;
		return *this -= res;
	}

	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator|(const uint128_t& x) const {
		uint128_t res(*this);
		res |= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator^(const uint128_t& x) const {
		uint128_t res(*this);
		res ^= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator&(const uint128_t& x) const {
		uint128_t res(*this);
		res &= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator>>(const int& n) const {
		uint128_t res(*this);
		res >>= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator<<(const int& n) const {
		uint128_t res(*this);
		res <<= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator+(const uint128_t& x) const {
		uint128_t res(*this);
		res += x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator-(const uint128_t& x) const {
		uint128_t res(*this);
		res -= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator*(const uint128_t& x) const {
		uint128_t res(*this);
		res *= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator/(const uint128_t& x) const {
		uint128_t res(*this);
		res /= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint128_t uint128_t::operator%(const uint128_t& x) const {
		uint128_t res(*this);
		res %= x;
		return res;
	}

	[[nodiscard]] uint128_t::operator uint64_t() const {
		return ((uint64_t)buf[2] << 32) | buf[3];
	}
	[[nodiscard]] uint128_t::operator uint32_t() const {
		return buf[3];
	}

	[[nodiscard]] constexpr inline const uint32_t uint256_t::operator[](int16_t n) const {
		return 0 <= n && n < 8 ? buf[n] : 0;
	}
	constexpr uint256_t::uint256_t() : buf({ 0 }) {}
	constexpr uint256_t::uint256_t(const uint64_t& x) : buf{ 0, 0, 0, 0, 0, 0, static_cast<uint32_t>(x >> 32), static_cast<uint32_t>(x) } {}
	constexpr uint256_t::uint256_t(const uint128_t& x) : buf({ 0 }) {
		for (short i = 0; i < 4; i++)
			buf[4 + i] = x[i];
	}
	constexpr uint256_t::uint256_t(const uint256_t& x) : buf(x.buf) {}

	[[nodiscard]] constexpr inline const bool uint256_t::operator==(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return false;
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint256_t::operator!=(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return true;
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint256_t::operator<(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint256_t::operator>(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint256_t::operator<=(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint256_t::operator>=(const uint256_t& x) const {
		for (short i = 0; i < 8; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return true;
	}

	constexpr inline uint256_t& uint256_t::operator=(const uint256_t& x) {
		buf = x.buf;
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator|=(const uint256_t& x) {
		for (short i = 0; i < 8; i++)
			buf[i] |= x[i];
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator^=(const uint256_t& x) {
		for (short i = 0; i < 8; i++)
			buf[i] ^= x[i];
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator&=(const uint256_t& x) {
		for (short i = 0; i < 8; i++)
			buf[i] &= x[i];
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator>>=(const int& n) {
		for (short i = 0; i < 8; i++)
			buf[i] = (buf[i - (n >> 3)] >> (n % 8)) | (buf[i + 1 - (n >> 3)] << (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator<<=(const int& n) {
		for (short i = 0; i < 8; i++)
			buf[i] = (buf[i + (n >> 3)] << (n % 8)) | (buf[i + 1 + (n >> 3)] >> (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator+=(const uint256_t& x) {
		uint64_t tmp = 0;
		for (short i = 7; i >= 0; i--) {
			tmp += buf[i] + x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator-=(const uint256_t& x) {
		uint64_t tmp = 0;
		for (short i = 7; i >= 0; i--) {
			tmp = tmp + 0xffffffff + buf[i] - x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator*=(const uint256_t& x) {
		uint64_t tmp = 0;
		for (short i = 7; i >= 0; i--) {
			for (short j = 0; j <= i; j++)
				tmp += (uint64_t)buf[7 - j] * (uint64_t)x[7 - i + j];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint256_t& uint256_t::operator/=(const uint256_t& x) {
		uint256_t res, one = 1;
		int16_t s = 0, m = 127, e = 255;
		while (e > 0) {
			uint256_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = res | (one << m);
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		return *this = res;
	}
	constexpr inline uint256_t& uint256_t::operator%=(const uint256_t& x) {
		uint256_t res, one = 1;
		int16_t s = 0, m = 127, e = 255;
		while (e > 0) {
			uint256_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = 0;
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		res *= x;
		return *this -= res;
	}

	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator|(const uint256_t& x) const {
		uint256_t res(*this);
		res |= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator^(const uint256_t& x) const {
		uint256_t res(*this);
		res ^= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator&(const uint256_t& x) const {
		uint256_t res(*this);
		res &= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator>>(const int& n) const {
		uint256_t res(*this);
		res >>= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator<<(const int& n) const {
		uint256_t res(*this);
		res <<= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator+(const uint256_t& x) const {
		uint256_t res(*this);
		res += x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator-(const uint256_t& x) const {
		uint256_t res(*this);
		res -= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator*(const uint256_t& x) const {
		uint256_t res(*this);
		res *= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator/(const uint256_t& x) const {
		uint256_t res(*this);
		res /= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint256_t uint256_t::operator%(const uint256_t& x) const {
		uint256_t res(*this);
		res %= x;
		return res;
	}

	[[nodiscard]] uint256_t::operator uint128_t() const {
		uint128_t res;
		for (short i = 0; i < 4; i++)
			res.buf[i] = buf[i + 4];
		return res;
	}
	[[nodiscard]] uint256_t::operator uint64_t() const {
		return ((uint64_t)buf[6] << 32) | buf[7];
	}
	[[nodiscard]] uint256_t::operator uint32_t() const {
		return buf[7];
	}

	[[nodiscard]] constexpr inline const uint32_t  uint512_t::operator[](int16_t n) const {
		return 0 <= n && n < 16 ? buf[n] : 0;
	}
	constexpr uint512_t::uint512_t() : buf({ 0 }) {}
	constexpr uint512_t::uint512_t(const uint64_t& x) : buf{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, static_cast<uint32_t>(x >> 32), static_cast<uint32_t>(x) } {}
	constexpr uint512_t::uint512_t(const uint128_t& x) : buf({ 0 }) {
		for (short i = 0; i < 4; i++)
			buf[12 + i] = x[i];
	}
	constexpr uint512_t::uint512_t(const uint256_t& x) : buf({ 0 }) {
		for (short i = 0; i < 8; i++)
			buf[8 + i] = x[i];
	}
	constexpr uint512_t::uint512_t(const uint512_t& x) : buf(x.buf) {}

	[[nodiscard]] constexpr inline const bool uint512_t::operator==(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return false;
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint512_t::operator!=(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return true;
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint512_t::operator<(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint512_t::operator>(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint512_t::operator<=(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint512_t::operator>=(const uint512_t& x) const {
		for (short i = 0; i < 16; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return true;
	}

	constexpr inline uint512_t& uint512_t::operator=(const uint512_t& x) {
		buf = x.buf;
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator|=(const uint512_t& x) {
		for (short i = 0; i < 16; i++)
			buf[i] |= x[i];
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator^=(const uint512_t& x) {
		for (short i = 0; i < 16; i++)
			buf[i] ^= x[i];
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator&=(const uint512_t& x) {
		for (short i = 0; i < 16; i++)
			buf[i] &= x[i];
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator>>=(const int& n) {
		for (short i = 0; i < 16; i++)
			buf[i] = (buf[i - (n >> 3)] >> (n % 8)) | (buf[i + 1 - (n >> 3)] << (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator<<=(const int& n) {
		for (short i = 0; i < 16; i++)
			buf[i] = (buf[i + (n >> 3)] << (n % 8)) | (buf[i + 1 + (n >> 3)] >> (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator+=(const uint512_t& x) {
		uint64_t tmp = 0;
		for (short i = 15; i >= 0; i--) {
			tmp += buf[i] + x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator-=(const uint512_t& x) {
		uint64_t tmp = 0;
		for (short i = 15; i >= 0; i--) {
			tmp = tmp + 0xffffffff + buf[i] - x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator*=(const uint512_t& x) {
		uint64_t tmp = 0;
		for (short i = 15; i >= 0; i--) {
			for (short j = 0; j <= i; j++)
				tmp += (uint64_t)buf[3 - j] * (uint64_t)x[3 - i + j];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint512_t& uint512_t::operator/=(const uint512_t& x) {
		uint512_t res, one = 1;
		int16_t s = 0, m = 255, e = 511;
		while (e > 0) {
			uint512_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = res | (one << m);
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		return *this = res;
	}
	constexpr inline uint512_t& uint512_t::operator%=(const uint512_t& x) {
		uint512_t res, one = 1;
		int16_t s = 0, m = 255, e = 511;
		while (e > 0) {
			uint512_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = 0;
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		res *= x;
		return *this -= res;
	}

	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator|(const uint512_t& x) const {
		uint512_t res(*this);
		res |= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator^(const uint512_t& x) const {
		uint512_t res(*this);
		res ^= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator&(const uint512_t& x) const {
		uint512_t res(*this);
		res &= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator>>(const int& n) const {
		uint512_t res(*this);
		res >>= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator<<(const int& n) const {
		uint512_t res(*this);
		res <<= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator+(const uint512_t& x) const {
		uint512_t res(*this);
		res += x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator-(const uint512_t& x) const {
		uint512_t res(*this);
		res -= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator*(const uint512_t& x) const {
		uint512_t res(*this);
		res *= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator/(const uint512_t& x) const {
		uint512_t res(*this);
		res /= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint512_t uint512_t::operator%(const uint512_t& x) const {
		uint512_t res(*this);
		res %= x;
		return res;
	}

	[[nodiscard]] uint512_t::operator uint256_t() const {
		uint256_t res;
		for (short i = 0; i < 8; i++)
			res.buf[i] = buf[i + 8];
		return res;
	}
	[[nodiscard]] uint512_t::operator uint128_t() const {
		uint128_t res;
		for (short i = 0; i < 4; i++)
			res.buf[i] = buf[i + 12];
		return res;
	}
	[[nodiscard]] uint512_t::operator uint64_t() const {
		return ((uint64_t)buf[14] << 32) | buf[15];
	}
	[[nodiscard]] uint512_t::operator uint32_t() const {
		return buf[15];
	}

	[[nodiscard]] constexpr inline const uint32_t uint1024_t::operator[](int16_t n) const {
		return 0 <= n && n < 32 ? buf[n] : 0;
	}
	constexpr uint1024_t::uint1024_t() : buf({ 0 }) {}
	constexpr uint1024_t::uint1024_t(const uint64_t& x) : buf{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, static_cast<uint32_t>(x >> 32), static_cast<uint32_t>(x) } {}
	constexpr uint1024_t::uint1024_t(const uint128_t& x) : buf({ 0 }) {
		for (short i = 0; i < 4; i++)
			buf[28 + i] = x[i];
	}
	constexpr uint1024_t::uint1024_t(const uint256_t& x) : buf({ 0 }) {
		for (short i = 0; i < 8; i++)
			buf[24 + i] = x[i];
	}
	constexpr uint1024_t::uint1024_t(const uint512_t& x) : buf({ 0 }) {
		for (short i = 0; i < 16; i++)
			buf[16 + i] = x[i];
	}
	constexpr uint1024_t::uint1024_t(const uint1024_t& x) : buf(x.buf) {}

	[[nodiscard]] constexpr inline const bool uint1024_t::operator==(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return false;
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint1024_t::operator!=(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return true;
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint1024_t::operator<(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint1024_t::operator>(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return false;
	}
	[[nodiscard]] constexpr inline const bool uint1024_t::operator<=(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return buf[i] < x[i];
		return true;
	}
	[[nodiscard]] constexpr inline const bool uint1024_t::operator>=(const uint1024_t& x) const {
		for (short i = 0; i < 32; i++)
			if (buf[i] != x[i]) return buf[i] > x[i];
		return true;
	}

	constexpr inline uint1024_t& uint1024_t::operator=(const uint1024_t& x) {
		buf = x.buf;
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator|=(const uint1024_t& x) {
		for (short i = 0; i < 32; i++)
			buf[i] |= x[i];
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator^=(const uint1024_t& x) {
		for (short i = 0; i < 32; i++)
			buf[i] ^= x[i];
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator&=(const uint1024_t& x) {
		for (short i = 0; i < 32; i++)
			buf[i] &= x[i];
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator>>=(const int& n) {
		for (short i = 0; i < 32; i++)
			buf[i] = (buf[i - (n >> 3)] >> (n % 8)) | (buf[i + 1 - (n >> 3)] << (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator<<=(const int& n) {
		for (short i = 0; i < 32; i++)
			buf[i] = (buf[i + (n >> 3)] << (n % 8)) | (buf[i + 1 + (n >> 3)] >> (8 - (n % 8)));
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator+=(const uint1024_t& x) {
		uint64_t tmp = 0;
		for (short i = 31; i >= 0; i--) {
			tmp += buf[i] + x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator-=(const uint1024_t& x) {
		uint64_t tmp = 0;
		for (short i = 31; i >= 0; i--) {
			tmp = tmp + 0xffffffff + buf[i] - x[i];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator*=(const uint1024_t& x) {
		uint64_t tmp = 0;
		for (short i = 31; i >= 0; i--) {
			for (short j = 0; j <= i; j++)
				tmp += (uint64_t)buf[3 - j] * (uint64_t)x[3 - i + j];
			buf[i] = tmp & 0xffffffff;
			tmp >>= 32;
		}
		return *this;
	}
	constexpr inline uint1024_t& uint1024_t::operator/=(const uint1024_t& x) {
		uint1024_t res, one = 1;
		int16_t s = 0, m = 511, e = 1023;
		while (e > 0) {
			uint1024_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = res | (one << m);
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		return *this = res;
	}
	constexpr inline uint1024_t& uint1024_t::operator%=(const uint1024_t& x) {
		uint1024_t res, one = 1;
		int16_t s = 0, m = 511, e = 1023;
		while (e > 0) {
			uint1024_t tmp = x;
			tmp *= res | (one << m);
			if (tmp == x) {
				*this = 0;
				return *this;
			}
			else if (tmp < x) {
				if (m + 1 == e) {
					s = 0;
					e--;
					m = e / 2;
					res |= one << m;
				}
				else {
					s = m;
					m = (e + s) / 2;
				}
			}
			else {
				e = m;
				m = (e + s) / 2;
			}
		}
		res *= x;
		return *this -= res;
	}

	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator|(const uint1024_t& x) const {
		uint1024_t res(*this);
		res |= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator^(const uint1024_t& x) const {
		uint1024_t res(*this);
		res ^= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator&(const uint1024_t& x) const {
		uint1024_t res(*this);
		res &= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator>>(const int& n) const {
		uint1024_t res(*this);
		res >>= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator<<(const int& n) const {
		uint1024_t res(*this);
		res <<= n;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator+(const uint1024_t& x) const {
		uint1024_t res(*this);
		res += x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator-(const uint1024_t& x) const {
		uint1024_t res(*this);
		res -= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator*(const uint1024_t& x) const {
		uint1024_t res(*this);
		res *= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator/(const uint1024_t& x) const {
		uint1024_t res(*this);
		res /= x;
		return res;
	}
	[[nodiscard]] constexpr inline const uint1024_t uint1024_t::operator%(const uint1024_t& x) const {
		uint1024_t res(*this);
		res %= x;
		return res;
	}

	[[nodiscard]] uint1024_t::operator uint512_t() const {
		uint256_t res;
		for (short i = 0; i < 16; i++)
			res.buf[i] = buf[i + 16];
		return res;
	}
	[[nodiscard]] uint1024_t::operator uint256_t() const {
		uint256_t res;
		for (short i = 0; i < 8; i++)
			res.buf[i] = buf[i + 24];
		return res;
	}
	[[nodiscard]] uint1024_t::operator uint128_t() const {
		uint128_t res;
		for (short i = 0; i < 4; i++)
			res.buf[i] = buf[i + 28];
		return res;
	}
	[[nodiscard]] uint1024_t::operator uint64_t() const {
		return ((uint64_t)buf[30] << 32) | buf[31];
	}
	[[nodiscard]] uint1024_t::operator uint32_t() const {
		return buf[31];
	}
}

namespace std {

	[[nodiscard]] const string to_string(const math::uint128_t& x) {
		if (x == 0) return "0";
		math::uint128_t tmp = x, s = 1;
		while (s < tmp)
			s *= 10;
		string res = "";
		while (tmp > 0) {
			res += (char)(((uint32_t)(tmp / s)) + '0');
			tmp %= s;
			s /= 10;
		}
		return res;
	}
	[[nodiscard]] const string to_string(const math::uint256_t& x) {
		if (x == 0) return "0";
		math::uint256_t tmp = x, s = 1;
		while (s < tmp)
			s *= 10;
		string res = "";
		while (tmp > 0) {
			res += (char)(((uint32_t)(tmp / s)) + '0');
			tmp %= s;
			s /= 10;
		}
		return res;
	}
	[[nodiscard]] const string to_string(const math::uint512_t& x) {
		if (x == 0) return "0";
		math::uint512_t tmp = x, s = 1;
		while (s < tmp)
			s *= 10;
		string res = "";
		while (tmp > 0) {
			res += (char)(((uint32_t)(tmp / s)) + '0');
			tmp %= s;
			s /= 10;
		}
		return res;
	}
	[[nodiscard]] const string to_string(const math::uint1024_t& x) {
		if (x == 0) return "0";
		math::uint1024_t tmp = x, s = 1;
		while (s < tmp)
			s *= 10;
		string res = "";
		while (tmp > 0) {
			res += (char)(((uint32_t)(tmp / s)) + '0');
			tmp %= s;
			s /= 10;
		}
		return res;
	}
}

inline std::ostream& operator<<(std::ostream& os, const math::uint128_t& x) {
	return os << std::to_string(x);
}
inline std::ostream& operator<<(std::ostream& os, const math::uint256_t& x) {
	return os << std::to_string(x);
}
inline std::ostream& operator<<(std::ostream& os, const math::uint512_t& x) {
	return os << std::to_string(x);
}
inline std::ostream& operator<<(std::ostream& os, const math::uint1024_t& x) {
	return os << std::to_string(x);
}

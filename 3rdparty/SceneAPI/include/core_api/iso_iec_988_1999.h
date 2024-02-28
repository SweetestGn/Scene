#pragma once

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
	// from ISO/IEC 988:1999 spec.

	// 7.18.1.1 Exact-width integer types.
	typedef __int8 int8_t;
	typedef __int16 int16_t;
	typedef __int32 int32_t;
	typedef __int64 int64_t;
	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;

	// 7.18.1.2 Minimum-width integer types.
	typedef int8_t int_least8_t;
	typedef int16_t int_least16_t;
	typedef int32_t int_least32_t;
	typedef int64_t int_least64_t;
	typedef uint8_t uint_least8_t;
	typedef uint16_t uint_least16_t;
	typedef uint32_t uint_least32_t;
	typedef uint64_t uint_least64_t;

	// 7.18.1.3 Fastest-width integer types.
	typedef int int_fast8_t;
	typedef int int_fast16_t;
	typedef int int_fast32_t;
	typedef int64_t int_fast64_t;
	typedef unsigned int uint_fast8_t;
	typedef unsigned int uint_fast16_t;
	typedef unsigned int uint_fast32_t;
	typedef uint64_t uint_fast64_t;

	// 7.18.1.4 Integer types capable of holding object pointers.
	using ::intptr_t;
	using ::uintptr_t;

	// 7.18.1.5 Greatest-width integer types.
	typedef int_least64_t intmax_t;
	typedef uint_least64_t uintmax_t;
#else
	#include <stdint.h>
#endif

#ifndef DJOEZEKE_JENCH_COMPILER_H
#define DJOEZEKE_JENCH_COMPILER_H

// clang-format off

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup language Standard Checks
 * @{
 */

// With the MSVC compilers, the value of __cplusplus is by default always "199611L"(C++98).
// To avoid that, the library instead references _MSVC_LANG which is always set a correct value.
// See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/ for more details.
#if defined(_MSVC_LANG) && !defined(__clang__)
    #define JENCH_CPLUSPLUS _MSVC_LANG
#else
    #define JENCH_CPLUSPLUS __cplusplus
#endif

// C++ language standard detection

#if !defined(JENCH_HAS_CXX_26) && !defined(JENCH_HAS_CXX_23) && !defined(JENCH_HAS_CXX_20)\
    && !defined(JENCH_HAS_CXX_17) && !defined(JENCH_HAS_CXX_14) && !defined(JENCH_HAS_CXX_11)
    #if (defined(JENCH_CPLUSPLUS) && JENCH_CPLUSPLUS > 202302L)
        #define JENCH_HAS_CXX_26
        #define JENCH_HAS_CXX_23
        #define JENCH_HAS_CXX_20
        #define JENCH_HAS_CXX_17
        #define JENCH_HAS_CXX_14
    #elif (defined(JENCH_CPLUSPLUS) && JENCH_CPLUSPLUS > 202002L)
        #define JENCH_HAS_CXX_23
        #define JENCH_HAS_CXX_20
        #define JENCH_HAS_CXX_17
        #define JENCH_HAS_CXX_14
    #elif (defined(JENCH_CPLUSPLUS) && JENCH_CPLUSPLUS > 201703L)
        #define JENCH_HAS_CXX_20
        #define JENCH_HAS_CXX_17
        #define JENCH_HAS_CXX_14
    #elif (defined(JENCH_CPLUSPLUS) && JENCH_CPLUSPLUS > 201402L)
        #define JENCH_HAS_CXX_17
        #define JENCH_HAS_CXX_14
    #elif (defined(JENCH_CPLUSPLUS) && JENCH_CPLUSPLUS > 201103L)
        #define JENCH_HAS_CXX_14
    #endif
    // Always specified because it is the minimal required version
    #define JENCH_HAS_CXX_11
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name  Compiler brand, like `MSVC`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define JENCH_COMPILER_IS(name) JENCH_COMPILER_IS_##name

/**
 * @brief   Checks if the compiler is of given brand and is newer than or equal
 *          to the passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name >= x.y.z.
 * @retval  false  otherwise.
 */
#define JENCH_COMPILER_SINCE(name, x, y, z)                                 \
  (JENCH_COMPILER_IS(name) && ((JENCH_COMPILER_VERSION_MAJOR > (x)) ||     \
                                ((JENCH_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((JENCH_COMPILER_VERSION_MINOR > (y)) ||   \
                                  ((JENCH_COMPILER_VERSION_MINOR == (y)) && \
                                   (JENCH_COMPILER_VERSION_PATCH >= (z)))))))

/**
 * @brief   Checks if  the compiler  is of  given brand and  is older  than the
 *          passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name < x.y.z.
 * @retval  false  otherwise.
 */
#define JENCH_COMPILER_BEFORE(name, x, y, z)                                \
  (JENCH_COMPILER_IS(name) && ((JENCH_COMPILER_VERSION_MAJOR < (x)) ||     \
                                ((JENCH_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((JENCH_COMPILER_VERSION_MINOR < (y)) ||   \
                                  ((JENCH_COMPILER_VERSION_MINOR == (y)) && \
                                   (JENCH_COMPILER_VERSION_PATCH < (z)))))))


/// Compiler is gcc
#if !defined(__GNUC__)
    #define JENCH_COMPILER_IS_GCC 0
#else
    #define JENCH_COMPILER_IS_GCC 1
    #define JENCH_COMPILER_VERSION_MAJOR __GNUC__
    #define JENCH_COMPILER_VERSION_MINOR __GNUC_MINOR__
    #define JENCH_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/// Compiler is clang
#if !defined(__clang__)
    #define JENCH_COMPILER_IS_CLANG 0
#elif JENCH_COMPILER_IS(GCC)
    #define JENCH_COMPILER_IS_CLANG 0
#else
    #define JENCH_COMPILER_IS_CLANG 1
    #define JENCH_COMPILER_VERSION_MAJOR __clang_major__
    #define JENCH_COMPILER_VERSION_MINOR __clang_minor__
    #define JENCH_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
    #define JENCH_COMPILER_IS_MSVC 0
#elif JENCH_COMPILER_IS(CLANG)
    #define JENCH_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
    #define JENCH_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZZ */
    #define JENCH_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
    #define JENCH_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
    #define JENCH_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
    #define JENCH_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZ */
    #define JENCH_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
    #define JENCH_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
    #define JENCH_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
    #define JENCH_COMPILER_IS_MSVC 1
    /* _MSC_VER = XXYY */
    #define JENCH_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
    #define JENCH_COMPILER_VERSION_MINOR (_MSC_VER % 100)
    #define JENCH_COMPILER_VERSION_PATCH 0
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */
 
#if JENCH_COMPILER_IS(GCC)
    #define JENCH_PRAGMA_TO_STR(x) _Pragma(#x)
    #define JENCH_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
    #define JENCH_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
    #define JENCH_GCC_SUPPRESS_WARNING(w) JENCH_PRAGMA_TO_STR(GCC diagnostic ignored w)
    #define JENCH_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
        JENCH_GCC_SUPPRESS_WARNING_PUSH JENCH_GCC_SUPPRESS_WARNING(w)
#else // JENCH_GCC
    #define JENCH_GCC_SUPPRESS_WARNING_PUSH
    #define JENCH_GCC_SUPPRESS_WARNING(w)
    #define JENCH_GCC_SUPPRESS_WARNING_POP
    #define JENCH_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // JENCH_GCC

#if JENCH_COMPILER_IS(MSVC)
    #define JENCH_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
    #define JENCH_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
    #define JENCH_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
    #define JENCH_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
        JENCH_MSVC_SUPPRESS_WARNING_PUSH JENCH_MSVC_SUPPRESS_WARNING(w)
#else // JENCH_MSVC
    #define JENCH_MSVC_SUPPRESS_WARNING_PUSH
    #define JENCH_MSVC_SUPPRESS_WARNING(w)
    #define JENCH_MSVC_SUPPRESS_WARNING_POP
    #define JENCH_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // JENCH_MSVC

#if JENCH_COMPILER_IS(CLANG)
    #define JENCH_PRAGMA_TO_STR(x) _Pragma(#x)
    #define JENCH_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
    #define JENCH_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
    #define JENCH_CLANG_SUPPRESS_WARNING(w) JENCH_PRAGMA_TO_STR(clang diagnostic ignored w)
    #define JENCH_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
        JENCH_CLANG_SUPPRESS_WARNING_PUSH JENCH_CLANG_SUPPRESS_WARNING(w)
#else // JENCH_CLANG
    #define JENCH_CLANG_SUPPRESS_WARNING_PUSH
    #define JENCH_CLANG_SUPPRESS_WARNING(w)
    #define JENCH_CLANG_SUPPRESS_WARNING_POP
    #define JENCH_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // JENCH_CLANG

#if JENCH_COMPILER_IS(GCC)
    #define JENCH_DIABLE_WARNINGS                  \
        JENCH_GCC_SUPPRESS_WARNING_PUSH            \
        JENCH_GCC_SUPPRESS_WARNING("-Weverything")
    
    #define JENCH_ENABLE_WARNINGS                  \
        JENCH_GCC_SUPPRESS_WARNING_POP
#endif // JENCH_COMPILER_IS_GCC

#if JENCH_COMPILER_IS(MSVC)
    #define JENCH_DIABLE_WARNINGS                  \
        JENCH_MSVC_SUPPRESS_WARNING_PUSH           \
        JENCH_MSVC_SUPPRESS_WARNING()
    
    #define JENCH_ENABLE_WARNINGS                  \
        JENCH_MSVC_SUPPRESS_WARNING_POP
#endif // JENCH_COMPILER_IS_MSVC

#if JENCH_COMPILER_IS(CLANG)
    #define JENCH_DIABLE_WARNINGS                  \
        JENCH_CLANG_SUPPRESS_WARNING_PUSH          \
        JENCH_CLANG_SUPPRESS_WARNING("-Weverything")
    
    #define JENCH_ENABLE_WARNINGS                  \
        JENCH_CLANG_SUPPRESS_WARNING_POP
#endif // JENCH_COMPILER_IS_CLANG

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Attributes
 * @{
 */

 /** compiler builtin check */
#ifndef JENCH_HAS_BUILTIN
	#ifdef __has_builtin
    	#define JENCH_HAS_BUILTIN(x) __has_builtin(x)
  	#else
    	#define JENCH_HAS_BUILTIN(x) 0
  	#endif
#endif

/** compiler attribute check */
#ifndef JENCH_HAS_ATTRIBUTE
  	#ifdef __has_attribute
    	#define JENCH_HAS_ATTRIBUTE(x) __has_attribute(x)
  	#else
    	#define JENCH_HAS_ATTRIBUTE(x) 0
  	#endif
#endif

/** compiler feature check */
#ifndef JENCH_HAS_FEATURE
  	#ifdef __has_feature
    	#define JENCH_HAS_FEATURE(x) __has_feature(x)
  	#else
    	#define JENCH_HAS_FEATURE(x) 0
  	#endif
#endif

/** compiler include check */
#ifndef JENCH_HAS_INCLUDE
  	#ifdef __has_include
    	#define JENCH_HAS_INCLUDE(x) __has_include(x)
  	#else
    	#define JENCH_HAS_INCLUDE(x) 0
  	#endif
#endif

/** compiler cpp attribute check */
#ifndef JENCH_HAS_CPP_ATTRIBUTE
  	#ifdef __has_cpp_attribute
        #define JENCH_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
  	#else
    	#define JENCH_HAS_CPP_ATTRIBUTE(x) 0
  	#endif
#endif

/** inline for compiler */
#ifndef JENCH_INLINE
  	#if defined(__cplusplus) || JENCH_STDC >= 199901L
    	#define JENCH_INLINE inline
  	#elif JENCH_HAS_ATTRIBUTE(always_inline) || JENCH_COMPILER_SINCE(GCC, 4, 0, 0)
    	#define JENCH_INLINE __inline__ __attribute__((always_inline))
  	#else
    	#define JENCH_INLINE
  	#endif
#endif

/** noinline for compiler */
#ifndef JENCH_NOINLINE
  	#if JENCH_COMPILER_SINCE(MSVC, 14, 0, 0)
    	#define JENCH_NOINLINE __declspec(noinline)
  	#elif JENCH_HAS_ATTRIBUTE(noinline) || (JENCH_COMPILER_SINCE(GCC, 4, 0, 0))
    	#define JENCH_NOINLINE __attribute__((noinline))
  	#else
    	#define JENCH_NOINLINE
  	#endif
#endif

/** align for compiler */
#ifndef JENCH_ALIGN
  	#if JENCH_COMPILER_SINCE(MSVC, 13, 0, 0)
    	#define JENCH_ALIGN(x) __declspec(align(x))
  	#elif JENCH_HAS_ATTRIBUTE(aligned) || defined(__GNUC__)
    	#define JENCH_ALIGN(x) __attribute__((aligned(x)))
  	#elif JENCH_CPP_VERSION >= 201103L
    	#define JENCH_ALIGN(x) alignas(x)
  	#else
    	#define JENCH_ALIGN(x)
  	#endif
#endif

/** deprecate warning */
#if defined(JENCH_HAS_CXX_14)
    #define JENCH_DEPRECATED(msg) [[deprecated(msg)]]
#else
    #define JENCH_DEPRECATED(msg)
#endif

#ifndef JENCH_NODISCARD
    #define JENCH_NODISCARD [[nodiscard]]
#endif

// switch usage of constexpr keyword depending on active C++ standard.
#if defined(JENCH_HAS_CXX_17)
    #define JENCH_CONSTEXPR constexpr
#else
    #define JENCH_CONSTEXPR
#endif

// switch usage of [[likely]] C++ attribute which has been available since C++20.
#if defined(JENCH_HAS_CXX_20) && JENCH_HAS_CPP_ATTRIBUTE(likely) >= 201803L
    #define JENCH_LIKELY(expr) (!!(expr)) [[likely]]
#elif JENCH_HAS_BUILTIN(__builtin_expect)
    #define JENCH_LIKELY(expr) (__builtin_expect(!!(expr), 1))
#else
    #define JENCH_LIKELY(expr) (!!(expr))
#endif

// switch usage of [[unlikely]] C++ attribute which has been available since C++20.
#if defined(JENCH_HAS_CXX_20) && JENCH_HAS_CPP_ATTRIBUTE(unlikely) >= 201803L
    #define JENCH_UNLIKELY(expr) (!!(expr)) [[unlikely]]
#elif JENCH_HAS_BUILTIN(__builtin_expect)
    #define JENCH_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
#else
    #define JENCH_UNLIKELY(expr) (!!(expr))
#endif

// switch usage of char8_t which has been available since C++20.
#if defined(JENCH_HAS_CXX_20) && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
    #define JENCH_HAS_CHAR8_T (1)
#else
    #define JENCH_HAS_CHAR8_T (0)
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup debugger
 * @{
 */

 #if !defined(JENCH_TRAP) && defined(__clang__) && defined( __has_builtin )
    #if __has_builtin( __builtin_debugtrap )
        #define JENCH_TRAP() __builtin_debugtrap()
    #endif
#endif

#if !defined( JENCH_TRAP ) && defined(_MSC_VER)
#    define JENCH_TRAP() __debugbreak()
#endif

#if !defined(JENCH_TRAP) // If we couldn't use compiler-specific impl from above, we get into platform-specific options
    #ifdef JENCH_PLATFORM_IS_APPLE

        #if defined(__i386__) || defined(__x86_64__)
            #define JENCH_TRAP() __asm__("int $3\n" : : ) /* NOLINT */
        #elif defined(__aarch64__)
            #define JENCH_TRAP() __asm__(".inst 0xd43e0000")
        #elif defined(__POWERPC__)
            #define JENCH_TRAP() __asm__("li r0, 20\nsc\nnop\nli r0, 37\nli r4, 2\nsc\nnop\n" \
            : : : "memory","r0","r3","r4" ) /* NOLINT */
        #endif

    #elif defined(JENCH_PLATFORM_IS_LINUX)
        // If we can use inline assembler, do it because this allows us to break
        // directly at the location of the failing check instead of breaking inside
        // raise() called from it, i.e. one stack frame below.
        #if defined(__GNUC__) && (defined(__i386) || defined(__x86_64))
            #define JENCH_TRAP() asm volatile ("int $3") /* NOLINT */
        #else // Fall back to the generic way.
            #include <signal.h>

            #define JENCH_TRAP() raise(SIGTRAP)
        #endif
    #elif defined(__MINGW32__)
        extern "C" __declspec(dllimport) void __stdcall DebugBreak();
        #define JENCH_TRAP() DebugBreak()
    #endif

#endif // ^^ JENCH_TRAP is not defined yet, so we define it

/** @} */

// clang-format on

#endif // DJOEZEKE_JENCH_COMPILER_H

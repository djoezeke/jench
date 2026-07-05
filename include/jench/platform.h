#ifndef DJOEZEKE_JENCH_PLATFORM_H
#define DJOEZEKE_JENCH_PLATFORM_H

// clang-format off

//-----------------------------------------------------------------------------
// [SECTION] Platform : Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup platform Platform Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name Platform, like `APPLE`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define JENCH_PLATFORM_IS(name) JENCH_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#ifdef __APPLE__
  	/**
   	* @brief Defined if compiling for Apple.
   	*/
	#define JENCH_PLATFORM_IS_APPLE 1
    #define JENCH_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
  	/**
   	* @brief Defined if compiling for Linux.
   	*/
	#define JENCH_PLATFORM_IS_LINUX 1
  	#define JENCH_PLATFORM_NAME_IS "Linux"
#elif defined(__WIN32__) || defined(_WIN32) || defined(__MINGW32__)
  	/**
   	* @brief Defined if compiling for Windows.
   	*/
  	#define JENCH_PLATFORM_IS_WINDOWS 1
  	#define JENCH_PLATFORM_NAME_IS "Windows"
#else
  	/**
   	* @brief Defined if compiling for Others.
   	*/
  	#define JENCH_PLATFORM_IS_OTHERS 1
  	#define JENCH_PLATFORM_NAME_IS "Others"
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Platform : ARCHITECTURE
//-----------------------------------------------------------------------------

/**
 * @defgroup 
 * @{
 */

#ifndef JENCH_ARCH_AMD64
	#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
		#define JENCH_ARCH_AMD64	  1
		#define JENCH_ARCH_BITNESS 64
	#else
		#define JENCH_ARCH_AMD64 0
	#endif
#endif

#ifndef JENCH_ARCH_X86
	#if defined(__i386__) || defined(_M_IX86)
		#define JENCH_ARCH_X86	  1
		#define JENCH_ARCH_BITNESS 32
	#else
		#define JENCH_ARCH_X86 0
	#endif
#endif

#ifndef JENCH_ARCH_ARM
	#if defined(__aarch64__) || defined(__ARM_ARCH_ISA_A64) || defined(_M_ARM64) || defined(__ARM_64BIT_STATE)             \
		|| defined(_M_ARM64EC)
		#define JENCH_ARCH_ARM32	  0
		#define JENCH_ARCH_ARM64	  1
		#define JENCH_ARCH_ARM	  1
		#define JENCH_ARCH_BITNESS 64
	#elif defined(__arm__) || defined(_M_ARM) || defined(__ARM_32BIT_STATE)
		#define JENCH_ARCH_ARM32	  1
		#define JENCH_ARCH_ARM64	  0
		#define JENCH_ARCH_ARM	  1
		#define JENCH_ARCH_BITNESS 32
	#else
		#define JENCH_ARCH_ARM32 0
		#define JENCH_ARCH_ARM64 0
		#define JENCH_ARCH_ARM	0
	#endif
#endif

#ifndef JENCH_ARCH_BITNESS
	#define JENCH_ARCH_BITNESS 0
#endif

#ifndef JENCH_ARCH_X64
	#if JENCH_ARCH_BITNESS == 64
		#define JENCH_ARCH_X64 1
	#else
		#define JENCH_ARCH_X64 0
	#endif
#endif

 /** @} */

//-----------------------------------------------------------------------------
// [SECTION] Platform : Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if JENCH_PLATFORM_IS_WINDOWS
    #define JENCH_API_EXPORT __declspec(dllexport)
    #define JENCH_API_IMPORT __declspec(dllimport)
    #define JENCH_NO_EXPORT
#else
    #define JENCH_API_EXPORT __attribute__((visibility("default")))
    #define JENCH_API_IMPORT __attribute__((visibility("default")))
    #define JENCH_NO_EXPORT __attribute__((visibility("hidden")))
#endif  // JENCH_PLATFORM_IS_WINDOWS

/**
 * @def JENCH_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct
 * symbol visibility on all platforms.
 */

#if defined(JENCH_BUILD_STATIC)
    #define JENCH_API
#elif defined(JENCH_BUILD_SHARED) || defined(JENCH_EXPORTS)
    /* We are building this library */
    #define JENCH_API JENCH_API_EXPORT
#elif defined(JENCH_LOAD_SHARED) || defined(JENCH_IMPORTS)
    /* We are using this library */
    #define JENCH_API JENCH_API_IMPORT
#else  // JENCH_BUILD_STATIC
    #define JENCH_API
#endif  // JENCH_BUILD_STATIC

/** @} */

// clang-format on

#endif // DJOEZEKE_JENCH_PLATFORM_H

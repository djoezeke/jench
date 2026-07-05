#ifndef DJOEZEKE_JENCH_COMMON_H
#define DJOEZEKE_JENCH_COMMON_H

// clang-format off

#ifndef JENCH_INTELLISENSE
  	#ifdef __INTELLISENSE__
    	#define JENCH_INTELLISENSE 1
	#else
		#define JENCH_INTELLISENSE 0
	#endif
#endif

#ifndef JENCH_DOXYGEN
	#if defined(DOXYGEN) || defined(__DOXYGEN) || defined(__DOXYGEN__) || defined(__doxygen__) || defined(__POXY__)        \
	|| defined(__poxy__)
		#define JENCH_DOXYGEN 1
	#else
		#define JENCH_DOXYGEN 0
	#endif
#endif

#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS)) && !defined(JENCH_NO_EXCEPTIONS)
    #define JENCH_THROW(exception) throw exception
    #define JENCH_TRY try
    #define JENCH_JENCH(exception) catch(exception)
#else
  #define JENCH_REQUIRE(expression, error)                                                        \
    do                                                                                             \
    {                                                                                              \
      if (JENCH_UNLIKELY(!(expression)))                                                          \
      {                                                                                            \
        printf("Error: %s (%s:%d)\n", error, __FILE__, __LINE__);        \
        abort();                                                                                   \
      }                                                                                            \
    } while (0)
    
    #define JENCH_THROWE(exception) JENCH_REQUIRE(false, exception.what())
    #define JENCH_THROW(exception) abort()
    #define JENCH_TRY if(true)
    #define JENCH_JENCH(exception) if(false)
#endif

#ifndef JENCH_ASSERT
    #include <assert.h> // assert
    #define JENCH_ASSERT(x) assert(x)
#else
    #define JENCH_ASSERT(x)
#endif

/** 
 * @brief One.
 *
 *  This is only semantic sugar for the number `1`.
 *  @note You can instead use `1` or `true` .
 *
 */
#define JENCH_TRUE 1

/** 
 * @brief Zero.
 *
 *  This is only semantic sugar for the number `0`.
 *  @note You can instead use `0` or `false` .
 *
 */
#define JENCH_FALSE 0

// clang-format on

#endif // DJOEZEKE_JENCH_COMMON_H

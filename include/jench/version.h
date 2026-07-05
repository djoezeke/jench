#ifndef DJOEZEKE_JENCH_VERSION_H
#define DJOEZEKE_JENCH_VERSION_H

// clang-format off

#ifndef JENCH_SKIP_VERSION_CHECK
    #if defined(JENCH_VERSION_MAJOR) && defined(JENCH_VERSION_MINOR) && defined(JENCH_VERSION_PATCH)
        #if JENCH_VERSION_MAJOR != 0 || JENCH_VERSION_MINOR != 1 || JENCH_VERSION_PATCH != 0
            #warning "Already included a different version of the library!"
        #endif
    #endif
#endif  // JENCH_SKIP_VERSION_CHECK

#define JENCH_TOSTR_IMPL(x) #x
#define JENCH_TOSTR(x) JENCH_TOSTR_IMPL(x)

/**
 * @defgroup version version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def JENCH_VERSION_MAJOR
 * @brief Major version number of the library.
 * @note If this were version 1.2.3, this value would be 1.
 * @since This macro is available since 0.1.0 .
 */
#ifndef JENCH_VERSION_MAJOR
    #define JENCH_VERSION_MAJOR 0
#endif // JENCH_VERSION_MAJOR

/**
 * @def JENCH_VERSION_MINOR
 * @brief Minor version number of the library.
 * @note If this were version 1.2.3, this value would be 2.
 * @since This macro is available since 0.1.0 .
 */
#ifndef JENCH_VERSION_MINOR
    #define JENCH_VERSION_MINOR 1
#endif // JENCH_VERSION_MINOR

/**
 * @def JENCH_VERSION_PATCH
 * @brief Patch version number of the library.
 * @note If this were version 1.2.3, this value would be 3.
 * @since This macro is available since 0.1.0 .
 */
#ifndef JENCH_VERSION_PATCH
    #define JENCH_VERSION_PATCH 0
#endif // JENCH_VERSION_PATCH

/**
 * @def JENCH_VERSION_STRING
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */
#ifndef JENCH_VERSION_STRING
    #define JENCH_VERSION_STRING          \
    JENCH_TOSTR(JENCH_VERSION_MAJOR) "." \
    JENCH_TOSTR(JENCH_VERSION_MINOR) "." \
    JENCH_TOSTR(JENCH_VERSION_PATCH)
#endif // JENCH_VERSION_STRING

/**
 * @def JENCH_VERSION
 * @brief Library version number.
 */
#ifndef JENCH_VERSION
    #define JENCH_VERSION (JENCH_VERSION_MAJOR * 10000 + JENCH_VERSION_MINOR * 100 + JENCH_VERSION_PATCH)
#endif // JENCH_VERSION

/** @} */

// clang-format on

#endif // DJOEZEKE_JENCH_VERSION_H

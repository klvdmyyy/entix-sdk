#pragma once

// -----------------------------------------------
// Compiler detection using predefined macros
// -----------------------------------------------
#if defined(__clang__)
    #define ENGINE_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define ENGINE_COMPILER_GCC
#elif defined(_MSC_VER)
    #define ENGINE_COMPILER_MSVC
#else
    #warning "Unknown or unsupported compiler. It can cause errors!"
#endif

// -----------------------------------------------
// Platform detection using predefined macros
// -----------------------------------------------
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define ENGINE_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define ENGINE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define ENGINE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define ENGINE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define ENGINE_PLATFORM_LINUX
	/* #error "Linux is not supported!" */
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

// -----------------------------------------------
// Force inline macro
// -----------------------------------------------
#ifdef ENGINE_COMPILER_CLANG
#    define E_FORCE_INLINE [[clang::always_inline]]
#elif defined(ENGINE_COMPILER_GCC)
#    define E_FORCE_INLINE [[gnu::always_inline]]
#elif defined(ENGINE_COMPILER_MSVC)
#    define E_FORCE_INLINE [[msvc::forceinline]]
#else
#	 warning "E_FORCE_INLINE are not implementend for your compiler!"
#    define E_FORCE_INLINE
#endif

// -----------------------------------------------
// Platform specific Engine API
// -----------------------------------------------
#ifdef ENGINE_PLATFORM_WINDOWS
    #ifdef ENGINE_BUILD_DLL
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_API
#endif

// -----------------------------------------------
// Other useful macros
// -----------------------------------------------
#define E_BIT(X) (1 << X)

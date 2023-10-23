#pragma once

#undef TRACTOR_OS_WINDOWS
#undef TRACTOR_OS_LINUX
#undef TRACTOR_OS_MACOS
#undef TRACTOR_OS_ANDROID
#undef TRACTOR_OS_IOS

#if defined _WIN32
#define TRACTOR_OS_WINDOWS 1
#elif defined(__linux__) && !defined(__ANDROID__)
#define TRACTOR_OS_LINUX 1
#elif defined(__APPLE__)
#define TRACTOR_OS_MACOS 1
#endif

namespace tractor
{
    enum class os
    {
        windows,
        linux,
        macos,
        android,
        ios,
#if defined TRACTOR_OS_WINDOWS
        native = windows,
#elif defined TRACTOR_OS_LINUX
        native = linux,
#elif defined TRACTOR_OS_MACOS
        native = macos,
#elif defined TRACTOR_OS_ANDROID
        native = android,
#elif defined TRACTOR_OS_IOS
        native = ios,
#else
        native,
#endif
    };

    constexpr bool is_windows_v = os::native == os::windows;
    constexpr bool is_linux_v = os::native == os::linux;
    constexpr bool is_macos_v = os::native == os::macos;
    constexpr bool is_android_v = os::native == os::android;
    constexpr bool is_ios_v = os::native == os::ios;

    constexpr bool is_windows() { return is_windows_v; }
    constexpr bool is_linux() { return is_linux_v; }
    constexpr bool is_macos() { return is_macos_v; }
    constexpr bool is_android() { return is_android_v; }
    constexpr bool is_ios() { return is_ios_v; }

    constexpr bool is_os(os o) { return o == os::native; }
} // namespace tractor

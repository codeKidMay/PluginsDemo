#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <cstdarg>
#include <csignal>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <limits>
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
#include <sstream>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <algorithm>
#include <future>
#include <bitset>
#include <regex>
#include <iomanip>
#include <new>
#include <array>
#include <filesystem>

#ifdef PLUGIN_MANAGE_EXPORTS
#define PLUGIN_MANAGE_EXP __declspec(dllexport)
#else
#define PLUGIN_MANAGE_EXP __declspec(dllimport)
#endif

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64)
#define ARK_PLATFORM_WIN
#elif defined(__APPLE_CC__)
#define ARK_PLATFORM_DARWIN
#else
#define ARK_PLATFORM_LINUX
#endif

#ifdef ARK_PLATFORM_WIN
// only windows include

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#ifndef WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <MSWSock.h>
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#define _SCL_SECURE_NO_WARNINGS

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGUSR1 10
#define SIGPIPE 13
#define SIGCHLD 17
#define SIGSYS 32

#include <sdkddkver.h>
#include <Dbghelp.h>
#pragma comment(lib, "DbgHelp")
#pragma comment(lib, "ws2_32")

#else
// only other Unix/Linux include
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#ifdef ARK_PLATFORM_LINUX
#include <sys/prctl.h>
#include <endian.h>
#endif
#include <dlfcn.h>

#ifdef ARK_PLATFORM_DARWIN
#include <spawn.h>
#endif // ARK_PLATFORM_DARWIN

#endif

#ifdef min
#undef min
#endif // min

#ifdef max
#undef max
#endif // max

#define ARK_LITTLE_ENDIAN
#define ARK_BIG_ENDIAN

#if !defined(ARK_ENDIAN)
#if defined(USE_BIG_ENDIAN)
#define ARK_ENDIAN ARK_BIG_ENDIAN
#else
#define ARK_ENDIAN ARK_LITTLE_ENDIAN
#endif
#endif // !defined(ARK_ENDIAN)

#define UNIX_FLAVOUR_LINUX 1
#define UNIX_FLAVOUR_BSD 2
#define UNIX_FLAVOUR_OTHER 3
#define UNIX_FLAVOUR_OSX 4

#define COMPILER_MICROSOFT 0
#define COMPILER_GNU 1
#define COMPILER_BORLAND 2
#define COMPILER_INTEL 3
#define COMPILER_CLANG 4

#ifdef _MSC_VER
#define ARK_COMPILER COMPILER_MICROSOFT
#elif defined(__INTEL_COMPILER)
#define ARK_COMPILER COMPILER_INTEL
#elif defined(__BORLANDC__)
#define ARK_COMPILER COMPILER_BORLAND
#elif defined(__GNUC__)
#define ARK_COMPILER COMPILER_GNU
#elif defined(__clang__)
#define ARK_COMPILER COMPILER_CLANG
#else
#pragma error "FATAL ERROR: Unknown compiler."
#endif

#if defined(ARK_PLATFORM_LINUX) || defined(ARK_PLATFORM_DARWIN)
#if defined(HAVE_DARWIN)
#define ARK_PLATFORM_NAME "MacOSX"
#define UNIX_FLAVOUR UNIX_FLAVOUR_OSX
#elif defined(USE_KQUEUE)
#define ARK_PLATFORM_NAME "FreeBSD"
#define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#elif defined(USE_KQUEUE_DFLY)
#define ARK_PLATFORM_NAME "DragonFlyBSD"
#define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#else
#define ARK_PLATFORM_NAME "Linux"
#define UNIX_FLAVOUR UNIX_FLAVOUR_LINUX
#endif
#elif defined(ARK_PLATFORM_WIN)
#define ARK_PLATFORM_NAME "Windows"
#else
#pragma error "FATAL ERROR: Unknown platform."
#endif

#ifndef ARK_RUN_MODE
#if defined(DEBUG) || defined(_DEBUG)
#define ARK_RUN_MODE_DEBUG
#define ARK_RUN_MODE_NAME "Debug"
#else
#define ARK_RUN_MODE_RELEASE
#define ARK_RUN_MODE_NAME "Release"
#endif // DEBUG
#endif

#ifndef X64
#if defined(_WIN64) || defined(__x86_64__) || defined(__amd64) || defined(__LP64__)
#define X64
#endif
#endif

#ifdef X64
#define ARK_ARCH_NAME "x64"
#else
#define ARK_ARCH_NAME "x86"
#endif // X64

#define ARK_LITTLE_ENDIAN

#ifdef ARK_PLATFORM_WIN
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4305)
#pragma warning(disable : 4800)
#pragma warning(disable : 4996)
#endif

#if defined(ARK_USE_GUID_32)
using guid_t = int32_t;
#elif defined(ARK_USE_GUID_128)
using guid_t = int128_t;
#else
using guid_t = int64_t;
#endif

using conv_id_t = uint32_t;
using bus_id_t = int;
using msg_id_t = uint16_t;

#pragma once


#include "Logging.h"
#include <filesystem>

#ifdef BDY_ENABLE_ASSERTS

#define BDY_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BDY##type##ERROR(msg, __VA_ARGS__); BDY_DEBUGBREAK(); } }
#define BDY_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BDY_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define BDY_INTERNAL_ASSERT_NO_MSG(type, check) BDY_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BDY_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define BDY_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define BDY_INTERNAL_ASSERT_GET_MACRO(...) BDY_EXPAND_MACRO( BDY_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BDY_INTERNAL_ASSERT_WITH_MSG, BDY_INTERNAL_ASSERT_NO_MSG) )

#define BDY_ASSERT(...) BDY_EXPAND_MACRO( BDY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define BDY_CORE_ASSERT(...) BDY_EXPAND_MACRO( BDY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else

#define BDY_ASSERT(...)
#define BDY_CORE_ASSERT(...)

#endif

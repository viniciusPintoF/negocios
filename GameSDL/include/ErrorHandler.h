#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <iostream>

#if defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#elif defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#endif

#define M_DEBUG
#if defined(M_DEBUG)
#define ASSERT(x) if(!x) DEBUG_BREAK();
#define LOG_ERROR(x) std::cerr << "ERROR: "<< __FILE__ << ":" << __LINE__ << " " << __func__ << " [" << x << "]" << std::endl;
#define MY_DEBUG(x) std::cout << "Debug: "<< __FILE__ << ":" << __LINE__ << " " << __func__ << " [" << x << "]" << std::endl;
#else
#define ASSERT(x)
#define LOG_ERROR(x)
#endif

#endif

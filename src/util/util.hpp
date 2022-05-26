#ifndef UTIL_UTIL_HPP
#define UTIL_UTIL_HPP

#define COMPTIME_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define COMPTIME_ARRAY_END(a) a + COMPTIME_ARRAY_SIZE(a)

namespace util {}  // namespace util

#endif  // UTIL_UTIL_HPP

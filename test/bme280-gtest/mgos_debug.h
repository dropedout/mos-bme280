#ifndef MGOS_DEBUG_H
#define MGOS_DEBUG_H

#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <iostream>

#define LOG_DEBUG "DEBUG"
#define LL_ERROR "ERROR"
#define LL_INFO "INFO"

#define LOG(l,x) \
  do { \
    std::cout << #l << '\t'; \
    printf x; \
    std::cout << '\n';\
  } while (0)


#endif // MGOS_DEBUG_H

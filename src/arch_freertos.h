#pragma once

#if MG_ARCH == MG_ARCH_FREERTOS

#include <ctype.h>
#if !defined(MG_ENABLE_LWIP) || !MG_ENABLE_LWIP
#include <errno.h>
#endif
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>  // rand(), strtol(), atoi()
#include <string.h>
#if defined(__ARMCC_VERSION)
#define mode_t size_t
#include <alloca.h>
#include <time.h>
#elif defined(__CCRH__)
#else
#include <sys/stat.h>
#endif

#include <FreeRTOS.h>
#include <task.h>

#define MG_ENABLE_CUSTOM_CALLOC 1

static inline void mg_free(void *ptr) {
  vPortFree(ptr);
}

// Re-route calloc/free to the FreeRTOS's functions, don't use stdlib
static inline void *mg_calloc(size_t cnt, size_t size) {
  void *p = pvPortMalloc(cnt * size);
  if (p != NULL) memset(p, 0, size * cnt);
  return p;
}

#if !defined(MG_ENABLE_POSIX_FS) || !MG_ENABLE_POSIX_FS
#else
#define mkdir(a, b) mg_mkdir(a, b)
static inline int mg_mkdir(const char *path, mode_t mode) {
  (void) path, (void) mode;
  return -1;
}
#endif

#endif  // MG_ARCH == MG_ARCH_FREERTOS

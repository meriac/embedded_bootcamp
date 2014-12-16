#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef  __cplusplus
#  define EXTERN extern "C"
#else
#  define EXTERN extern
#endif/*__CPP__*/

#include "linker.h"

#define NOINLINE __attribute__ ((noinline))
#define PACKED __attribute__((packed))
#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

/* array count macro */
#define ARRAY_COUNT(x) (sizeof(x)/sizeof(x[0]))

#if defined(MK64F)
#  include <MK64F12.h>
#else
#  error "unknown ARCH in Makefile"
#endif

#ifndef TRUE
#define TRUE 1
#endif/*TRUE*/

#ifndef FALSE
#define FALSE 0
#endif/*FALSE*/

#include <tfp_printf.h>
#ifndef dprintf
#define dprintf tfp_printf
#endif/*dprintf*/

#ifdef  NDEBUG
#define DPRINTF(...) {}
#define assert(...)
#else /*NDEBUG*/
#define DPRINTF dprintf
#define assert(x) if(!(x)){dprintf("HALTED(%s:%i): assert(%s)\n",  __FILE__, __LINE__, #x);while(1);}
#endif/*NDEBUG*/

#ifdef  CHANNEL_DEBUG
#if (CHANNEL_DEBUG<0) || (CHANNEL_DEBUG>31)
#error "Debug channel needs to be >=0 and <=31"
#endif
#endif/*CHANNEL_DEBUG*/


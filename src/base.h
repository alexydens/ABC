/*
 * This is the header file you need to include to use my ANSI-compatible base
 * library in C, ABC (Ansi Base library for C).
 * MACROS - TO DEFINE:
 * -  DEBUG           - defines ENABLE_ASSERT
 * -  ENABLE_ASSERT   - enable debug assertions, that crash or do something else
 *    when not true.
 * -  ASSERT_BEHAVIOR - change what is done when an asssertion fails.
 * 
 * MACROS - PREDEFINED:
 * -  OS:
 *    -> OS_WINDOWS if operating system is Windows.
 *    -> OS_LINUX if operating system is Linux.
 *    -> OS_MACOS if operating system is MacOS.
 * - ARCHITECTURE:
 *    -> CPU_ARM if architecture is Arm.
 *    -> CPU_ARM64 if architecture is Arm64.
 *    -> CPU_X86 if architecture is x86.
 *    -> CPU_X86_64 if architecture is x86_64.
 */

/* Include guard */
#if !defined(BASE_ANSI_H)
#define BASE_ANSI_H

/* External dependencies: C standard library */
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

/* If debug, what else to define */
#if defined(DEBUG)
#   define ENABLE_ASSERT
#endif

/******************************************************************************
* Operating System ************************************************************
******************************************************************************/

/*
 * The OS_... macros are 1 if the OS is being used, and 0 if it is not.
 * The OS_NOVAL_... macros are only defined at all if the OS is present, so that
 * they can be used in ifdefs.
 */

#if defined(_WIN32)
#   define OS_WINDOWS   1
#   define OS_NOVAL_WINDOWS
#else
#   define OS_WINDOWS   0
#endif
#if defined(__linux__)
#   define OS_LINUX     1
#   define OS_NOVAL_LINUX
#else
#   define OS_LINUX     0
#endif
#if defined(__APPLE__)
#   define OS_MACOS     1
#   define OS_NOVAL_MACOS
#else
#   define OS_MACOS     0
#endif

/******************************************************************************
* System Architecture *********************************************************
******************************************************************************/

/*
 * The CPU_... macros are 1 if the architecture is being used, and 0 if it is
 * not.
 * The CPU_NOVAL_... macros are only defined at all if the architecture is 
 * present, so that they can be used in ifdefs.
 */
#if defined(__arm__)
#   define CPU_ARM      1
#   define CPU_NOVAL_ARM
#else
#   define CPU_ARM      0
#endif
#if defined(__aarch64__)
#   define CPU_ARM64    1
#   define CPU_NOVAL_ARM64
#else
#   define CPU_ARM64    0
#endif
#if defined(__i386__)
#   define CPU_X86      1
#   define CPU_NOVAL_X86
#else
#   define CPU_X86      0
#endif
#if defined(__x86_64)
#   define CPU_X86_64   1
#   define CPU_NOVAL_X86_64
#else
#   define CPU_X86_64   0
#endif

/******************************************************************************
* Utility Macros **************************************************************
******************************************************************************/

#define AS_STMT(S)          do{S}while(0)

#define CLAMP(V, MIN, MAX)  ((V) < (MIN) ? (MIN) : ((V) > (MAX) ? (MAX) : (V)))
#define SWAP(A, B)          AS_STMT( __typeof__(A) TMP = (A); A = (B); B = TMP; )
#define MAX(A, B)           ((A) > (B) ? (A) : (B))
#define MIN(A, B)           ((A) < (B) ? (A) : (B))

#define ARRLEN(A)           (sizeof(A)/sizeof(*A))

#define STRFROM_(S)         #S
#define STRFROM(S)          STRFROM_(S)
#define CONCAT_(A, B)       A##B
#define CONCAT(A, B)        CONCAT_(A, B)

static int _expr_val; /* used in the macro, so needs to be predefined */
#define ASSERT(EXPR)        AS_STMT(_expr_val = EXPR;\
                            if (!(_expr_val)) ASSERT_ONFAIL(EXPR);)

#if defined(ENABLE_ASSERT)
#   define ASSERT_ONFAIL(EXPR)       AS_STMT(\
  printf(\
    "FATAL: ASSERTION FAILED AT\n\t-> FILE %s\n\t-> LINE %d\n\t-> EXPR %s\n",\
    __FILE__, __LINE__, #EXPR);\
  printf("\a\a\a\a\a");\
  exit(-1);\
  )
#else
#   define ASSERT_ONFAIL(EXPR)
#endif

/******************************************************************************
* Basic Types *****************************************************************
******************************************************************************/

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef float     f32;
typedef double    f64;

typedef int bool;
enum { false, true };

/*
 * To pass in a function pointer to a function use VoidFunc*, not void* for the
 * correct size
 */
typedef void VoidFunc(void);

/******************************************************************************
* Compound Types **************************************************************
******************************************************************************/

/* For making vectors, you can use these macros */
#define MAKE_V2I32(X, Y)    (v2i32){(X), (Y)}
#define MAKE_V3I32(X, Y, Z) (v3i32){(X), (Y), (Z)}
#define MAKE_V2F32(X, Y)    (v2f32){(X), (Y)}
#define MAKE_V3F32(X, Y, Z) (v3f32){(X), (Y), (Z)}

/* Predefined colors */
#define RED     (Color){{.r = 255, .g = 0, .b = 0, .a = 255}}
#define GREEN   (Color){{.r = 0, .g = 255, .b = 0, .a = 255}}
#define BLUE    (Color){{.r = 0, .g = 0, .b = 255, .a = 255}}
#define MAGENTA (Color){{.r = 255, .g = 0, .b = 255, .a = 255}}
#define CYAN    (Color){{.r = 0, .g = 255, .b = 255, .a = 255}}
#define YELLOW  (Color){{.r = 255, .g = 255, .b = 0, .a = 255}}
#define WHITE   (Color){{.r = 255, .g = 255, .b = 255, .a = 255}}
#define BLACK   (Color){{.r = 0, .g = 0, .b = 0, .a = 255}}
/* For making colors, use this macro */
#define MAKE_COLOR(R, G, B, A) (Color){{.r = (R), .g = (G), .b = (B), .a = (A)}}

/* i32 vectors */
typedef struct {
    i32 x;
    i32 y;
} v2i32;
typedef struct {
    i32 x;
    i32 y;
    i32 z;
} v3i32;
/* f32 vectors */
typedef struct {
    f32 x;
    f32 y;
} v2f32;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} v3f32;

/* Color structure, can be casted to an RGBA u32 */
typedef union {
  struct {
    u8 a;
    u8 b;
    u8 g;
    u8 r;
  };
  u32 uint;
} Color;

/******************************************************************************
* Global consts ***************************************************************
******************************************************************************/

/* signed int min vals */
static i8   min_i8  = (i8) 0x80;
static i16  min_i16 = (i16)0x8000;
static i32  min_i32 = (i32)0x80000000;
static i64  min_i64 = (i64)0x8000000000000000lu;
/* signed int max vals */
static i8   max_i8  = (i8) 0x7f;
static i16  max_i16 = (i16)0x7fff;
static i32  max_i32 = (i32)0x7fffffff;
static i64  max_i64 = (i64)0x7ffffffffffffffflu;
/* unsigned int max vals */
static u8   max_u8  = (u8) 0xff;
static u16  max_u16 = (u16)0xffff;
static u32  max_u32 = (u32)0xffffffff;
static u64  max_u64 = (u64)0xfffffffffffffffflu;

/* f32 consts */
static f32  m_epsilon32 = 1.1920929e-7f;
static f32  pi32    = 3.14159265359f;
static f32  e32     = 2.71828182846f;
/* f64 consts */
static f64  m_epsilon64 = 2.220446e-16;
static f64  pi64    = 3.1415965359;
static f64  e64     = 2.71828182846;

/******************************************************************************
* Float Functions *************************************************************
******************************************************************************/

/* Infinity for f32 */
f32 inf_f32();
/* Negative infinity for f32 */
f32 neginf_f32();

/* Infinity for f32 */
f64 inf_f64();
/* Negative infinity for f32 */
f64 neginf_f64();

/* Linear interpolation for f32 */
f32 lerp_f32(f32 a, f32 b, f32 t);
/* Linear interpolation for f64 */
f64 lerp_f64(f64 a, f64 b, f64 t);

/******************************************************************************
* Vector Functions ************************************************************
******************************************************************************/

/* Dot product of two v2i32(s) */
i32 dot_v2i32(v2i32 a, v2i32 b);
/* Dot product of two v3i32(s) */
i32 dot_v3i32(v3i32 a, v3i32 b);
/* Dot product of two v2f32(s) */
f32 dot_v2f32(v2f32 a, v2f32 b);
/* Dot product of two v3f32(s) */
f32 dot_v3f32(v3f32 a, v3f32 b);

/* The z coordinate of a hypothetical cross product of a and b */
i32 cross_v2i32(v2i32 a, v2i32 b);
/* The cross product of two v3i32(s) */
v3i32 cross_v3i32(v3i32 a, v3i32 b);
/* The z coordinate of a hypothetical cross product of a and b */
f32 cross_v2f32(v2f32 a, v2f32 b);
/* The cross product of two v3f32(s) */
v3f32 cross_v3f32(v3f32 a, v3f32 b);

/* Normalize the vector v */
v2f32 normalize_v2f32(v2f32 v);
/* Normalize the vector v */
v3f32 normalize_v3f32(v3f32 v);

#endif /* BASE_ANSI_H */

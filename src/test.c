/* The base library */
#include <ABC/base.h>
/* The linear allocator */
#include <ABC/arena_alloc.h>

/* For strcmp() */
#include <string.h>

int main() {
  /* Testing the arena allocator */
  Arena arena = createArena(32);
  i32* a = arena_alloc(&arena, sizeof(i32) * 4);
  i32* b = arena_alloc(&arena, sizeof(i32));
  *b = 1;
  a[3] = 4;
  printf("%d, %d\n", *b, a[3]);
  arena_free(&arena);

  /* Testing the operating system finder */
  printf("Operating System:\n");
  printf("\t-> Windows: %s\n", OS_WINDOWS ? "true" : "false");
  printf("\t-> Linux: %s\n", OS_LINUX ? "true" : "false");
  printf("\t-> MacOS: %s\n", OS_MACOS ? "true" : "false");

  /* Testing the system architecture finder */
  printf("System Architecture:\n");
  printf("\t-> Arm: %s\n", CPU_ARM ? "true" : "false");
  printf("\t-> Arm64: %s\n", CPU_ARM64 ? "true" : "false");
  printf("\t-> x86: %s\n", CPU_X86 ? "true" : "false");
  printf("\t-> x86_64: %s\n", CPU_X86_64 ? "true" : "false");

  /* Utility Macros */
  printf("Utility Macros:\n");
  /* CLAMP */
  ASSERT(1 == CLAMP(0, 1, 3));
  printf("\t-> Clamp lower than min:\tsuccess!\n");
  ASSERT(3 == CLAMP(4, 1, 3));
  printf("\t-> Clamp heigher than max:\tsuccess!\n");
  ASSERT(2 == CLAMP(2, 1, 3));
  printf("\t-> Clamp within range:\t\tsuccess!\n");
  /* SWAP */
  {
    i32 swap_test_a = 0;
    i32 swap_test_b = 0;
    swap_test_a = 1;
    swap_test_b = 2;
    SWAP(swap_test_a, swap_test_b);
    ASSERT(swap_test_a == 2 && swap_test_b == 1);
  }
  printf("\t-> Swap:\t\t\tsuccess!\n");
  /* MAX */
  ASSERT(4 == MAX(4, 2));
  printf("\t-> Max 1st value:\t\tsuccess!\n");
  ASSERT(4 == MAX(2, 4));
  printf("\t-> Max 2nd value:\t\tsuccess!\n");
  /* MIN */
  ASSERT(2 == MIN(2, 4));
  printf("\t-> Min 1st value:\t\tsuccess!\n");
  ASSERT(2 == MIN(4, 2));
  printf("\t-> Min 2nd value:\t\tsuccess!\n");
  /* ARRLEN */
  {
    i32 arrlen_test[5] = { 0, 1, 2, 3, 4 };
    ASSERT(5 == ARRLEN(arrlen_test));
  }
  printf("\t-> Arrlen:\t\t\tsuccess!\n");
  /* STRFROM */
  ASSERT(strcmp(STRFROM(testing_strfrom), "testing_strfrom") == 0);
  printf("\t-> Strfrom:\t\t\tsuccess!\n");
  /* CONCAT */
  ASSERT(strcmp(STRFROM(CONCAT(abc, 123)), "abc123") == 0);
  printf("\t-> Concat:\t\t\tsuccess!\n");

  /* Color - is it the right u32? */
  printf("Colors:\n");
  {
    Color col = RED;
    Color col2 = MAKE_COLOR(0xff, 0xea, 0xff, 0xff);
    ASSERT(col.uint == 0xff0000ff);
    printf("\t-> Predefined (red):\t\tsuccess!\n");
    ASSERT(col2.uint == 0xffeaffff);
    printf("\t-> Made with macro:\t\tsuccess!\n");
  }

  /* Global consts */
  printf("Global consts:\n");
  /* signed int min vals */
  printf("\t-> min_i8: %d\n", min_i8);
  printf("\t-> min_i16: %d\n", min_i16);
  printf("\t-> min_i32: %d\n", min_i32);
  printf("\t-> min_i64: %ld\n", min_i64);
  /* signed int max vals */
  printf("\t-> max_i8: %d\n", max_i8);
  printf("\t-> max_i16: %d\n", max_i16);
  printf("\t-> max_i32: %d\n", max_i32);
  printf("\t-> max_i64: %ld\n", max_i64);
  /* unsigned int max vals */
  printf("\t-> max_u8: %u\n", max_u8);
  printf("\t-> max_u16: %u\n", max_u16);
  printf("\t-> max_u32: %u\n", max_u32);
  printf("\t-> max_u64: %lu\n", max_u64);
  /* f32 consts */
  printf("\t-> m_epsilon32: %1.8f\n", m_epsilon32);
  printf("\t-> pi32: %1.8f\n", pi32);
  printf("\t-> e32: %1.8f\n", e32);
  /* f64 consts */
  printf("\t-> m_epsilon64: %1.16f\n", m_epsilon64);
  printf("\t-> pi64: %1.16f\n", pi64);
  printf("\t-> e64: %1.16f\n", e64);

  /* Float functions */
  printf("Float functions:\n");
  printf("\t-> inf_f32: %f\n", inf_f32());
  printf("\t-> neginf_f32: %f\n", neginf_f32());
  printf("\t-> inf_f64: %f\n", inf_f32());
  printf("\t-> neginf_f64: %f\n", neginf_f64());
  ASSERT(lerp_f32(0.0f, 1.0f, 0.5f) == 0.5f);
  printf("\t-> lerp_f32\t\t\tsuccess!\n");
  ASSERT(lerp_f64(0.0, 1.0, 0.5) == 0.5);
  printf("\t-> lerp_f64\t\t\tsuccess!\n");
  /* TODO: Test the vector functions, and vectors in general - ugh */

  return 0;
}

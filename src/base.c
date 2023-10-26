/* Include the header */
#include "base.h"

/******************************************************************************
* Float Functions *************************************************************
******************************************************************************/

f32 inf_f32() {
  return 1.0f / 0.0f;
}
f32 neginf_f32() {
  return -1.0f / 0.0f;
}

f64 inf_f64() {
  return 1.0 / 0.0;
}
f64 neginf_f64() {
  return -1.0f / 0.0;
}

f32 lerp_f32(f32 a, f32 b, f32 t) {
  if (a > b) SWAP(a, b);

  return a + (t * (b-a));
}
f64 lerp_f64(f64 a, f64 b, f64 t) {
  if (a > b) SWAP(a, b);

  return a + (t * (b-a));
}

/******************************************************************************
* Vector Functions ************************************************************
******************************************************************************/

i32 dot_v2i32(v2i32 a, v2i32 b) {
  return (a.x*b.x)+(a.y*b.y);
}
i32 dot_v3i32(v3i32 a, v3i32 b) {
  return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}
f32 dot_v2f32(v2f32 a, v2f32 b) {
  return (a.x*b.x)+(a.y*b.y);
}
f32 dot_v3f32(v3f32 a, v3f32 b) {
  return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

i32 cross_v2i32(v2i32 a, v2i32 b) {
  return (a.x * b.y) - (a.y * b.x);
}
v3i32 cross_v3i32(v3i32 a, v3i32 b) {
  v3i32 res;
  res.x = a.y*b.z - a.z*b.y;
  res.y = a.z*b.x - a.x*b.z;
  res.z = a.x*b.y - a.y*b.x;
  return res;
}
f32 cross_v2f32(v2f32 a, v2f32 b) {
  return (a.x * b.y) - (a.y * b.x);
}
v3f32 cross_v3f32(v3f32 a, v3f32 b) {
  v3f32 res;
  res.x = a.y*b.z - a.z*b.y;
  res.y = a.z*b.x - a.x*b.z;
  res.z = a.x*b.y - a.y*b.x;
  return res;
}

v2f32 normalize_v2f32(v2f32 v) {
  f32 divideBy = sqrt(v.x * v.x + v.y * v.y);
  return MAKE_V2F32(v.x / divideBy, v.y / divideBy);
}
v3f32 normalize_v3f32(v3f32 v) {
  f32 divideBy = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  return MAKE_V3F32(v.x / divideBy, v.y / divideBy, v.z / divideBy);
}

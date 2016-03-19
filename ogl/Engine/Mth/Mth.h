#ifndef _IRIS_MATH_
#define _IRIS_MATH_

#include "Types.h"
#include <math.h>

namespace mth
{
  template  <typename T>          inline  T     Sqrt(T _val) { return (T)sqrt(_val); }
  template  <typename T>          inline  T     Sin(T _ang) { return (T)sin(_ang); }
  template  <typename T>          inline  T     Cos(T _ang) { return (T)cos(_ang); }
  template  <typename T>          inline  T     Tan(T _ang) { return (T)tan(_ang); }
  template  <typename T>          inline  void  SinCos(T _ang, T& s_, T& c_) { s_ = Sin(_ang);  c_ = Cos(_ang); }
  template  <typename T>          inline  T     ASin(T _val) { return (T)asin(_val); }
  template  <typename T>          inline  T     ACos(T _val) { return (T)acos(_val); }
  template  <typename T>          inline  T     ATan(T _val) { return (T)atan(_val); }
  template  <typename T>          inline  T     ATan2(T _x, T _y) { return (T)atan2(_x, _y); }
  template  <typename T>          inline  T     Pow2(T _val) { return _val*_val; }
  template  <typename T>          inline  T     PowN(T _val, int _n) { T r = 1.0f; if (_n>0) for (int i = 0; i<_n; ++i) { r *= _val; } else if (_n<0) { for (int i = 0; i<-_n; ++i) r /= _val; } return r; }
  template  <typename T>          inline  T     Log(T val) { return (T)log(val); }
  template  <typename T>          inline  T     LogBase(T val, T base) { return (T)(log(val) / log(base)); }
  template  <typename T>          inline  T     Min(T _a, T _b) { return _a<_b ? _a : _b; }
  template  <typename T>          inline  T     Max(T _a, T _b) { return _a>_b ? _a : _b; }
  template  <typename T>          inline  T     Clamp(T _val, T _min, T _max) { T r = Min(_val, _max); r = Max(r, _min);  return r; }
  template  <typename T>          inline  T     Abs(T _val) { return (T)fabs(_val); }
  template  <typename T>          inline  T     Floor(T _val) { return (T)floor(_val); }
  template  <typename T>          inline  T     Ceil(T _val) { return (T)ceil(_val); }
  template  <typename T>          inline  T     Round(T _val) { return Floor(_val + (T)0.5); }
  template  <typename T>          inline  T     Exp(T _val) { return (T)exp(_val); }
  template  <typename T>          inline  void  Swap(T& _a, T& _b) { T t = _a; _a = _b; _b = t; }

  template  <typename T>          inline  T     Lerp(const T& _a, const T& _b, const T& _lambda) { return _a*((T)1 - _lambda) + _b*_lambda; }
  template  <typename T>          inline  bool  IsPowerOf2(const T& x) { return !(x == 0) && !(x & (x - 1)); }

  // Copiadas de cmath.h
  template <class T>              inline bool InRangeNonSorted_Open(T const& val, T const& ref0, T const& ref1)
  {
    return (val < ref0 && val > ref1) || (val < ref1 && val > ref0);
  }
  template <class T>              inline bool InRangeNonSorted_Close(T const& val, T const& ref0, T const& ref1)
  {
    return (val <= ref0 && val >= ref1) || (val <= ref1 && val >= ref0);
  }
  template <class T>              inline bool EsPar(T const& val) { return ((val & 0x1) == 0); }

  inline bool IsPositive(const float fVal)
  {
    return (*(int32*)(&fVal) & 0x80000000) == 0;
  }
  inline float Sign(float fVal)
  {
    int32 i = static_cast<int32>((*(int32*)(&fVal) & 0x80000000 | 0x3F800000));
    return *(float*)(&i);
  }

  inline uint32 RoundUp4(uint32 n)
  {
    if (n & 0x3)
      return ((n & 0xFFFFFFFC) + 0x4);
    else
      return n;
  }

  inline uint32 RoundUp32(uint32 n)
  {
    if (n & 0x1F)
      return ((n & 0xFFFFFFE0) + 0x20);
    else
      return n;
  }

  inline uint32 RoundDown32(uint32 n)
  {
    return (n & 0xFFFFFFE0);
  }

  inline bool IsPowerOf2(uint32 n)
  {
    if (n == 0)
    {
      return false;
    }
    else
    {
      return (n & (n - 1)) == 0;
    }
  }
}

#endif
//-----------------------------------------------------------------------
// Vector2 class
// This class defines a 4d vector
//-----------------------------------------------------------------------
#ifndef __VECTOR4_H__
#define __VECTOR4_H__


#include "MathTypes.h"
#include "MathUtils.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Math
{
template<typename T>
class Vector4
{
public:
  union
  {
    struct
    {
      T x, y, z, w;
    };

    struct
    {
      T r, g, b, a;
    };

    T u[4];
  };
  
public:
  inline Vector4 ();
  inline Vector4 (const Vector4<T>& otro);
  inline Vector4 (const Vector3<T>& otro);
  inline Vector4 (const Vector3<T>& otro, const T tw);
  inline Vector4 (const T tx, const T ty, const T tz, const T tw);
  inline Vector4 (const T escalar);

  inline        Vector4<T>  operator + (const Vector4<T>& otro) const;
  inline        Vector4<T>  operator - (const Vector4<T>& otro) const;
  inline        Vector4<T>  operator * (const T escalar) const;
  inline        Vector4<T>  operator / (const T escalar) const;
  inline        Vector4<T>  operator + (const T escalar) const;
  inline        Vector4<T>  operator - (const T escalar) const;
  inline        Vector4<T>  operator - () const;
  inline        Vector4<T>& operator + ();
  inline const  Vector4<T>& operator + () const;

  inline Vector4<T>& operator += (const Vector4<T>& otro);
  inline Vector4<T>& operator -= (const Vector4<T>& otro);
  inline Vector4<T>& operator *= (const T escalar);
  inline Vector4<T>& operator /= (const T escalar);
  inline Vector4<T>& operator += (const T escalar);
  inline Vector4<T>& operator -= (const T escalar);
  inline Vector4<T>& operator () (const T tx, const T ty, const T tz, const T tw);
  inline void        Set         (const T tx, const T ty, const T tz, const T tw);
  inline void        SetZero     ();
  inline T operator * (const Vector4<T>& otro) const;

  inline bool operator ==       (const Vector4<T>& otro) const;
  inline bool operator !=       (const Vector4<T>& otro) const;
  inline bool IsEqualEpsilon    (const Vector4<T>& otro) const;
  inline bool IsNotEqualEpsilon (const Vector4<T>& otro) const;

  inline Vector2<T>& Scale     (const Vector2<T>& otro);
  inline Vector2<T>  GetScaled (const Vector2<T>& otro) const;
  inline const Vector2<T>& SetIfMinComponents (const Vector2<T>& otro);
  inline const Vector2<T>& SetIfMaxComponents (const Vector2<T>& otro);

  inline T  operator [] (int i) const;
  inline T& operator [] (int i);

  inline Vector4<T>& Normalize     (const T tk = One<T>());
  inline Vector4<T>  GetNormalized () const;
  inline T           Length        () const;
  inline T           SquaredLength () const;

  inline Vector4<T>& Lerp    (const Vector4<T>& otro, const T t);
  inline Vector4<T>  GetLerp (const Vector4<T>& otro, const T t) const;
};

template<typename T> inline Vector4<T>  operator * (const T escalar, const Vector4<T>& otro);
template<typename T> inline Vector4<T>  operator / (const T escalar, const Vector4<T>& otro);
template<typename T> inline Vector4<T>  operator + (const T escalar, const Vector4<T>& otro);
template<typename T> inline Vector4<T>  operator - (const T escalar, const Vector4<T>& otro);

#include "Vector4.inl"

}
#endif

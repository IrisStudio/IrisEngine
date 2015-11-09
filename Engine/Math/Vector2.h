#ifndef _H_VECTOR2_H_
#define _H_VECTOR2_H_

namespace iris
{
template<typename T> class Vector2
{
public:
  T x, y;
    
  // Construcción
  inline Vector2 ();
  inline Vector2 (const Vector2<T>& otro);
  inline Vector2 (const T fx, const T fy);
  inline Vector2 (const T escalar);


  // Operadores aritméticos
  inline        Vector2<T>  operator + (const Vector2<T>& otro) const;
  inline        Vector2<T>  operator - (const Vector2<T>& otro) const;
  inline        Vector2<T>  operator * (const T escalar) const;
  inline        Vector2<T>  operator / (const T escalar) const;
  inline        Vector2<T>  operator + (const T escalar) const;
  inline        Vector2<T>  operator - (const T escalar) const;
  inline        Vector2<T>  operator - () const;
  inline        Vector2<T>& operator + ();
  inline const  Vector2<T>& operator + () const;


  // Operadores aritméticos de actualización   
  inline Vector2<T>& operator += (const Vector2<T>& otro);
  inline Vector2<T>& operator -= (const Vector2<T>& otro);
  inline Vector2<T>& operator *= (const T escalar);
  inline Vector2<T>& operator /= (const T escalar);
  inline Vector2<T>& operator += (const T escalar);
  inline Vector2<T>& operator -= (const T escalar);

  
  // Operadores y funciones de asignación
  inline Vector2<T>& operator ()  (const T tx, const T ty);
  inline void        Set          (const T tx, const T ty);
  inline void        SetZero      ();


  // Coordenadas polares
  void  SetFromPolar (const T ang, const T length);
  void  GetPolar     (T& ang, T& length) const;


  // Producto escalar (*)
  inline T operator * (const Vector2<T>& otro) const;
  
  
  // Operadores y funciones de comparacion
  inline bool operator ==       (const Vector2<T>& otro) const;
  inline bool operator !=       (const Vector2<T>& otro) const;
  inline bool IsEqualEpsilon    (const Vector2<T>& otro) const;
  inline bool IsNotEqualEpsilon (const Vector2<T>& otro) const;


  // Producto por componentes (escalado)
  inline Vector2<T>& Scale     (const Vector2<T>& otro);
  inline Vector2<T>  GetScaled (const Vector2<T>& otro) const;


  // Establecimiento condicional
  inline const Vector2<T>& SetIfMinComponents (const Vector2<T>& otro);
  inline const Vector2<T>& SetIfMaxComponents (const Vector2<T>& otro);


  // Operador de acceso []
  inline T  operator [] (int i) const;
  inline T& operator [] (int i);


  // Funciones de la longitud 
  inline Vector2<T>& Normalize     (const T tk = One<T>());
  inline Vector2<T>  GetNormalized () const;
  inline T           Length        () const;
  inline T           SquaredLength () const;


  // Rotaciones
  inline Vector2<T>& Rotate     (const T angle);
  inline Vector2<T>  GetRotated (const T angle) const;
  inline T           GetAngle   () const;


  // Interpolación lineal
  inline Vector2<T>& Lerp    (const Vector2<T>& otro, const T t);
  inline Vector2<T>  GetLerp (const Vector2<T>& otro, const T t) const;
};

//--------------------------------------------------------------------------
// OPERADORES EXTERNOS
//--------------------------------------------------------------------------
// Operadores para poder usar orden inverso en las expresiones
template<typename T> inline Vector2<T>  operator * (const T escalar, const Vector2<T>& otro);
template<typename T> inline Vector2<T>  operator / (const T escalar, const Vector2<T>& otro);
template<typename T> inline Vector2<T>  operator + (const T escalar, const Vector2<T>& otro);
template<typename T> inline Vector2<T>  operator - (const T escalar, const Vector2<T>& otro);

//--------------------------------------------------------------------------
// FUNCIONES EXTERNAS
//--------------------------------------------------------------------------
template<typename T> inline Vector2<T> VectorMinComponents (const Vector2<T>& uno, const Vector2<T>& otro);
template<typename T> inline Vector2<T> VectorMaxComponents (const Vector2<T>& uno, const Vector2<T>& otro);

// Fichero con las definiciones de las funciones inline
#include "Vector2.inl"

}

#endif // _H_VECTOR2_H_

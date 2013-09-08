/**
 * \file quantity.hpp
 *
 * \brief   Zero-overhead dimensional analysis and unit/quantity manipulation and conversion.
 * \author  Michael S. Kenniston, Martin Moene
 * \date    23 February 2012
 * \since   0.4
 *
 * Based on quantity.hpp, rev 0.4 as of 2001-07-16 by Michael S. Kenniston.
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Unless otherwise specified, the definitions of all units in this
 * file are from NIST Special Publication 811, found online at
 * http://physics.nist.gov/cuu/pdf/sp811.pdf, or from other NIST
 * web pages.
 *
 * TO DO:
 * - templatize ostream (beware gnu compatability)
 * - check on proper way to compute double long pow( x, y )
 * - test with Rep defined to be a high-precision class instead of a primitive
 *
 * Possible future enhancements:
 * - add fractional dimensions
 * - add any_quantity
 * - [done: templatize on Rep type (float, double, and long double only)]
 * ____
 *
 * 18 April 2012, Martin Moene:
 *
 * Changes:
 * - added quantity_io_engineering.hpp
 * - added is_base to dimensions<> for quantity_io_engineering.hpp
 *
 *
 * 20 February 2012, Martin Moene:
 *
 * Changes:
 * - removed dependency on Boost/Config.h
 * - introduced TYPENAME_TYPE_K to also support compilers more modern than VC6.
 * - templatized quantity and supporting classes on representation type.
 *   Note 1: added converting copy-assignment constructor and assignment operator.
 *   Note 2: Rep used in Rep * quantity<> and quantity<> * Rep.
 *   Note 3: Rep used in meter() etc.
 *   Note 4: this change seems to have enabled further optimization for -Ox,
 *           as performance of quantity<D,double> is now same as for plain double.
 *
 * Performance:
 * - pass by reference of lhs, rhs performs better than pass-by-value (keep PBR).
 * - T get( permit ) performs better than T pure() (keep get( permit )).
 *
 * Possible future enhancements:
 * - add scaling
 */

/*
 * Performance tests on AMD Athlon 64 X2 Dual Core processor 5600+
 *
 * VC6, -Ox, pass arguments by reference (faster):
 * one double work loop =     0.00755 usec
 * one quantity work loop =   0.00755 usec
 *
 * VC6, no opt, pass arguments by reference:
 * one double work loop =     0.00988333 usec
 * one quantity work loop =   0.153917 usec
 *
 * VC6, -Ox, pass arguments by copy (slower):
 * one double work loop =     0.00755 usec
 * one quantity work loop =   0.0541667 usec
 *
 * VC2010, -Ox
 * one double work loop =     0 usec (optimized away ?)
 * one quantity work loop =   0.00755 usec
 *
 * g++ (GCC) 4.5.0, -O2, -O3: argument passing yields no difference.
 * g++ (GCC) 4.5.0, -O3: Quantity same performance as double.
 * one double work loop =     0.00885 usec
 * one quantity work loop =   0.00885 usec
 */

#ifndef PHYS_UNITS_QUANTITY_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_HPP_INCLUDED

#include <cmath>  // for pow()

#if defined( __GNUC__ )
   #define PHYS_UNITS_COMPILER_IS_GNUC
#elif defined( __MWERKS__ )
   #define PHYS_UNITS_COMPILER_IS_MWERKS
#elif defined( _MSC_VER )
   #define PHYS_UNITS_COMPILER_IS_MSVC
   #if ( _MSC_VER >= 1200 ) && ( _MSC_VER < 1300 )
      #define PHYS_UNITS_COMPILER_IS_MSVC6
   #endif
   #if ( _MSC_VER >= 1600 ) && ( _MSC_VER < 1700 )
      #define PHYS_UNITS_COMPILER_IS_MSVC2010
   #endif
#endif

#ifdef PHYS_UNITS_COMPILER_IS_MSVC
   // for MSVC, 4248 = invalid access to "private" - must be treated as an error
   // for MSVC, 4786 = truncated names in debugger - ignore
   #pragma warning( error:4248; disable:4786 )
#endif

#ifndef TYPENAME_TYPE_K
   #ifdef PHYS_UNITS_COMPILER_IS_MSVC6
      #define TYPENAME_TYPE_K
   #else
      #define TYPENAME_TYPE_K typename
   #endif
#endif

#if defined( PHYS_UNITS_COMPILER_IS_MSVC6 ) || defined( PHYS_UNITS_COMPILER_IS_MWERKS )
   #define PHYS_UNITS_NO_PASCAL_IDENTIFIER
#endif

#ifdef PHYS_UNITS_NO_PASCAL_IDENTIFIER
   /*
    * Some compilers use "pascal" as a keyword.
    * Note that defining a macro "pascal()" with zero arguments
    * will not interfere with the use of "pascal" as a keyword,
    * since the macro will be expanded only when followed by "()".
    */
   #define pascal() pascal_()
#endif

/**
 * Note: I use an outer namespace ct.
 *
 * I'd prefer an inner namespace ct, however that prevents users to e.g.:
 * - using namespace phys::units::io;
 * - using namespace phys::units::io::eng
 *
 * Instead they would have to write:
 * - using namespace phys::units::ct::io;
 * - using namespace phys::units::ct::io::eng
 *
 * Which defeates the hiding of namespace ct.
 *
 * Hopefully there'll be no collision with namespace ct of another library.
 */
namespace ct {

/**
 * namespace ct::phys.
 */
namespace phys {

/**
 * namespace ct::phys::units.
 */
namespace units {
}}}

namespace ct { namespace phys { namespace units {

#ifdef PHYS_UNITS_REP_TYPE
   typedef PHYS_UNITS_REP_TYPE Rep;
#else
   typedef double Rep;
#endif

/*
 * declare now, define later.
 */
template< typename Dims, typename T = Rep >
class quantity;

/**
 * We could drag dimensions around individually, but it's much more convenient to package them.
 */
template< int D1, int D2, int D3, int D4 = 0, int D5 = 0, int D6 = 0, int D7 = 0 >
struct dimensions
{
   enum
   {
      dim1 = D1,
      dim2 = D2,
      dim3 = D3,
      dim4 = D4,
      dim5 = D5,
      dim6 = D6,
      dim7 = D7,

      is_all_zero =
         D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0 && D5 == 0 && D6 == 0 && D7 == 0,

      is_base =
         1 == (D1 != 0) + (D2 != 0) + (D3 != 0) + (D4 != 0) + (D5 != 0) + (D6 != 0) + (D7 != 0)  &&
         1 ==  D1 + D2 + D3 + D4 + D5 + D6 + D7,
   };

   template< int R1, int R2, int R3, int R4, int R5, int R6, int R7 >
   bool operator==( dimensions<R1, R2, R3, R4, R5, R6, R7> const & rhs ) const
   {
      return D1==R1 && D2==R2 && D3==R3 && D4==R4 && D5==R5 && D6==R6 && D7==R7;
   }

   template< int R1, int R2, int R3, int R4, int R5, int R6, int R7 >
   bool operator!=( dimensions<R1, R2, R3, R4, R5, R6, R7> const & rhs ) const
   {
      return !( *this == rhs );
   }
};

typedef dimensions< 0, 0, 0 > dimensionless_d;

/**
 * namespace detail.
 */
namespace detail {

/**
 * \def PHYS_UNITS_STATIC_ASSERT_TYPE
 * \brief spm_static_assert; msg must be an identifier like 'sizeof_byte_must_be_1_byte'.
 *
 * The "static_assert" template is used to trigger a compile-time
 * error if the user attempts to take a root of a quantity
 * which would yield non-integer dimensional exponents,
 * or instantiate a quantity with all dimensions zero.
 */
#define PHYS_UNITS_STATIC_ASSERT_TYPE(expr, msg) \
    typedef typename phys::units::detail::CompileTimeError<( (expr) != 0 ) >::type ERROR__##msg;

/**
 * helper class for PHYS_UNITS_STATIC_ASSERT_TYPE.
 */
template<int> struct CompileTimeError {};

/**
 * helper class for PHYS_UNITS_STATIC_ASSERT_TYPE, ok-case specialization.
 */
template<> struct CompileTimeError<true> { typedef char type; };

/**
 * \brief The "permit" class is a portability hack - anyone with a permit
 * is treated as a friend w.r.t. access to the constructor and
 * m_value accessors of any quantity<>.
 */
template < typename T >
struct permit
{
   typedef T value_type;

   permit()
   {
   }

   explicit permit( value_type const & v )
   : m_value( v )
   {
   }

   // needed so we can construct primitives from it:

   operator value_type() const
   {
      return m_value;
   }

   value_type m_value;
};

/**
 * \brief The "collapse" template is used to avoid quantity< dimensions< 0, 0, 0 > >,
 * i.e. to make dimensionless results come out as type "Rep".
 * VC6 doesn't support partial specialization
 */
template< typename Dims, typename T >
struct collapse
{
   typedef quantity< Dims, T > type;
};

#ifndef PHYS_UNITS_COMPILER_IS_MSVC6

/**
 * Collapse dimensionless quantity to the representation type.
 */
template< typename T >
struct collapse< dimensionless_d, T >
{
   typedef T type;
};

#else // VC6 doesn't support partial template specialization

#define PHYS_UNITS_VC6_GEN_COLLAPSE( T ) \
template<> \
struct collapse< dimensionless_d, T > \
{ \
   typedef T type; \
};

PHYS_UNITS_VC6_GEN_COLLAPSE( float )
PHYS_UNITS_VC6_GEN_COLLAPSE( double )
PHYS_UNITS_VC6_GEN_COLLAPSE( long double )

#undef PHYS_UNITS_VC6_GEN_COLLAPSE

#endif // PHYS_UNITS_COMPILER_IS_MSVC6

#ifndef PHYS_UNITS_COMPILER_IS_MSVC6

// Given condition, select a type.

template < bool condition, typename Then, typename Else > struct select_;

template < typename Then, typename Else > struct select_< true , Then, Else > { typedef Then result; };
template < typename Then, typename Else > struct select_< false, Then, Else > { typedef Else result; };

#else // PHYS_UNITS_COMPILER_IS_MSVC6

// VC6 friendly select_< Condition, Then, Else >::result;

template < bool Condition, typename Then, typename Else >
struct select_
{
   template < bool InnerCondition > struct selector;

   template <> struct selector< true  > { typedef Then result; };
   template <> struct selector< false > { typedef Else result; };

   typedef typename selector< Condition >::result result;
};

#endif // PHYS_UNITS_COMPILER_IS_MSVC6

/**
 * select largest type of two types given.
 */
template < typename T, typename U >
struct promote
{
   typedef typename select_< (sizeof(T) >= sizeof(U)), T, U >::result type;
};

#define PHYS_UNITS_PROMOTE( T, U ) \
   TYPENAME_TYPE_K detail::promote<T,U>::type

/*
 * The following batch of structs are type generators to calculate
 * the correct type of the result of various operations.
 */

/**
 * product type generator.
 */
template< typename LhsDims, typename RhsDims, typename T >
struct product
{
   enum
   {
      d1 = LhsDims::dim1 + RhsDims::dim1,
      d2 = LhsDims::dim2 + RhsDims::dim2,
      d3 = LhsDims::dim3 + RhsDims::dim3,
      d4 = LhsDims::dim4 + RhsDims::dim4,
      d5 = LhsDims::dim5 + RhsDims::dim5,
      d6 = LhsDims::dim6 + RhsDims::dim6,
      d7 = LhsDims::dim7 + RhsDims::dim7,
   };

   typedef typename collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T >::type type;
};

/**
 * quotient type generator.
 */
template< typename LhsDims, typename RhsDims, typename T >
struct quotient
{
   enum
   {
      d1 = LhsDims::dim1 - RhsDims::dim1,
      d2 = LhsDims::dim2 - RhsDims::dim2,
      d3 = LhsDims::dim3 - RhsDims::dim3,
      d4 = LhsDims::dim4 - RhsDims::dim4,
      d5 = LhsDims::dim5 - RhsDims::dim5,
      d6 = LhsDims::dim6 - RhsDims::dim6,
      d7 = LhsDims::dim7 - RhsDims::dim7,
   };

   typedef typename collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T >::type type;
};

/**
 * reciprocal type generator.
 */
template< typename Dims, typename T >
struct reciprocal
{
   enum
   {
      d1 = - Dims::dim1,
      d2 = - Dims::dim2,
      d3 = - Dims::dim3,
      d4 = - Dims::dim4,
      d5 = - Dims::dim5,
      d6 = - Dims::dim6,
      d7 = - Dims::dim7,
   };

   typedef typename collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T >::type type;
};

/**
 * power type generator.
 */
template< typename Dims, int N, typename T >
struct power
{
   enum {
      d1 = N * Dims::dim1,
      d2 = N * Dims::dim2,
      d3 = N * Dims::dim3,
      d4 = N * Dims::dim4,
      d5 = N * Dims::dim5,
      d6 = N * Dims::dim6,
      d7 = N * Dims::dim7,
   };

   typedef typename collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T >::type type;
};

/**
 * root type generator.
 */
template< typename Dims, int N, typename T >
struct root
{
   enum
   {
      all_even_multiples =
         Dims::dim1 % N == 0 &&
         Dims::dim2 % N == 0 &&
         Dims::dim3 % N == 0 &&
         Dims::dim4 % N == 0 &&
         Dims::dim5 % N == 0 &&
         Dims::dim6 % N == 0 &&
         Dims::dim7 % N == 0
   };

   enum
   {
      d1 = Dims::dim1 / N,
      d2 = Dims::dim2 / N,
      d3 = Dims::dim3 / N,
      d4 = Dims::dim4 / N,
      d5 = Dims::dim5 / N,
      d6 = Dims::dim6 / N,
      d7 = Dims::dim7 / N
   };

   typedef typename collapse< dimensions< d1, d2, d3, d4, d5, d6, d7 >, T >::type type;
};

} // namespace detail

/**
 * \brief class "quantity" is the heart of the library. It associates
 * dimensions  with a single "Rep" data member and protects it from
 * dimensionally inconsistent use.
 */
template< typename Dims, typename T /*= Rep */ >
class quantity
{
public:
   typedef Dims dimension_type;

   typedef T value_type;

   typedef quantity< Dims, T > this_type;

   quantity()
   {
   }

#ifndef PHYS_UNITS_COMPILER_IS_MSVC6
   // default destructor is ok
   // default copy constructor is ok
   // default assignment operator is ok

   /**
    * converting copy-assignment constructor.
    */
   template < typename Y >
   quantity( quantity< Dims, Y > const & rhs )
   : m_value( rhs.get( detail::permit<Y>() ) )
   {
   }

   /**
    * converting assignment operator.
    */
   template < typename Y >
   this_type & operator=( quantity< Dims, Y > const & rhs )
   {
      m_value = rhs.get( detail::permit<Y>() );
      return *this;
   }

#else // VC6 requires complete specialization

   // default destructor is ok

   #define PHYS_UNITS_VC6_GEN_CTOR_CPYASN( T ) \
      quantity( quantity< Dims, T > const & rhs ) \
      : m_value( rhs.get( detail::permit<T>() ) ) {}

   /**
    * converting copy-assignment constructor(s).
    */
   PHYS_UNITS_VC6_GEN_CTOR_CPYASN( float );
   PHYS_UNITS_VC6_GEN_CTOR_CPYASN( double );
   PHYS_UNITS_VC6_GEN_CTOR_CPYASN( long double );

   /**
    * converting assignment operator(s).
    */
   #define PHYS_UNITS_VC6_GEN_OPERATOR_ASN( T ) \
   this_type & operator=( quantity< Dims, T > const & rhs ) \
   { \
      m_value = rhs.get( detail::permit<T>() ); \
      return *this; \
   }

   PHYS_UNITS_VC6_GEN_OPERATOR_ASN( float );
   PHYS_UNITS_VC6_GEN_OPERATOR_ASN( double );
   PHYS_UNITS_VC6_GEN_OPERATOR_ASN( long double );

   #undef PHYS_UNITS_VC6_GEN_CTOR_CPYASN
   #undef PHYS_UNITS_VC6_GEN_OPERATOR_ASN
#endif

   /**
    * We need a "zero" of each type -- for comparisons, to initialize running
    * totals, etc.  Note:  0 m != 0 kg, since they are of different dimensionality.
    * The zero() function is really just defined for convenience, since
    * quantity< length_d >::zero() == 0 * meter(), etc.
    */
   static quantity zero()
   {
      return quantity( value_type( 0.0 ) );
   }

   // MSVC appears to get confused by certain binary operators and functions
   // which have two template parameters.  It has better luck when such things
   // are defined as members of the lhs.

   /**
    * multiply, as member function to please VC6.
    */
   template< typename RhsDims, typename Y >
   typename detail::product< Dims, RhsDims, PHYS_UNITS_PROMOTE(value_type,Y) >::type
   operator*( quantity< RhsDims, Y > const & rhs ) const
   {
      typedef PHYS_UNITS_PROMOTE(value_type,Y) result_value_type;

      return TYPENAME_TYPE_K detail::product< Dims, RhsDims, result_value_type >::type (
         detail::permit<result_value_type>( m_value * rhs.get( detail::permit<Y>() ) ) );
   }

   /**
    * divide, as member function to please VC6.
    */
   template< typename RhsDims, typename Y >
   typename detail::quotient< Dims, RhsDims, PHYS_UNITS_PROMOTE(value_type,Y) >::type
   operator/( quantity< RhsDims, Y > const & rhs ) const
   {
      typedef PHYS_UNITS_PROMOTE(value_type,Y) result_value_type;

      return TYPENAME_TYPE_K detail::quotient< Dims, RhsDims, result_value_type >::type (
         detail::permit<result_value_type>( m_value / rhs.get( detail::permit<Y>() ) ) );
   }

   /**
    * The "permit" constructor and accessors allow access by functions that
    * should really just be declared as friends and refer directly to the
    * private members.
    */
   explicit quantity( detail::permit< value_type > const & p )
   : m_value( p.m_value )
   {
   }

   /**
    * permit access to value (non-const).
    */
   value_type & get( detail::permit< value_type > const & )
   {
      return m_value;
   }

   /**
    * permit access to value (const).
    */
   const value_type & get( detail::permit< value_type > const & ) const
   {
      return m_value;
   }

private:
   /**
    * private initializing constructor.
    */
   explicit quantity( value_type val )
   : m_value( val )
   {
   }

   value_type m_value;

   enum { ok = ! Dims::is_all_zero };

   PHYS_UNITS_STATIC_ASSERT_TYPE( ok, quantity_dimensions_must_not_all_be_zero );
};

// Give names to the seven fundamental dimensions of physical reality.

typedef dimensions< 1, 0, 0, 0, 0, 0, 0 > length_d;
typedef dimensions< 0, 1, 0, 0, 0, 0, 0 > mass_d;
typedef dimensions< 0, 0, 1, 0, 0, 0, 0 > time_interval_d;
typedef dimensions< 0, 0, 0, 1, 0, 0, 0 > electric_current_d;
typedef dimensions< 0, 0, 0, 0, 1, 0, 0 > thermodynamic_temperature_d;
typedef dimensions< 0, 0, 0, 0, 0, 1, 0 > amount_of_substance_d;
typedef dimensions< 0, 0, 0, 0, 0, 0, 1 > luminous_intensity_d;

// We define all the operators here.  Most could be defined as members of the
// quantity class, but that would really clutter up the class definition.
// It seems simpler to keep all the additions in one place, and so on.

// Addition operators

/**
 * quan += quan
 */
template< typename Dims, typename X, typename Y >
inline quantity< Dims, X > &
operator+=( quantity< Dims, X > & lhs, quantity< Dims, Y > const & rhs )
{
   lhs.get( detail::permit<X>() ) += rhs.get( detail::permit<Y>() );
   return lhs;
}

/**
 * + quan
 */
template< typename Dims, typename X >
inline quantity< Dims, X >
operator+( quantity< Dims, X > const & rhs )
{
   return quantity< Dims, X >( detail::permit<X>( + rhs.get( detail::permit<X>() ) ) );
}

/**
 * quan + quan
 */
template< typename Dims, typename X, typename Y >
inline quantity< Dims, PHYS_UNITS_PROMOTE(X,Y) >
operator+( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   typedef PHYS_UNITS_PROMOTE(X,Y) result_value_type;

   return quantity< Dims, result_value_type >( detail::permit<result_value_type>(
      lhs.get( detail::permit<X>() ) + rhs.get( detail::permit<Y>() ) )
   );
}

// Subtraction operators

/**
 * quan -= quan
 */
template< typename Dims, typename X, typename Y >
inline quantity< Dims, X > &
operator-=( quantity< Dims, X > & lhs, quantity< Dims, Y > const & rhs )
{
   lhs.get( detail::permit<X>() ) -= rhs.get( detail::permit<Y>() );
   return lhs;
}

/**
 * - quan
 */
template< typename Dims, typename X >
inline quantity< Dims, X >
operator-( quantity< Dims, X > const & rhs )
{
   return quantity< Dims, X >( detail::permit<X>( - rhs.get( detail::permit<X>() ) ) );
}

/**
 * quan - quan
 */
template< typename Dims, typename X, typename Y >
inline quantity< Dims, PHYS_UNITS_PROMOTE(X,Y) >
operator-( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   typedef PHYS_UNITS_PROMOTE(X,Y) result_value_type;

   return quantity< Dims, result_value_type >( detail::permit< result_value_type >(
      lhs.get( detail::permit<X>() ) - rhs.get( detail::permit<Y>() ) )
   );
}

// Multiplication operators

/**
 * quan *= num
 */
template< typename Dims, typename X >
inline quantity< Dims, X > &
operator*=( quantity< Dims, X > & lhs, const Rep & rhs )
{
   lhs.get( detail::permit<X>() ) *= rhs;
   return lhs;
}

/**
 * quan * num
 */
template< typename Dims, typename X >
inline quantity< Dims, PHYS_UNITS_PROMOTE(X,Rep) >
operator*( quantity< Dims, X > const & lhs, const Rep & rhs )
{
   typedef PHYS_UNITS_PROMOTE(X,Rep) result_value_type;

   return quantity< Dims, result_value_type >( detail::permit< result_value_type >(
      lhs.get( detail::permit<X>() ) * rhs )
   );
}

/**
 * num * quan
 */
template< typename Dims, typename Y >
inline quantity< Dims, PHYS_UNITS_PROMOTE(Rep,Y) >
operator*( const Rep & lhs, quantity< Dims, Y > const & rhs )
{
   typedef PHYS_UNITS_PROMOTE(Rep,Y) result_value_type;

   return quantity< Dims, result_value_type >( detail::permit< result_value_type >(
      lhs * rhs.get( detail::permit<Y>() ) )
   );
}

// quan * quan: defined as member for portability (VC6)

// Division operators

/**
 * quan /= num
 */
template< typename Dims, typename X, typename Y >
inline quantity< Dims, X > &
operator/= ( quantity< Dims, X > & lhs, const Y & rhs )
{
   lhs.get( detail::permit<X>() ) /= rhs;
   return lhs;
}

/**
 * quan / num
 */
template< typename Dims, typename X >
inline quantity< Dims, PHYS_UNITS_PROMOTE(X,Rep) >
operator/( quantity< Dims, X > const & lhs, const Rep & rhs )
{
   typedef PHYS_UNITS_PROMOTE(X,Rep) result_value_type;

   return quantity< Dims, result_value_type >( detail::permit< result_value_type >(
      lhs.get( detail::permit<X>() ) / rhs )
   );
}

/**
 * num / quan
 */
template< typename Dims, typename Y >
inline typename detail::reciprocal< Dims, PHYS_UNITS_PROMOTE(Rep,Y) >::type
operator/( const Rep & lhs, quantity< Dims, Y > const & rhs )
{
   typedef PHYS_UNITS_PROMOTE(Rep,Y) result_value_type;

   return TYPENAME_TYPE_K detail::reciprocal< Dims, result_value_type >::type(
      detail::permit< result_value_type >( lhs / rhs.get( detail::permit<Y>() ) )
   );
}

// quan / quan: defined as member for portability (VC6)

/**
 * return absolute value.
 * NTS: fabs() vs. std::abs()
 */
template < typename T, typename U >
inline quantity<T,U> abs( quantity<T,U> const & x )
{
   return quantity<T,U>( detail::permit<U>( fabs( x.get( detail::permit<U>() ) ) ) );
}

// General powers

/**
 * N-th power.
 */
template< int N, typename Dims, typename T >
typename detail::power< Dims, N, T >::type
nth_power( quantity< Dims, T > const & rhs )
{
   return TYPENAME_TYPE_K detail::power< Dims, N, T >::type(
      detail::permit<T>( T( pow( rhs.get( detail::permit<T>() ), T( N ) ) ) )
   );
}

// Low powers defined separately for efficiency.

/**
 * square.
 */
template< typename Dims, typename T >
inline typename detail::power< Dims, 2, T >::type
square( quantity< Dims, T > const & arg )
{
   return arg * arg;
}

/**
 * cube.
 */
template< typename Dims, typename T >
inline typename detail::power< Dims, 3, T >::type
cube( quantity< Dims, T > const & arg )
{
   return arg * arg * arg;
}

// General root

/**
 * n-th root.
 */
template< int N, typename Dims, typename T >
typename detail::root< Dims, N, T >::type
nth_root( quantity< Dims, T > const & rhs )
{
   PHYS_UNITS_STATIC_ASSERT_TYPE( (detail::root< Dims, N, T >::all_even_multiples), root_result_dimensions_must_be_integral );

   return TYPENAME_TYPE_K detail::root< Dims, N, T >::type(
      detail::permit<T>( T( pow( rhs.get( detail::permit<T>() ), T( 1.0 ) / N ) ) )
   );
}

// Low roots defined separately for convenience.

/**
 * square root.
 */
template< typename Dims, typename T >
typename detail::root< Dims, 2, T >::type
sqrt( quantity< Dims, T > const & rhs )
{
   PHYS_UNITS_STATIC_ASSERT_TYPE(
      (detail::root< Dims, 2, T >::all_even_multiples), root_result_dimensions_must_be_integral );

   return TYPENAME_TYPE_K detail::root< Dims, 2, T >::type(
      detail::permit<T>( T( pow( rhs.get( detail::permit<T>() ), T( 1.0 ) / 2 ) ) )
   );
}

// Comparison operators

/**
 * equality.
 */
template< typename Dims, typename X, typename Y >
inline bool operator==( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) == rhs.get( detail::permit<Y>() );
}

/**
 * inequality.
 */
template< typename Dims, typename X, typename Y >
inline bool operator!=( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) != rhs.get( detail::permit<Y>() );
}

/**
 * less-equal.
 */
template< typename Dims, typename X, typename Y >
inline bool operator<=( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) <= rhs.get( detail::permit<Y>() );
}

/**
 * greater-equal.
 */
template< typename Dims, typename X, typename Y >
inline bool operator>=( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) >= rhs.get( detail::permit<Y>() );
}

/**
 * less-than.
 */
template< typename Dims, typename X, typename Y >
inline bool operator<( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) < rhs.get( detail::permit<Y>() );
}

/**
 * greater-than.
 */
template< typename Dims, typename X, typename Y >
inline bool operator>( quantity< Dims, X > const & lhs, quantity< Dims, Y > const & rhs )
{
   return lhs.get( detail::permit<X>() ) > rhs.get( detail::permit<Y>() );
}

// The seven SI base units.  These tie our numbers to the real world.

inline quantity< length_d > meter()
{
   return quantity< length_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< mass_d > kilogram()
{
   return quantity< mass_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< time_interval_d > second()
{
   return quantity< time_interval_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< electric_current_d > ampere()
{
   return quantity< electric_current_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< thermodynamic_temperature_d > kelvin()
{
   return quantity< thermodynamic_temperature_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< amount_of_substance_d > mole()
{
   return quantity< amount_of_substance_d >( detail::permit<Rep>( 1.0 ) );
}

inline quantity< luminous_intensity_d > candela()
{
   return quantity< luminous_intensity_d >( detail::permit<Rep>( 1.0 ) );
}

// The standard SI prefixes.

inline Rep yotta()   { return Rep( 1e+24L ); }
inline Rep zetta()   { return Rep( 1e+21L ); }
inline Rep exa()     { return Rep( 1e+18L ); }
inline Rep peta()    { return Rep( 1e+15L ); }
inline Rep tera()    { return Rep( 1e+12L ); }
inline Rep giga()    { return Rep( 1e+9L ); }
inline Rep mega()    { return Rep( 1e+6L ); }
inline Rep kilo()    { return Rep( 1e+3L ); }
inline Rep hecto()   { return Rep( 1e+2L ); }
inline Rep deka()    { return Rep( 1e+1L ); }
inline Rep deci()    { return Rep( 1e-1L ); }
inline Rep centi()   { return Rep( 1e-2L ); }
inline Rep milli()   { return Rep( 1e-3L ); }
inline Rep micro()   { return Rep( 1e-6L ); }
inline Rep nano()    { return Rep( 1e-9L ); }
inline Rep pico()    { return Rep( 1e-12L ); }
inline Rep femto()   { return Rep( 1e-15L ); }
inline Rep atto()    { return Rep( 1e-18L ); }
inline Rep zepto()   { return Rep( 1e-21L ); }
inline Rep yocto()   { return Rep( 1e-24L ); }

// Binary prefixes, pending adoption.

inline Rep kibi() { return Rep( 1024 ); }
inline Rep mebi() { return Rep( 1024 * kibi() ); }
inline Rep gibi() { return Rep( 1024 * mebi() ); }
inline Rep tebi() { return Rep( 1024 * gibi() ); }
inline Rep pebi() { return Rep( 1024 * tebi() ); }
inline Rep exbi() { return Rep( 1024 * pebi() ); }
inline Rep zebi() { return Rep( 1024 * exbi() ); }
inline Rep yobi() { return Rep( 1024 * zebi() ); }

// The rest of the standard dimensional types, as specified in SP811.

typedef dimensions< 2, 0, -2 >            absorbed_dose_d;
typedef dimensions< 2, 0, -3 >            absorbed_dose_rate_d;
typedef dimensions< 1, 0, -2 >            acceleration_d;
typedef dimensions< 0, 0, -1 >            activity_of_a_nuclide_d;
typedef dimensions< 0, 0, -1 >            angular_velocity_d;
typedef dimensions< 0, 0, -2 >            angular_acceleration_d;
typedef dimensions< 2, 0, 0 >             area_d;
typedef dimensions< -2, -1, 4, 2 >        capacitance_d;
typedef dimensions< -3, 0, 0, 0, 0, 1 >   concentration_d;
typedef dimensions< -2, 0, 0, 1 >         current_density_d;
typedef dimensions< 2, 0, -2 >            dose_equivalent_d;
typedef dimensions< -1, 1, -1 >           dynamic_viscosity_d;
typedef dimensions< 0, 0, 1, 1 >          electric_charge_d;
typedef dimensions< -3, 0, 1, 1 >         electric_charge_density_d;
typedef dimensions< -2, -1, 3, 2 >        electric_conductance_d;
typedef dimensions< 1, 1, -3, -1 >        electric_field_strenth_d;
typedef dimensions< -2, 0, 1, 1 >         electric_flux_density_d;
typedef dimensions< 2, 1, -3, -1 >        electric_potential_d;
typedef dimensions< 2, 1, -3, -2 >        electric_resistance_d;
typedef dimensions< 2, 1, -2 >            energy_d;
typedef dimensions< -1, 1, -2 >           energy_density_d;
typedef dimensions< 0, -1, 1, 1 >         exposure_d;
typedef dimensions< 1, 1, -2 >            force_d;
typedef dimensions< 0, 0, -1 >            frequency_d;
typedef dimensions< 2, 1, -2, 0, -1 >     heat_capacity_d;
typedef dimensions< 0, 1, -2 >            heat_density_d;
typedef dimensions< 0, 1, -3 >            heat_density_flow_rate_d;
typedef dimensions< 2, 1, -3 >            heat_flow_rate_d;
typedef dimensions< 0, 1, -3 >            heat_flux_density_d;
typedef dimensions< 0, 1, -3, 0, -1 >     heat_transfer_coefficient_d;
typedef dimensions< -2, 0, 0, 0, 0, 0, 1 >   illuminance_d;
typedef dimensions< 2, 1, -2, -2 >        inductance_d;
typedef dimensions< 0, 1, -3 >            irradiance_d;
typedef dimensions< 2, 0, -1 >            kinematic_viscosity_d;
typedef dimensions< -2, 0, 0, 0, 0, 0, 1 >   luminance_d;
typedef dimensions< 0, 0, 0, 0, 0, 0, 1 > luminous_flux_d;
typedef dimensions< -1, 0, 0, 1 >         magnetic_field_strength_d;
typedef dimensions< 2, 1, -2, -1 >        magnetic_flux_d;
typedef dimensions< 0, 1, -2, -1 >        magnetic_flux_density_d;
typedef dimensions< 1, 1, -2, -2 >        magnetic_permeability_d;
typedef dimensions< -3, 1, 0 >            mass_density_d;
typedef dimensions< 0, 1, -1 >            mass_flow_rate_d;
typedef dimensions< 2, 1, -2, 0, 0, -1 >  molar_energy_d;
typedef dimensions< 2, 1, -2, -1, 0, -1 > molar_entropy_d;
typedef dimensions< 2, 1, -2 >            moment_of_force_d;
typedef dimensions< -3, -1, 4, 2 >        permittivity_d;
typedef dimensions< 2, 1, -3 >            power_d;
typedef dimensions< -1, 1, -2 >           pressure_d;
typedef dimensions< 0, 1, -3 >            radiance_d;
typedef dimensions< 2, 1, -3 >            radiant_intensity_d;
typedef dimensions< 1, 0, -1 >            speed_d;
typedef dimensions< 2, 0, -2 >            specific_energy_d;
typedef dimensions< 2, 0, -2, 0, -1 >     specific_heat_capacity_d;
typedef dimensions< 3, -1, 0 >            specific_volume_d;
typedef dimensions< -1, 0, 1 >            substance_permeability_d;
typedef dimensions< 0, 1, -2 >            surface_tension_d;
typedef dimensions< 1, 1, -3, 0, -1 >     thermal_conductivity_d;
typedef dimensions< 2, 0, -1 >            thermal_diffusivity_d;
typedef dimensions< 0, -1, 3, 0, 1 >      thermal_insulance_d;
typedef dimensions< -2, -1, 3, 0, 1 >     thermal_resistance_d;
typedef dimensions< -1, -1, 3, 0, 1 >     thermal_resistivity_d;
typedef dimensions< 2, 1, -2 >            torque_d;
typedef dimensions< 3, 0, 0 >             volume_d;
typedef dimensions< 3, 0, -1 >            volume_flow_rate_d;
typedef dimensions< -1, 0, 0 >            wave_number_d;

// Handy values.

inline Rep                                pi()           { return Rep( 3.141592653589793238462L ); }
inline Rep                                percent()      { return Rep( 1 ) / 100; }

// Not approved for use alone, but needed for use with prefixes.

inline quantity< mass_d >                 gram()         { return kilogram() / 1000; }

// The derived SI units, as specified in SP811.

inline Rep                                radian()       { return Rep( 1 ); }
inline Rep                                steradian()    { return Rep( 1 ); }
inline quantity< force_d >                newton()       { return meter() * kilogram() / square( second() ); }
inline quantity< pressure_d >             pascal()       { return newton() / square( meter() ); }
inline quantity< energy_d >               joule()        { return newton() * meter(); }
inline quantity< power_d >                watt()         { return joule() / second(); }
inline quantity< electric_charge_d >      coulomb()      { return second() * ampere(); }
inline quantity< electric_potential_d >   volt()         { return watt() / ampere(); }
inline quantity< capacitance_d >          farad()        { return coulomb() / volt(); }
inline quantity< electric_resistance_d >  ohm()          { return volt() / ampere(); }
inline quantity< electric_conductance_d > siemens()      { return ampere() / volt(); }
inline quantity< magnetic_flux_d >        weber()        { return volt() * second(); }
inline quantity< magnetic_flux_density_d > tesla()       { return weber() / square( meter() ); }
inline quantity< inductance_d >           henry()        { return weber() / ampere(); }
inline quantity< thermodynamic_temperature_d > degree_celsius()   { return kelvin(); }
inline quantity< luminous_flux_d >        lumen()        { return candela() * steradian(); }
inline quantity< illuminance_d >          lux()          { return lumen() / meter() / meter(); }
inline quantity< activity_of_a_nuclide_d > becquerel()   { return 1 / second(); }
inline quantity< absorbed_dose_d >        gray()         { return joule() / kilogram(); }
inline quantity< dose_equivalent_d >      sievert()      { return joule() / kilogram(); }
inline quantity< frequency_d >            hertz()        { return 1 / second(); }

// The rest of the units approved for use with SI, as specified in SP811.
// (However, use of these units is generally discouraged.)

inline quantity< length_d >               angstrom()     { return Rep( 1e-10L ) * meter(); }
inline quantity< area_d >                 are()          { return Rep( 1e+2L ) * square( meter() ); }
inline quantity< pressure_d >             bar()          { return Rep( 1e+5L ) * pascal(); }
inline quantity< area_d >                 barn()         { return Rep( 1e-28L ) * square( meter() ); }
inline quantity< activity_of_a_nuclide_d > curie()       { return Rep( 3.7e+10L ) * becquerel(); }
inline quantity< time_interval_d >        day()          { return Rep( 86400L ) * second(); }
inline Rep                                degree_angle() { return pi() / 180; }
inline quantity< acceleration_d >         gal()          { return Rep( 1e-2L ) * meter() / square( second() ); }
inline quantity< area_d >                 hectare()         { return Rep( 1e+4L ) * square( meter() ); }
inline quantity< time_interval_d >        hour()         { return Rep( 3600 ) * second(); }
inline quantity< speed_d >                knot()         { return Rep( 1852 ) / 3600 * meter() / second(); }
inline quantity< volume_d >               liter()        { return Rep( 1e-3L ) * cube( meter() ); }
inline quantity< time_interval_d >        minute()       { return Rep( 60 ) * second(); }
inline Rep                                minute_angle() { return pi() / 10800; }
inline quantity< length_d >               mile_nautical()   { return Rep( 1852 ) * meter(); }
inline quantity< absorbed_dose_d >        rad()          { return Rep( 1e-2L ) * gray(); }
inline quantity< dose_equivalent_d >      rem()          { return Rep( 1e-2L ) * sievert(); }
inline quantity< exposure_d >             roentgen()     { return Rep( 2.58e-4L ) * coulomb() / kilogram(); }
inline Rep                                second_angle() { return pi() / 648000L; }
inline quantity< mass_d >                 ton_metric()   { return Rep( 1e+3L ) * kilogram(); }

// Alternate (non-US) spellings:

inline quantity< length_d >               metre()        { return meter(); }
inline quantity< volume_d >               litre()        { return liter(); }
inline Rep                                deca()         { return deka(); }
inline quantity< mass_d >                 tonne()        { return ton_metric(); }

}}} // namespace ct { namespace units { namespace phys {

#undef PHYS_UNITS_PROMOTE

#ifndef PHYS_UNITS_IN_CT_NAMESPACE
using namespace ct;
#endif

#endif // PHYS_UNITS_QUANTITY_HPP_INCLUDED

/*
 * end of file
 */

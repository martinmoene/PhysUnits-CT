/**
 * \file io_output_engineering.hpp
 *
 * \brief   Engineering IO for quantity library.
 * \author  Jukka Korpela, David Hoerl, Martin Moene
 * \date    18 April 2012
 * \since   0.4
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 */

#ifndef PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

#include <iomanip>
#include <limits>

/*
 * Note: micro, µ, may not work everywhere, so you can define a glyph yourself:
 */
#ifndef PHYS_UNITS_MICRO_GLYPH
# define PHYS_UNITS_MICRO_GLYPH "µ"
#endif

/*
 * Note: if not using signed at the computation of prefix_end below,
 * VC2010 -Wall issues a warning about unsigned and addition overflow.
 * Hence the cast to signed int here.
 */
#define PHYS_UNITS_DIMENSION_OF(a) ( static_cast<int>( sizeof(a) / sizeof(*(a)) ) )

namespace ct { namespace phys { namespace units {

/**
 * format quantity in engineering units.
 * code derived from http://www.cs.tut.fi/~jkorpela/c/eng.html, by Jukka Korpela.
 */
template < typename Dims, typename T = Rep >
class eng_format
{
public:
   typedef Dims dimension_type;

   typedef T value_type;

   eng_format( quantity<Dims, T> const & q, int const digits = 6, bool const showpos = false )
   : m_magnitude()
   , m_unit()
   , m_fixed( false )
   , m_showpos( showpos )
   {
      construct( q, digits );
   }

   std::string magnitude() const
   {
      return m_magnitude;
   }

   std::string unit() const
   {
      return m_unit;
   }

   std::string repr() const
   {
      return magnitude() + " " + unit();
   }

private:
   /*
    * Note that here x is always positive, no need to round symmetrically:
    */
   static int lrint( value_type const x )
   {
      return static_cast<int>( x + std::numeric_limits<value_type>::epsilon() );
   }

   /*
    * single symbol, not being kg and prefix is within range:
    */
   static bool fits_eng_notation( int const expof10, int const prefix_start, int const prefix_end )
   {
      return unit_info<Dims>::single() && dimension_type() != mass_d()
          && prefix_start <= expof10 && expof10 <= prefix_end;
   }

   void construct( quantity<Dims, T> const & q, int digits )
   {
      static char const * prefix[] =
      {
         "y", "z", "a", "f", "p", "n", PHYS_UNITS_MICRO_GLYPH, "m", "",
         "k", "M", "G", "T", "P", "E", "Z", "Y"
      };

      // from "y" to "Y":
      const int prefix_start = -24;
      const int prefix_end   = prefix_start + 3 * ( PHYS_UNITS_DIMENSION_OF( prefix ) -1 );

      const char * sign = "";

      value_type value = q.get( detail::permit<T>() );

//       assert( isnormal( value ) ); // could also return NULL

      if( value < 0.0 )
      {
         sign  = "-";
         value = -value;
      }
      else if ( m_showpos )
      {
         sign = "+";
      }
      else
      {
         sign = "";
      }

      /*
       * correctly round to desired number of digits:
       */
      int expof10 = lrint( floor( log10( value ) ) );
      value      *= pow( 10.0, digits - 1 - expof10 );

      /*
       * contrary to VC2010 documentation, it seems that
       *   long double modf( long double, long double* )
       * isn't available; same for GCC 4.5.2.
       */
      double display = 0.0;
      value_type fract = modf( value, &display );

      if ( fract >= 0.5 )
      {
         display += 1.0;
      }

      value = display * pow( 10.0, expof10 - digits + 1 );

      if ( expof10 > 0 )
      {
         expof10 = ( expof10 / 3 ) * 3;
      }
      else
      {
         expof10 = ( ( -expof10 + 3 ) / 3 ) * (-3);
      }

      value *= pow( 10.0, -expof10 );

      if (value >= 1000.0)
      {
         value   /= 1000.0;
         expof10 += 3;
      }
      else if (value >= 100.0)
      {
         digits -= 2;
      }
      else if ( value >= 10.0 )
      {
         digits -= 1;
      }

      if ( fits_eng_notation( expof10, prefix_start, prefix_end ) )
      {
         std::ostringstream os;

         if ( m_fixed )
         {
            os << sign << std::fixed << std::setprecision(digits-1) << value;
         }
         else
         {
            os << sign << value;
         }

         m_magnitude = os.str();

         m_unit = std::string( prefix[ ( expof10 - prefix_start ) / 3] );
      }
      else
      {
         std::ostringstream os;

         if ( m_fixed )
         {
            os << sign << std::fixed << std::setprecision(digits-1) << value << "e" << expof10;
         }
         else
         {
            os << sign << value << "e" << expof10;
         }
         m_magnitude = os.str();
      }

      m_unit += to_unit_symbol( q );
   }

private:
   std::string m_magnitude;
   std::string m_unit;
   bool m_fixed;
   bool m_showpos;
};

template< typename Dims, typename T >
std::string to_eng_magnitude( quantity<Dims, T> const & q, int const digits = 6, bool const showpos = false )
{
   return eng_format<Dims, T>( q, digits, showpos ).magnitude();
}

template< typename Dims, typename T >
std::string to_eng_unit( quantity<Dims, T> const & q )
{
   return eng_format<Dims, T>( q ).unit();
}

template< typename Dims, typename T >
std::string to_eng_string( quantity<Dims, T> const & q, int const digits = 6, bool const showpos = false )
{
   return eng_format<Dims, T>( q, digits, showpos ).repr();
}

namespace io {
namespace eng {

template< typename Dims, typename T >
std::string to_string( quantity<Dims, T> const & q, int const digits = 6, bool const showpos = false )
{
   return to_eng_string( q, digits, showpos );
}

template< typename Dims, typename T >
inline std::ostream & operator<<( std::ostream & os, quantity< Dims, T > const & q )
{
   return os << to_string( q );
}

} // namespace eng
} // namespace io

}}} // namespace ct { namespace units { namespace phys {

#endif // PHYS_UNITS_QUANTITY_IO_ENGINEERING_HPP_INCLUDED

/*
 * end of file
 */


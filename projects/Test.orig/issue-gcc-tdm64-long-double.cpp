
// cl -W3 -EHsc -I.. issue-gcc-tdm64-long-double.cpp

// g++ -Wall -I.. -o issue-gcc-tdm64-long-double.exe issue-gcc-tdm64-long-double.cpp

// g++ (tdm64-1) 4.6.1 doesn't format long doubles nicely on Win7 64-bit

#include <iostream> // enable use of std::cout in quantity.hpp

//#define PHYS_UNITS_REP_TYPE double
#define PHYS_UNITS_REP_TYPE long double

#include "phys/units/quantity.hpp"              // required
#include "phys/units/quantity_io.hpp"           // required for operator<<

using phys::units::quantity;
using phys::units::length_d;
using phys::units::meter;

int main()
{
   std::cout << "sizeof( long double ): " << sizeof( long double ) << std::endl;

   long double ld = 1.23456789123456789L;

   std::cout << "long double 1.23...: " << ld << std::endl;
   std::cout << "meter(): " << meter() << std::endl;

   quantity<length_d >             q   = meter();
   quantity<length_d, double>      qd  = meter();
   quantity<length_d, long double> qld = meter();

//   qld.get( phys::units::detail::permit<long double>() );

   std::cout << "quantity<length_d > q: "               << q << std::endl;
   std::cout << "quantity<length_d, double> qd: "       << qd << std::endl;
   std::cout << "quantity<length_d, long double> qld: " << qld << std::endl;

   std::ostringstream os;
   os << meter();
   std::cout << "ostringstream << meter(), os.str():" << os.str() << std::endl;

   return 0;
}

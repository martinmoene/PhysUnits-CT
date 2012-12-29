/*
 * TestArithmetic.cpp
 *
 * Created by Martin on 27 December 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "TestUtil.hpp"

#include "catch.hpp"
//#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

#ifdef PHYS_UNITS_IN_CT_NAMESPACE
using namespace ct::phys::units;
using namespace ct::phys::units::io;
#else
using namespace phys::units;
using namespace phys::units::io;
#endif

TEST_CASE( "quantity/operator/arithmetic", "Quantity arithmetic operators" )
{
    // constructors

    quantity<area_d> a1;
    quantity<area_d> a2( meter() * meter() );
    REQUIRE( b( a2 ) == "1.000000 m+2" );

    // assignment

    a1 = 3 * meter() * meter();
    REQUIRE( b( a1 ) == "3.000000 m+2" );
    a2 = 4 * meter() * meter();
    REQUIRE( b( a2 ) == "4.000000 m+2" );

    // addition

    a1 = 5 * meter() * meter();
    a2 = 6 * meter() * meter();
    a1 += a2;
    REQUIRE( b( a1 ) == "11.000000 m+2" );

    REQUIRE( b( a1 ) == "11.000000 m+2" );

    REQUIRE( b( a1 + a2 ) == "17.000000 m+2" );

    // subtraction

    a1 = 9 * meter() * meter();
    a2 = 7 * meter() * meter();
    a1 -= a2;
    REQUIRE( b( a1 ) == "2.000000 m+2" );

    REQUIRE( b( -a1 ) == "-2.000000 m+2" );

    REQUIRE( b( a1 - a2 ) == "-5.000000 m+2" );
    REQUIRE( b( a2 - a1 ) == "5.000000 m+2" );

    // multiplication

    quantity<speed_d> s1( 8 * meter() / second() );
    quantity<speed_d> s2( 20 * meter() / second() );
    quantity<time_interval_d> t( 5 * second() );
    quantity<length_d> len( 4 * meter() );

    s1 *= 2;
    REQUIRE( b( s1 ) == "16.000000 m s-1" );

    REQUIRE( b( s1 * s2 ) == "320.000000 m+2 s-2" );
    REQUIRE( b( s1 * len ) == "64.000000 m+2 s-1" );
    REQUIRE( b( s1 * 3 ) == "48.000000 m s-1" );
    REQUIRE( b( 5 * s1 ) == "80.000000 m s-1" );

    // division

    s2 /= 5;
    REQUIRE( b( s2 ) == "4.000000 m s-1" );

    REQUIRE( b( s2 / s2 ) == "1.000000" );
    REQUIRE( b( s2 / t ) == "0.800000 m s-2" );
    REQUIRE( b( s2 / 8 ) == "0.500000 m s-1" );
    REQUIRE( b( 8 / s2 ) == "2.000000 m-1 s" );
}

TEST_CASE( "quantity/operator/arithmetic/compile-time error", "" )
{
    quantity<length_d> q( meter() );

    q = meter();
// uncomment next line for compile-time error:
//    q = second();
}

/*
 * end of file
 */

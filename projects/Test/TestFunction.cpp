/*
 * TestFunction.cpp
 *
 * Created by Martin on 27 December 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "TestUtil.hpp"

#include "catch.hpp"
#include "phys/units/quantity.hpp"

#ifdef PHYS_UNITS_IN_CT_NAMESPACE
using namespace ct::phys::units;
using namespace ct::phys::units::io;
#else
using namespace phys::units;
using namespace phys::units::io;
#endif

TEST_CASE( "quantity/function/power", "Quantity power functions" )
{
    // general powers

    quantity<force_d> f1( 2 * newton() );

    REQUIRE( b(nth_power<10>( f1 ) ) == "1024.000000 m+10 kg+10 s-20" );
    REQUIRE( b(nth_power< 4>( f1 ) ) == "16.000000 m+4 kg+4 s-8" );
    REQUIRE( b(nth_power< 3>( f1 ) ) == "8.000000 m+3 kg+3 s-6" );
    REQUIRE( b(nth_power< 2>( f1 ) ) == "4.000000 m+2 kg+2 s-4" );
    REQUIRE( b(nth_power< 1>( f1 ) ) == "2.000000 m kg s-2" );
    REQUIRE( b(nth_power< 0>( f1 ) ) == "1.000000" );
    REQUIRE( b(nth_power<-1>( f1 ) ) == "0.500000 m-1 kg-1 s+2" );
    REQUIRE( b(nth_power<-2>( f1 ) ) == "0.250000 m-2 kg-2 s+4" );

    // special powers

    REQUIRE( b(square( f1 ) ) == "4.000000 m+2 kg+2 s-4" );
    REQUIRE( b(cube( f1 ) ) == "8.000000 m+3 kg+3 s-6" );
}

TEST_CASE( "quantity/function/root", "Quantity root functions" )
{
    // general roots

    quantity<dimensions< 4, 0, 0 > > hv( 10000 * meter() * meter() * meter() * meter() );

    REQUIRE( b(nth_root< 4>( hv ) ) == "10.000000 m" );
    REQUIRE( b(nth_root< 2>( hv ) ) == "100.000000 m+2" );
    REQUIRE( b(nth_root< 1>( hv ) ) == "10000.000000 m+4" );
    REQUIRE( b(nth_root<-1>( hv ) ) == "0.000100 m-4" );
    REQUIRE( b(nth_root<-2>( hv ) ) == "0.010000 m-2" );
    REQUIRE( b(nth_root<-4>( hv ) ) == "0.100000 m-1" );

    // special roots

    REQUIRE( b(sqrt( hv ) ) == "100.000000 m+2" );

    quantity<power_d> p1( 3 * watt() );
    quantity<power_d> p2( 4 * watt() );

    REQUIRE( b(sqrt( square( p1 ) + square( p2 ) ) ) == "5.000000 m+2 kg s-3" );

    quantity<frequency_d> freq( 25 / second() );
    quantity<dimensions< 0, 0, -1, 2> > thing( 9 * ampere() * ampere() / second() );

    REQUIRE( b(sqrt( freq * thing ) ) == "15.000000 s-1 A" );
}

TEST_CASE( "quantity/function/various", "Quantity, various functions" )
{
    quantity<length_d> m( meter() );
    // abs
    REQUIRE( b(abs(  m ) ) == "1.000000 m" );
    REQUIRE( b(abs( +m ) ) == "1.000000 m" );
    REQUIRE( b(abs( -m ) ) == "1.000000 m" );
}

TEST_CASE( "quantity/function/exception", "Quantity function exceptions" )
{
// dimension powers must be even mutiples:
// uncomment next line fr compile-time error:
//    nth_root<2>( meter() * meter() / second() );

// quantity must be dimensionless when used in cast (regardless destination):
// uncomment next line fr compile-time error:
//    double d = meter();
}

/*
 * end of file
 */

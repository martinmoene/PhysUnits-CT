/*
 * TestCompile.cpp
 *
 * Created by Martin on 27 December 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "catch.hpp"
#include "phys/units/quantity.hpp"

#ifdef PHYS_UNITS_IN_CT_NAMESPACE
using namespace ct::phys::units;
#else
using namespace phys::units;
#endif

void compile()
{
    meter();
    meter() + meter();
    meter() - meter();
    meter() * meter();
    meter() / meter();

    meter() == meter();
    meter() != meter();

    meter() <  meter();
    meter() <= meter();
    meter() >  meter();
    meter() >= meter();

    quantity<length_d> m( meter() );
    m += meter();
    m -= meter();
    quantity<area_d> m2 = m * meter();
    m = m2 / meter();

    double value1 = meter() / meter();
    int    value2 = meter() / meter();

//    product ( length_d, length_d );
//    quotient( length_d, length_d );
//    quotient( length_d, length_d );
//    reciprocal( length_d );
    nth_power<2>( meter() );
    nth_root<2> ( meter() * meter() );
}

/*
 * end of file
 */

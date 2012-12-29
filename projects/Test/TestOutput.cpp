/*
 * TestOutput.cpp
 *
 * Created by Martin on 17 October 2012.
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

TEST_CASE( "output/convert", "Quantity output conversions" )
{
}

TEST_CASE( "output/exception", "Quantity output exceptions" )
{
    REQUIRE_THROWS_AS( prefix( "x" ), prefix_error );
}

/*
 * end of file
 */

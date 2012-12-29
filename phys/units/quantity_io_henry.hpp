/**
 * \file quantity_io_henry.hpp
 *
 * \brief   henry, inductance.
 * \author  Martin Moene
 * \date    22 February 2012
 * \since   1.0.0
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 */

#ifndef PHYS_UNITS_QUANTITY_IO_HENRY_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_HENRY_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

namespace ct { namespace phys { namespace units {

/**
 * henry, [H].
 */
template<>
struct unit_info< inductance_d >
{
    static bool        single() { return true; }
    static std::string name()   { return "henry"; }
    static std::string symbol() { return "H"; }
};

}}} // namespace ct { namespace units { namespace phys {

#endif // PHYS_UNITS_QUANTITY_IO_HENRY_HPP_INCLUDED

/*
 * end of file
 */

/**
 * \file quantity_io_lux.hpp
 *
 * \brief   lux, illuminance.
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

#ifndef PHYS_UNITS_QUANTITY_IO_LUX_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_LUX_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

namespace ct { namespace phys { namespace units {

/**
 * lux, [lx].
 */
template<>
struct unit_info< illuminance_d >
{
    static bool        single() { return true; }
    static std::string name()   { return "lux"; }
    static std::string symbol() { return "lx"; }
};

}}} // namespace ct { namespace units { namespace phys {

#endif // PHYS_UNITS_QUANTITY_IO_LUX_HPP_INCLUDED

/*
 * end of file
 */

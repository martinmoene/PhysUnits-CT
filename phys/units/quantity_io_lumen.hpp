/**
 * \file quantity_io_lumen.hpp
 *
 * \brief   lumen, luminous flux.
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

#ifndef PHYS_UNITS_QUANTITY_IO_LUMEN_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_IO_LUMEN_HPP_INCLUDED

#include "phys/units/quantity_io.hpp"

namespace ct { namespace phys { namespace units {

/**
 * lumen, [lm].
 */
template<>
struct unit_info< luminous_flux_d >
{
    static bool        single() { return true; }
    static std::string name()   { return "lumen"; }
    static std::string symbol() { return "lm"; }
};

}}} // namespace ct { namespace units { namespace phys {

#endif // PHYS_UNITS_QUANTITY_IO_LUMEN_HPP_INCLUDED

/*
 * end of file
 */

/**
 * \file physical_constants.hpp
 *
 * \brief   .
 * \author  Michael S. Kenniston
 * \date    16 July 2001
 * \since   0.4
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
 * http://physics.nist.gov/Document/sp811.pdf, or from other NIST
 * web pages.
 */

#ifndef PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED
#define PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace ct { namespace phys { namespace units {

// acceleration of free-fall, standard
inline quantity< acceleration_d > g_sub_n() { return Rep( 9.80665L ) * meter() / square( second() ); }

// Avogadro constant
inline quantity< dimensions< 0, 0, 0, 0, 0, -1 > >
                                  N_sub_A() { return mole() / mole() * // to help msvc
                                             Rep( 6.02214199e+23L ) / mole(); }
// electronvolt
inline quantity< energy_d >            eV() { return Rep( 1.60217733e-19L ) * joule(); }

// elementary charge
inline quantity< electric_charge_d >    e() { return Rep( 1.602176462e-19L ) * coulomb(); }

// Planck constant
inline quantity< dimensions< 2, 1, -1 > >
                                        h() { return Rep( 6.62606876e-34L ) * joule() * second(); }

// speed of light in a vacuum
inline quantity< speed_d >              c() { return Rep( 299792458L ) * meter() / second(); }

// unified atomic mass unit
inline quantity< mass_d >               u() { return Rep( 1.6605402e-27L ) * kilogram(); }

// etc.

}}} // namespace ct { namespace units { namespace phys {

#endif // PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED

/*
 * end of file
 */

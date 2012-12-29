/**
 * \file other_units.hpp
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
 * http://physics.nist.gov/Document/sp811.pdf
 * Other sources: OED = Oxford English Dictionary
 *
 * This file contains the definitions of units that are *NOT* approved
 * for use with SI, as specified by SP811.  These units should not
 * be used with any new work.  However, they may be needed for
 * handling and converting legacy data.
 */

#ifndef PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED
#define PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace ct { namespace phys { namespace units {

inline quantity< electric_current_d >     abampere()        { return Rep( 1e+1L ) * ampere(); }
inline quantity< electric_charge_d >      abcoulomb()       { return Rep( 1e+1L ) * coulomb(); }
inline quantity< capacitance_d >          abfarad()         { return Rep( 1e+9L ) * farad(); }
inline quantity< inductance_d >           abhenry()         { return Rep( 1e-9L ) * henry(); }
inline quantity< electric_conductance_d > abmho()           { return Rep( 1e+9L ) * siemens(); }
inline quantity< electric_resistance_d >  abohm()           { return Rep( 1e-9L ) * ohm(); }
inline quantity< electric_potential_d >   abvolt()          { return Rep( 1e-8L ) * volt(); }
inline quantity< area_d >                 acre()            { return Rep( 4.046873e+3L ) * square( meter() ); }
inline quantity< volume_d >               acre_foot()       { return Rep( 1.233489e+3L ) * cube( meter() ); }
inline quantity< length_d >               astronomical_unit() { return Rep( 1.495979e+11L ) * meter(); }
inline quantity< pressure_d >             atmosphere_std()  { return Rep( 1.01325e+5L ) * pascal(); }
inline quantity< pressure_d >             atmosphere_tech() { return Rep( 9.80665e+4L ) * pascal(); }

inline quantity< volume_d >               barrel()          { return Rep( 1.589873e-1L ) * cube( meter() ); }
inline quantity< electric_current_d >     biot()            { return Rep( 1e+1L ) * ampere(); }
inline quantity< energy_d >               btu()             { return Rep( 1.05587e+3L ) * joule(); }
inline quantity< energy_d >               btu_it()          { return Rep( 1.055056e+3L ) * joule(); }
inline quantity< energy_d >               btu_th()          { return Rep( 1.054350e+3L ) * joule(); }
inline quantity< energy_d >               btu_39F()         { return Rep( 1.05967e+3L ) * joule(); }
inline quantity< energy_d >               btu_59F()         { return Rep( 1.05480e+3L ) * joule(); }
inline quantity< energy_d >               btu_60F()         { return Rep( 1.05468e+3L ) * joule(); }
inline quantity< volume_d >               bushel()          { return Rep( 3.523907e-2L ) * cube( meter() ); }

inline quantity< energy_d >               calorie()         { return Rep( 4.19002L ) * joule(); }
inline quantity< energy_d >               calorie_it()      { return Rep( 4.1868L ) * joule(); }
inline quantity< energy_d >               calorie_th()      { return Rep( 4.184L ) * joule(); }
inline quantity< energy_d >               calorie_15C()     { return Rep( 4.18580L ) * joule(); }
inline quantity< energy_d >               calorie_20C()     { return Rep( 4.18190L ) * joule(); }
inline quantity< mass_d >                 carat_metric()    { return Rep( 2e-4L ) * kilogram(); }
inline quantity< length_d >               chain()           { return Rep( 2.011684e+1L ) * meter(); }
inline quantity< thermal_insulance_d >    clo()             { return Rep( 1.55e-1L ) * square( meter() ) * kelvin() / watt(); }
inline quantity< pressure_d >             cm_mercury()      { return Rep( 1.333224e+3L ) * pascal(); }
inline quantity< volume_d >               cord()            { return Rep( 3.624556L ) * cube( meter() ); }
inline quantity< volume_d >               cup()             { return Rep( 2.365882e-4L ) * cube( meter() ); }

inline quantity< dimensions< 2, 0, 0 > >  darcy()           { return Rep( 9.869233e-13L ) * square( meter() ); }
inline quantity< time_interval_d >        day_sidereal()    { return Rep( 8.616409e+4L ) * second(); }
inline quantity< dimensions< 1, 0, 1, 1 > >  debye()        { return Rep( 3.335641e-30L ) * coulomb() * meter(); }
inline quantity< thermodynamic_temperature_d > degree_fahrenheit(){return Rep( 5.555556e-1L ) * kelvin(); }
inline quantity< thermodynamic_temperature_d > degree_rankine()   { return Rep( 5.555556e-1L ) * kelvin(); }
inline quantity< dimensions< -1, 1, 0 > > denier()          { return Rep( 1.111111e-7L ) * kilogram() / meter(); }
inline quantity< force_d >                dyne()            { return Rep( 1e-5L ) * newton(); }

inline quantity< energy_d >               erg()             { return Rep( 1e-7L ) * joule(); }

inline quantity< electric_charge_d >      faraday()         { return Rep( 9.648531e+4L ) * coulomb(); }
inline quantity< length_d >               fathom()          { return Rep( 1.828804L ) * meter(); }
inline quantity< length_d >               fermi()           { return Rep( 1e-15L ) * meter(); }
inline quantity< length_d >               foot()            { return Rep( 3.048e-1L ) * meter(); }
inline quantity< energy_d >               foot_pound_force() { return Rep( 1.355818L ) * joule(); }
inline quantity< energy_d >               foot_poundal()    { return Rep( 4.214011e-2L ) * joule(); }
inline quantity< length_d >               foot_us_survey()  { return Rep( 3.048006e-1L ) * meter(); }
inline quantity< illuminance_d >          footcandle()      { return Rep( 1.076391e+1L ) * lux(); }
inline quantity< illuminance_d >          footlambert()     { return Rep( 3.426259L ) * candela() / square( meter() ); }
inline quantity< time_interval_d >        fortnight()       { return Rep( 14 ) * day(); } // from OED
inline quantity< electric_charge_d >      franklin()        { return Rep( 3.335641e-10L ) * coulomb(); }
inline quantity< length_d >               furlong()         { return Rep( 2.01168e+2L ) * meter(); } // from OED

inline quantity< volume_d >               gallon_imperial() { return Rep( 4.54609e-3L ) * cube( meter() ); }
inline quantity< volume_d >               gallon_us()       { return Rep( 3.785412e-3L ) * cube( meter() ); }
inline quantity< magnetic_flux_density_d > gamma()          { return Rep( 1e-9L ) * tesla(); }
inline quantity< mass_d >                 gamma_mass()      { return Rep( 1e-9L ) * kilogram(); }
inline quantity< magnetic_flux_density_d > gauss()          { return Rep( 1e-4L ) * tesla(); }
inline quantity< electric_current_d >     gilbert()         { return Rep( 7.957747e-1L ) * ampere(); }
inline quantity< volume_d >               gill_imperial()   { return Rep( 1.420653e-4L ) * cube( meter() ); }
inline quantity< volume_d >               gill_us()         { return Rep( 1.182941e-4L ) * cube( meter() ); }
inline Rep                                gon()             { return Rep( 9e-1L ) * degree_angle(); }
inline quantity< mass_d >                 grain()           { return Rep( 6.479891e-5L ) * kilogram(); }

inline quantity< power_d >                horsepower()         { return Rep( 7.456999e+2L ) * watt(); }
inline quantity< power_d >                horsepower_boiler()  { return Rep( 9.80950e+3L ) * watt(); }
inline quantity< power_d >                horsepower_electric(){return Rep( 7.46e+2L ) * watt(); }
inline quantity< power_d >                horsepower_metric()  { return Rep( 7.354988e+2L ) * watt(); }
inline quantity< power_d >                horsepower_uk()      { return Rep( 7.4570e+2L ) * watt(); }
inline quantity< power_d >                horsepower_water()   { return Rep( 7.46043e+2L ) * watt(); }
inline quantity< time_interval_d >        hour_sidereal()      { return Rep( 3.590170e+3L ) * second(); }
inline quantity< mass_d >                 hundredweight_long(){ return Rep( 5.080235e+1L ) * kilogram(); }
inline quantity< mass_d >                 hundredweight_short(){ return Rep( 4.535924e+1L ) * kilogram(); }

inline quantity< length_d >               inch()            { return Rep( 2.54e-2L ) * meter(); }
inline quantity< pressure_d >             inches_mercury()  { return Rep( 3.386389e+3L ) * pascal(); }

inline quantity< wave_number_d >          kayser()          { return Rep( 1e+2 ) / meter(); }
inline quantity< force_d >                kilogram_force()  { return Rep( 9.80665 ) * newton(); }
inline quantity< force_d >                kilopond()        { return Rep( 9.80665 ) * newton(); }
inline quantity< force_d >                kip()             { return Rep( 4.448222e+3L ) * newton(); }

inline quantity< volume_d >               lambda_volume()      { return Rep( 1e-9L ) * cube( meter() ); }
inline quantity< illuminance_d >          lambert()         { return Rep( 3.183099e+3L ) * candela() / square( meter() ); }
inline quantity< heat_density_d >         langley()         { return Rep( 4.184e+4L ) * joule() / square( meter() ); }
inline quantity< length_d >               light_year()      { return Rep( 9.46073e+15L ) * meter(); }

inline quantity< magnetic_flux_d >        maxwell()         { return Rep( 1e-8L ) * weber(); }
inline quantity< electric_conductance_d > mho()             { return siemens(); }
inline quantity< length_d >               micron()          { return micro() * meter(); }
inline quantity< length_d >               mil()             { return Rep( 2.54e-5L ) * meter(); }
inline Rep                                mil_angle()       { return Rep( 5.625e-2L ) * degree_angle(); }
inline quantity< area_d >                 mil_circular()    { return Rep( 5.067075e-10L ) * square( meter() ); }
inline quantity< length_d >               mile()            { return Rep( 1.609344e+3L ) * meter(); }
inline quantity< length_d >               mile_us_survey()  { return Rep( 1.609347e+3L ) * meter(); }
inline quantity< time_interval_d >        minute_sidereal() { return Rep( 5.983617e+1L ) * second(); }

inline quantity< dimensions< -1, 0, 0, 1 > >oersted()       { return Rep( 7.957747e+1L ) * ampere() / meter(); }
inline quantity< mass_d >                 ounce_avdp()      { return Rep( 2.834952e-2L ) * kilogram(); }
inline quantity< volume_d >               ounce_fluid_imperial(){return Rep( 2.841306e-5L ) * cube( meter() ); }
inline quantity< volume_d >               ounce_fluid_us()  { return Rep( 2.957353e-5L ) * cube( meter() ); }
inline quantity< force_d >                ounce_force()     { return Rep( 2.780139e-1L ) * newton(); }
inline quantity< mass_d >                 ounce_troy()      { return Rep( 3.110348e-2L ) * kilogram(); }

inline quantity< length_d >               parsec()          { return Rep( 3.085678e+16L ) * meter(); }
inline quantity< volume_d >               peck()            { return Rep( 8.809768e-3L ) * cube( meter() ); }
inline quantity< mass_d >                 pennyweight()     { return Rep( 1.555174e-3L ) * kilogram(); }
inline quantity< substance_permeability_d >  perm_0C()      { return Rep( 5.72135e-11L ) * kilogram() / pascal() / second() / square( meter() ); }
inline quantity< substance_permeability_d >  perm_23C()     { return Rep( 5.74525e-11L ) * kilogram() / pascal() / second() / square( meter() ); }
inline quantity< illuminance_d >          phot()            { return Rep( 1e+4L ) * lux(); }
inline quantity< length_d >               pica_computer()   { return Rep( 4.233333e-3L ) * meter(); }
inline quantity< length_d >               pica_printers()   { return Rep( 4.217518e-3L ) * meter(); }
inline quantity< volume_d >               pint_dry()        { return Rep( 5.506105e-4L ) * cube( meter() ); }
inline quantity< volume_d >               pint_liquid()     { return Rep( 4.731765e-4L ) * cube( meter() ); }
inline quantity< length_d >               point_computer()  { return Rep( 3.527778e-4L ) * meter(); }
inline quantity< length_d >               point_printers()  { return Rep( 3.514598e-4L ) * meter(); }
inline quantity< dynamic_viscosity_d >    poise()           { return Rep( 1e-1L ) * pascal() * second(); }
inline quantity< mass_d >                 pound_avdp()      { return Rep( 4.5359237e-1L ) * kilogram(); }
inline quantity< force_d >                pound_force()     { return Rep( 4.448222L ) * newton(); }
inline quantity< mass_d >                 pound_troy()      { return Rep( 3.732417e-1L ) * kilogram(); }
inline quantity< force_d >                poundal()         { return Rep( 1.382550e-1L ) * newton(); }
inline quantity< pressure_d >             psi()             { return Rep( 6.894757e+3L ) * pascal(); }

inline quantity< energy_d >               quad()            { return Rep( 1e+15L ) * btu_it(); }
inline quantity< volume_d >               quart_dry()       { return Rep( 1.101221e-3L ) * cube( meter() ); }
inline quantity< volume_d >               quart_liquid()    { return Rep( 9.463529e-4L ) * cube( meter() ); }

inline Rep                                revolution()      { return Rep( 2 ) * pi(); }
inline quantity< dimensions< 1, -1, 1 > > rhe()             { return Rep( 1e+1L ) / pascal() / second(); }
inline quantity< length_d >               rod()             { return Rep( 5.029210L ) * meter(); }
inline quantity< angular_velocity_d >     rpm()             { return Rep( 1.047198e-1L ) / second(); }

inline quantity< time_interval_d >        second_sidereal() { return Rep( 9.972696e-1L ) * second(); }
inline quantity< time_interval_d >        shake()           { return Rep( 1e-8L ) * second(); }
inline quantity< mass_d >                 slug()            { return Rep( 1.459390e+1L ) * kilogram(); }
inline quantity< electric_current_d >     statampere()      { return Rep( 3.335641e-10L ) * ampere(); }
inline quantity< electric_charge_d >      statcoulomb()     { return Rep( 3.335641e-10L ) * coulomb(); }
inline quantity< capacitance_d >          statfarad()       { return Rep( 1.112650e-12L ) * farad(); }
inline quantity< inductance_d >           stathenry()       { return Rep( 8.987552e+11L ) * henry(); }
inline quantity< electric_conductance_d > statmho()         { return Rep( 1.112650e-12L ) * siemens(); }
inline quantity< electric_resistance_d >  statohm()         { return Rep( 8.987552e+11L ) * ohm(); }
inline quantity< electric_potential_d >   statvolt()        { return Rep( 2.997925e+2L ) * volt(); }
inline quantity< volume_d >               stere()           { return cube( meter() ); }
inline quantity< illuminance_d >          stilb()           { return Rep( 1e+4L ) * candela() / square( meter() ); }
inline quantity< kinematic_viscosity_d >  stokes()          { return Rep( 1e-4L ) * square( meter() ) / second(); }

inline quantity< volume_d >               tablespoon()      { return Rep( 1.478676e-5L ) * cube( meter() ); }
inline quantity< volume_d >               teaspoon()        { return Rep( 4.928922e-6L ) * cube( meter() ); }
inline quantity< dimensions< -1, 1, 0 > > tex()             { return Rep( 1e-6L ) * kilogram() / meter(); }
inline quantity< energy_d >               therm_ec()        { return Rep( 1.05506e+8L ) * joule(); }
inline quantity< energy_d >               therm_us()        { return Rep( 1.054804e+8L ) * joule(); }
inline quantity< mass_d >                 ton_assay()       { return Rep( 2.916667e-2L ) * kilogram(); }
inline quantity< force_d >                ton_force()       { return Rep( 8.896443e+3L ) * newton(); }
inline quantity< mass_d >                 ton_long()        { return Rep( 1.016047e+3L ) * kilogram(); }
inline quantity< heat_flow_rate_d >       ton_refrigeration()  { return Rep( 3.516853e+3L ) * watt(); }
inline quantity< volume_d >               ton_register()    { return Rep( 2.831685L ) * cube( meter() ); }
inline quantity< mass_d >                 ton_short()       { return Rep( 9.071847e+2L ) * kilogram(); }
inline quantity< energy_d >               ton_tnt()         { return Rep( 4.184e+9L ) * joule(); }
inline quantity< pressure_d >             torr()            { return Rep( 1.333224e+2L ) * pascal(); }

inline quantity< magnetic_flux_d >        unit_pole()       { return Rep( 1.256637e-7L ) * weber(); }

inline quantity< time_interval_d >        week()            { return Rep( 604800L ) * second(); } // 7 days

inline quantity< length_d >               x_unit()          { return Rep( 1.002e-13L ) * meter(); }

inline quantity< length_d >               yard()            { return Rep( 9.144e-1L ) * meter(); }
inline quantity< time_interval_d >        year_sidereal()   { return Rep( 3.155815e+7L ) * second(); }
inline quantity< time_interval_d >        year_std()        { return Rep( 3.1536e+7L ) * second(); } // 365 days
inline quantity< time_interval_d >        year_tropical()   { return Rep( 3.155693e+7L ) * second(); }

}}} // namespace ct { namespace units { namespace phys

#endif // PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

/*
 * end of file
 */

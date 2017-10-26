////////////////////////////////////////////////////////////////////////////////
/// @file  wave_triangle.h
/// @brief Definition of SystemC-AMS module Triangle Wave Generator
///
/// Copyright 2012-2017 AG Design of Cyber Physical Systems, TU Kaiserslautern.
///
/// @author Xiao Pan <pan@cs.uni-kl.de>,
///         Carna Radojijic <radojicic@cs.uni-kl.de>,
///         AG Design of Cyber-Physical Systems
///
/// @date   2017-06-01
///
/// @version 0.1.0
///
/// @section LICENSE License
///
///-----------------------------------------------------------------------------
/// (This code is commented throughout for use with Doxygen.)
///-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////


#ifndef _GENERATOR_WAVE_TRIANGLE_H
#define _GENERATOR_WAVE_TRIANGLE_H

#include <systemc-ams.h>


namespace sca_comlib
{
    // -------------------------------------------------------------------------
    //! @class wave_triangle
    
    //! @brief SystemC-AMS module of Triangle Wave Generator.
    
    //! The output of this module is a Triangle wave. Frequency, amplitude,
    //! and offset of the output can be set via corresponding parameters.
    // -------------------------------------------------------------------------
    class wave_triangle: public sca_tdf::sca_module{
    public:
        wave_triangle(sc_core::sc_module_name nm,
                      double    _freq,
                      double    _amp,
                      double    _ofset  = 0.0,
                      int       _rate   = 1);
        
        sca_tdf::sca_out<double> out;
        
    private:
        int rate;
        double stepsize;
        double actval;
        double amp;
        double ofset;
        double freq;
        
        
        void set_attributes();
        void initialize();
        void processing();
        
    public:

    };

} // namespace
#endif

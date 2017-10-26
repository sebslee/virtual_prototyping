////////////////////////////////////////////////////////////////////////////////
/// @file   wave_sine.cpp
/// @brief Implementation of SystemC-AMS module of Sine Waves Generator.
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


#include "../include/wave_sine.h"

using namespace sca_comlib;

// -----------------------------------------------------------------------------
//! Custom constructor for the wave_sine module

//! The constructor takes the value of frequency, amplitute, initial phase and
//! offset of the expected output signal.They are set to 1000,1.0,0.0,0.0 by
//! default, respectively. The reconfigurability of amplitude and frequency
//! can be set per the parameter "amp_c" and "freq_c". Besides, one can set
//! the data rate of output port with "datarate".

//! @param nm            The SystemC module name
//! @param _freq_def    Frequency of the generated wave
//! @param _amp_def     Amplitude of the generated wave
//! @param _phi         Initial phase
//! @param _offset      Output offset
//! @param _amp_c       Reconfigurability of amplitude
//! @param _freq_c      Reconfigurability of frequency
//! @param _rate        Output data rate
// -----------------------------------------------------------------------------
wave_sine::wave_sine(sc_core::sc_module_name nm,
                     double _freq_def,
                     double _amp_def,
                     double _phi,
                     double _offset,
                     bool   _amp_c,
                     bool   _freq_c,
                     int    _rate)
{
    if((_amp_c) && (!_freq_c))
    {
        //! create amp_in port if only amp_c is set to true
        amp_in = new sca_tdf::sca_in<double>;
        freq_recon = false;
    }
    else if((_freq_c) && (!_amp_c))
    {
        //! create freq_in port if only freq_c is set to true
        freq_in = new sca_tdf::sca_in<double>;
        ampl_recon = false;
    }
    else if(_amp_c && _freq_c)
    {
        //! create freq_in and amp_in ports if both freq_c and amp_c are set to
        //! true
        amp_in  = new sca_tdf::sca_in<double>;
        freq_in = new sca_tdf::sca_in<double>;
    }
    else
    {
        //! no creation if both freq_c and amp_c are set to false
        freq_recon = false;
        ampl_recon = false;
    }
    amp_reg     = _amp_def;
    freq_reg    = _freq_def;
    rate        = _rate;
    actval      = 0.;
    phi         = _phi;
    offset      = _offset;
}


void wave_sine::set_attributes(){
    //! set the data rate of output port
    out.set_rate(rate);
}

void wave_sine::initialize(){
    //! read time step of output port
    sample_time = out.get_timestep().to_seconds();
}

void wave_sine::processing() {
    
    if(freq_recon==true)
        //! read the frequency from mode port, and save into parameter register
        freq_reg=freq_in->read();
    
    if(ampl_recon==true)
        //! read the amplitude from amp_in port,and save into parameter register
        amp_reg=amp_in->read();
    
    //! calculate stepsize according to the time step of output port
    stepsize = sample_time*freq_reg*2.*M_PI;
    
    //! write <rate> data token for one bit
    for(int i=0; i<rate; i++)
    {
        out.write(amp_reg*sin( actval + phi )+offset,i);
        actval+=stepsize;
    }
}

void wave_sine::freq_con (sca_tdf::sca_signal<double>* f_in)
{
    (*freq_in)(*f_in);
    freq_recon = true;
}

void wave_sine::amp_con (sca_tdf::sca_signal<double>* a_in)
{
    (*amp_in)(*a_in);
    ampl_recon = true;
}

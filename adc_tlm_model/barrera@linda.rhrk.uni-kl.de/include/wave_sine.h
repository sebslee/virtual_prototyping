////////////////////////////////////////////////////////////////////////////////
/// @file  wave_sine.h
/// @brief Definition of SystemC-AMS module of Sine Waves Generator.
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



#ifndef _GENERATOR_WAVE_SINUS_H
#define _GENERATOR_WAVE_SINUS_H

#include <systemc-ams.h>

namespace sca_comlib
{
    // -------------------------------------------------------------------------
    //! @class wave_sine

    //! @brief SystemC-AMS module of Sine Waves Generator.

    //! The output of this module is a sine wave. Frequency, amplitude, offset
    //! and initial phase of the output can be set via corresponding parameters.
   
    //! You can also change the frequency and amplitude of the wave_sine wave
    //! dynamically (during simulation) via ports “freq_in” and “amp_in”. You
    //! have to set parameter “freq_c” and “amp_c” to “true” to enable the
    //! dynamic reconfiguration of frequency and amplitude. Otherwise ports
    //! “freq_in” and/or “amp_in” are not available. Meanwhile you must add the
    //! symbol “&” before the name of a signal, when you connect it to one of
    //! these 2 ports (see example).
    // -------------------------------------------------------------------------
    class wave_sine: public sca_tdf::sca_module{

    public:
        wave_sine(sc_core::sc_module_name nm,
                  double    _freq_def   = 1000.,
                  double    _amp_def    = 1.0,
                  double    _phi        = 0.0,
                  double    _offset     = 0.0,
                  bool      _amp_c      = false,
                  bool      _freq_c     = false,
                  int       _rate       = 1);
        
        // module interfaces 
        sca_tdf::sca_out<double>    out;                                        //!< output port
        sca_tdf::sca_in<double>*    freq_in;                                    //!< input of frequency
        sca_tdf::sca_in<double>*    amp_in;                                     //!< input of amplitude
        
        //! function to refer value of signal "f_in" to the opt. port "freq_in"
        void freq_con (sca_tdf::sca_signal<double>* f_in);
        
        //! function to refer value of signal "a_in" to the opt. port "ampl_in"
        void amp_con (sca_tdf::sca_signal<double>* a_in);
        


        
    private:
        bool    freq_recon, ampl_recon;
        int     rate;                                                           //!< The datarate of the output
        double  stepsize;                                                       //!< the steps between the output token (i.e. if one token hase the
        
        // value sin(x), then the next token has the value sin(x+stepsize)
        double  actval;                                                         //!< state variable to store the actual "x" value, if whe don't want
       
        // to use sca_get_time()
        double  sample_time;                                                    //!< variable to store sample time, which is the time between two tokens
        
        double  freq_reg;
        double  amp_reg;
        double  offset;
        double  phi;
        
        void set_attributes() ;
        void initialize() ;
        void processing();
        
          };
} // namespace

#endif

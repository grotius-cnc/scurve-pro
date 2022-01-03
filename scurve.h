#ifndef SCURVE_H
#define SCURVE_H

//! SCURVE MOTION
//!
//! An improved scurve algoritme using gain 1-100% to
//! reduce machine's acceleration, deceleration periods.
//!
//! Made by Skynet Cyberdyne 03-01-2022.
//! Licence Gpl2.
//!
//! The template funtions may be of type <float> or <double>.

#include <iostream>
#include <math.h>

//! Structure containing results.
template<typename T>
struct Result{
    //! Scurve.
    T sc_ct=0, sc_cs=0, sc_vr=0, sc_sr=0, sc_ar=0;
    //! Motion,
    T tr_ct=0, tr_cs=0;
};

class Scurve
{
public:
    Scurve();

public:
    //! gain=curve power.
    //! am=acceleration a.
    //! vo=velocity begin.
    //! ve=velocity end.
    //! at_time=request curve state at timestamp[t]
    template<typename T>
    Result<T> scurve_fwd(T gain, T am, T vo, T ve, T at_time);

    //! gain=curve power.
    //! am=acceleration a.
    //! vo=velocity begin.
    //! ve=velocity end.
    //! at_time=request curve state at timestamp[t]
    template<typename T>
    Result<T> scurve_bck(T gain, T am, T vo, T ve, T at_time);

    //! s=displacement.
    //! vo=velocity begin.
    //! ve=velocity end.
    //! vs=velocity max.
    //! a=acceleration.
    //! at_time=request at timestamp.
    //! gain=curve power.
    template<typename T>
    Result<T> motion(T s, T vo, T ve, T vs, T a, T at_time, T gain);

    void runtest();
};

#endif // SCURVE_H

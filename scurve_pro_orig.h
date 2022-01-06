#ifndef SCURVE_PRO_ORIG_H
#define SCURVE_PRO_ORIG_H

//!
//! An improved scurve algoritme using gain 1-100% to
//! reduce machine's acceleration, deceleration periods.
//!
//! Made by Skynet Cyberdyne 03-01-2022.
//! Licence Gpl2.
//!
//! 04-01-2022 Added motion_stop function.
//!

#include <iostream>
#include <math.h>
#include <stdio.h>

template<typename T>
class scurve_pro_orig
{
public:
    scurve_pro_orig();
    struct Result{
        //! Traditional lineair curve.
        //! ct=curve time.
        //! cs=curve displacement.
        //! vr=velocity result.
        //! sr=displacment result.
        //! ar=acceleration result.
        T ct=0, cs=0, vr=0, sr=0, ar=0;
        //! 100% Scurve without gain.
        //! sc_ct=scurve curve time.
        //! sc_cs=scurve curve displacement.
        //! sc_vr=scurve velocity result.
        //! sc_sr=scurve displacment result.
        //! sc_ar=scurve acceleration result.
        T sc_ct=0, sc_cs=0, sc_vr=0, sc_sr=0, sc_ar=0;
    };

    Result scurve_fwd(T gain, T am, T vo, T ve, T at_time);
    Result scurve_bck(T gain, T am, T vo, T ve, T at_time);
    Result motion(T s, T vo, T ve, T vs, T a, T at_time, T gain);
};
template class scurve_pro_orig<double>;

#endif // SCURVE_PRO_ORIG_H

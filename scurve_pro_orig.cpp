#include "scurve_pro_orig.h"

template<typename T>
scurve_pro_orig<T>::scurve_pro_orig()
{

}

//! Inputs:
//! gain=curve power. using gain=100
//! am=acceleration a.
//! vo=velocity begin.
//! ve=velocity end.
//! at_time=request curve state at timestamp[t]
//! Results:
//! ct=curve time.
//! vr=velocity result.
//! sr=displacement result.
//! ar=acceleration result.
template<typename T>
typename scurve_pro_orig<T>::Result scurve_pro_orig<T>::scurve_fwd(T gain, T am, T vo, T ve, T at_time){
    Result r;
    
    gain=100;
    
    //! formula's lineair acceleration:
    //! v*v=(vo*vo) + 2*a*s, s=vo*t + 0.5*a*(t*t), t=sqrt(s*2/a) ,v=vo+a*t
    //! formula's lineair steady:
    //! s=vo+ v*t, t=s/v
    //! formula's scurve:
    //! a(t)=jm*t
    //! v(t)=vo+jm*(t*t)/2
    //! s(t)=vo*t+jm*(t*t*t)/6

    //! Calculated acc at inflection point.
    T as=0;
    //! Jerk.
    T jm=0;
    //! Velocity.
    T v1=0,v2=0,v3=0;
    //! Displacement.
    T s1=0,s2=0,s3=0;
    //! Periods. t1=concave, t2=lineair transition, t3=convex.
    T t1=0,t2=0,t3=0;

    //! Gain 0-100% to make it more user friendly.
    //!
    //! 100% gain is full scurve without lineair transition period.
    //! 0.001% gain is a traditional lineair curve.
    gain=gain*((ve-vo)/100);

    as=2*am;
    t1=gain/as;
    jm=as/t1;
    t3=t1;

    //! Calculate period t2. Here we use no vo values.
    v1=0 +jm*(t1*t1)/2;                 //! Velocity end has priority.
    v3=v1;
    v2=(ve-vo)-(v1+v3);
    t2=v2/as;

    //! Totals, used by [t<..] requests below.
    if(t2<0){t2=0;}
    if(t2>0){                           //! Gain value = < ve-vo.
        v1=vo +jm*(t1*t1)/2;
        v2=v1+as*t2;
        v3=v2 + as*t3 - jm*(t3*t3)/2;

        s1=vo*t1 +jm*(t1*t1*t1)/6;
        s2=s1+ v1*t2+0.5*as*(t2*t2);
        s3=s2+ v2*t3 + as*(t3*t3)/2 - jm*(t3*t3*t3)/6;
    }
    if(t2==0){                          //! Gain value = ~(ve-vo).
        v1=vo +jm*(t1*t1)/2;
        v2=0;
        v3=v1 + as*t3 - jm*(t3*t3)/2;

        s1=vo*t1 +jm*(t1*t1*t1)/6;
        s2=0;
        s3=s1+ v1*t3 + as*(t3*t3)/2 - jm*(t3*t3*t3)/6;
    }

    r.sc_ct=t1+t2+t3;                        //! Total curve time.
    r.sc_cs=s3;

    T t=at_time;

    if(t<t1){                           //! Period concave t1
        v1=vo +jm*(t*t)/2;
        s1=vo*t +jm*(t*t*t)/6;

        r.sc_vr=v1;
        r.sc_sr=s1;
        r.sc_ar=jm*t;
        return r;
    }
    if(t>=t1 && t<=t1+t2){              //! Period lineair transition t2
        t-=t1;
        v2=v1+as*t;
        s2=s1+ v1*t+0.5*as*(t*t);

        r.sc_vr=v2;
        r.sc_sr=s2;
        r.sc_ar=as;
        return r;
    }
    if(t>t1+t2 && t<=t1+t2+t3){          //! Period convex t3
        t-=t1;
        t-=t2;

        if(t2==0){
            v2=v1;
            s2=s1;
        }

        v3=v2 + as*t - jm*(t*t)/2;
        s3=s2+ v2*t + as*(t*t)/2 - jm*(t*t*t)/6;

        r.sc_vr=v3;
        r.sc_sr=s3;
        r.sc_ar=as-jm*t;
        return r;
    }
    //! Normally don't get here.
    return r;
}

//! Inputs:
//! gain=curve power.
//! am=acceleration a.
//! vo=velocity begin.
//! ve=velocity end.
//! at_time=request curve state at timestamp[t]
//! Results:
//! ct=curve time.
//! vr=velocity result.
//! sr=displacement result.
//! ar=acceleration result.
template<typename T>
typename scurve_pro_orig<T>::Result scurve_pro_orig<T>::scurve_bck(T gain, T am, T vo, T ve, T at_time){
    Result r;

    gain=100;
    
    //! Invert vo,ve
    T vo_temp=vo;
    vo=ve;
    ve=vo_temp;

    //! formula's lineair acceleration:
    //! v*v=(vo*vo) + 2*a*s, s=vo*t + 0.5*a*(t*t), t=sqrt(s*2/a) ,v=vo+a*t
    //! formula's lineair steady:
    //! s=vo+ v*t, t=s/v
    //! formula's scurve:
    //! a(t)=jm*t
    //! v(t)=vo+jm*(t*t)/2
    //! s(t)=vo*t+jm*(t*t*t)/6

    //! Calculated acc at inflection point.
    T as=0;
    //! Jerk.
    T jm=0;
    //! Velocity.
    T v1=0,v2=0,v3=0;
    //! Displacement.
    T s1=0,s2=0,s3=0;
    //! Periods. t1=concave, t2=lineair transition, t3=convex.
    T t1=0,t2=0,t3=0;

    //! Gain 0-100% to make it more user friendly.
    //!
    //! 100% gain is full scurve without lineair transition period.
    //! 0.001% gain is a traditional lineair curve.
    gain=gain*((ve-vo)/100);

    as=2*am;
    t1=gain/as;
    jm=as/t1;
    t3=t1;

    //! Calculate period t2. Here we use no vo values.
    v1=0 +jm*(t1*t1)/2;                 //! Velocity end has priority.
    v3=v1;
    v2=(ve-vo)-(v1+v3);
    t2=v2/as;

    //! Totals, used by [t<..] requests below.
    if(t2<0){t2=0;}
    if(t2>0){                           //! Gain value = < ve-vo.
        v1=vo +jm*(t1*t1)/2;
        v2=v1+as*t2;
        v3=v2 + as*t3 - jm*(t3*t3)/2;

        s1=vo*t1 +jm*(t1*t1*t1)/6;
        s2=s1+ v1*t2+0.5*as*(t2*t2);
        s3=s2+ v2*t3 + as*(t3*t3)/2 - jm*(t3*t3*t3)/6;
    }
    if(t2==0){                          //! Gain value = ~(ve-vo).
        v1=vo +jm*(t1*t1)/2;
        v2=0;
        v3=v1 + as*t3 - jm*(t3*t3)/2;

        s1=vo*t1 +jm*(t1*t1*t1)/6;
        s2=0;
        s3=s1+ v1*t3 + as*(t3*t3)/2 - jm*(t3*t3*t3)/6;
    }

    r.sc_ct=t1+t2+t3;                        //! Total curve time.
    r.sc_cs=s3;

    //! Invert time.
    double t=r.sc_ct-at_time;

    if(t<t1){                           //! Period concave t1
        v1=vo +jm*(t*t)/2;
        s1=vo*t +jm*(t*t*t)/6;

        r.sc_vr=v1;
        r.sc_sr=r.sc_cs-s1;             //! Invert displacement.
        r.sc_ar=-std::abs(jm*t);        //! Invert acceleration.
        return r;
    }
    if(t>=t1 && t<=t1+t2){              //! Period lineair transition t2
        t-=t1;
        v2=v1+as*t;
        s2=s1+ v1*t+0.5*as*(t*t);

        r.sc_vr=v2;
        r.sc_sr=r.sc_cs-s2;             //! Invert displacement.
        r.sc_ar=-std::abs(as);          //! Invert acceleration.
        return r;
    }
    if(t>t1+t2 && t<=t1+t2+t3){          //! Period convex t3
        t-=t1;
        t-=t2;

        if(t2==0){
            v2=v1;
            s2=s1;
        }

        v3=v2 + as*t - jm*(t*t)/2;
        s3=s2+ v2*t + as*(t*t)/2 - jm*(t*t*t)/6;

        r.sc_vr=v3;
        r.sc_sr=r.sc_cs-s3;             //! Invert displacement.
        r.sc_ar=-std::abs(as-jm*t);     //! Invert acceleration.
        return r;
    }
    //! Normally don't get here.
    return r;
}

template<typename T>
//! s=displacement.
//! vo=velocity begin.
//! ve=velocity end.
//! vs=velocity max.
//! a=acceleration.
//! at_time=request at timestamp.
//! ct=curve time.
//! cs=curve displacement.
//! vr=velocity result.
//! sr=displacement result.
//! ar=acceleration result.
typename scurve_pro_orig<T>::Result scurve_pro_orig<T>::motion(T s, T vo, T ve, T vs, T a, T at_time, T gain){

    //! Scurve structure.
    Result r;

    gain=100;
    
    //! Traditional lineair curve
    T t1=0, t2=0, t3=0, s1=0, s2=0, s3=0, v1=0, ct=0, cs=0, vr=0, sr=0, ar=0;
    T t=at_time;

    //! formula's lineair acceleration:
    //! v*v=(vo*vo) + 2*a*s, s=vo*t + 0.5*a*(t*t), t=sqrt(s*2/a) ,v=vo+a*t
    //! formula's lineair steady:
    //! s=vo+ v*t, t=s/v
    //! formula's scurve:
    //! a(t)=jm*t
    //! v(t)=vo+jm*(t*t)/2
    //! s(t)=vo*t+jm*(t*t*t)/6

    //! Global limits.
    if(ve<0){ve=0;}
    if(vo<0){vo=0;}

    //! Curve down algo.
    //if(ve<vo && vs>0 && s>0){
     if(vo>=vs && vs>=ve && vs>0 && s>0){

        //! Limits
        if(vs>vo){vs=vo;}
        if(ve>vs){ve=vs;}

        t1=(vo-ve)/a;
        s1=vo*t1 +0.5*a*(t1*t1);

        //! Dcc period to vs.
        t1=abs((vo-vs)/-a);
        s1=abs(vo*t1 +0.5*-a*(t1*t1));

        //! Dcc vs to ve period.
        t3=abs((vs-ve)/-a);
        s3=abs(vs*t3 +0.5*-a*(t3*t3));

        //! Vs steady period.
        s2=s-(s1+s3);
        t2=s2/vs;

        bool prompt_new_ve=0;
        if(t2<0){ //! Ve can not be reached. Set new ve based on s.

            ve=sqrt((vo*vo) + 2*-a*s);
            t1=(vo-ve)/a;

            s1=abs(vo*t1 +0.5*-a*(t1*t1));

            t2=0; //! Only t1 is used in this case.
            t3=0;
            s2=0;
            s3=0;

            prompt_new_ve=1;
        }

        v1=vo - a*t1;

        ct=t1+t2+t3;
        cs=s1+s2+s3;

        if(t<t1){ //! Period 1.
            vr=vo - a*t;
            sr=abs(vo*t + 0.5*-a*(t*t));
            ar=-a;

            if(prompt_new_ve){
                 r=scurve_bck(gain,a,vo,ve,t);
                 r.vr=vr;
                 r.sr=sr;
                 r.ar=ar;
                 r.ct=ct;
                 r.cs=cs;
                 return r;
            }
            r=scurve_bck(gain,a,vo,vs,t);
            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
        if(t>=t1 &&t<=t1+t2){ //! Period 2.
            t-=t1;
            vr=v1;
            sr=s1 + (v1*t);
            ar=0;

            r.sc_vr=vr;
            r.sc_sr=sr;
            r.sc_ar=ar;

            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
        if(t>t1+t2){ //! Period 3.
            t-=t1;
            t-=t2;
            vr=v1 + -a*t;
            sr=abs(s1+s2 + v1*t + 0.5*-a*(t*t));
            ar=-a;

            r=scurve_bck(gain,a,vs,ve,t);
            r.sc_sr+=s1;
            r.sc_sr+=s2;
            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
    }

    //! Curve up algo.
    //if(ve>=vo && vs>0 && s>0){
     if(vo<=vs && vs>0 && s>0){

        //! Limits.
        if(ve>vs){ve=vs;}

        t1=(ve-vo)/a;
        s1=vo*t1 +0.5*a*(t1*t1);

        bool prompt_new_ve=0;
        if(s1>s){ //! Ve can not be reached! Set new ve based on s.
            t1=sqrt(s/(0.5*a));
            ve=vo+a*t1;

            ct=t1;
            cs=s;

            vr=vo+a*t;
            sr=0.5*a*(t*t);
            ar=a;

            prompt_new_ve=1;
        }

        //! Sample to fit.
        while(1){

            //! Acc period.
            t1=(vs-vo)/a;
            if(t1<0){t1=0;}
            s1=vo*t1 +0.5*a*(t1*t1);

            //! Dcc period.
            t3=abs((vs-ve)/-a);
            if(t3<0){t3=0;}
            s3=abs(vs*t3 +0.5*-a*(t3*t3));

            //! Steady period.
            s2=s-(s1+s3);
            t2=s2/vs;

            if(s1+s3<=s){
                break;
            } else {
                vs-=0.1*vs;         //! Important value. It reduces mavel by input value until curves fit.
                //! The reduce value has great impact on function cycle time.
                //! 0.1 = 10% velocity recude to find the fit.
            }
        }

        //! v1 is given by sc.scurve_fwd function.
        v1=vo+ a*t1;

        ct=t1+t2+t3;
        cs=s1+s2+s3;

        if(t<t1){ //! Period 1.
            vr=vo + a*t;
            sr=vo*t + 0.5*a*(t*t);
            ar=a;

            if(prompt_new_ve){
                r=scurve_fwd(gain,a,vo,ve,t);
                r.vr=vr;
                r.sr=sr;
                r.ar=ar;
                r.ct=ct;
                r.cs=cs;
                return r;
            }

            r=scurve_fwd(gain,a,vo,vs,t);
            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
        if(t>=t1 &&t<=t1+t2){ //! Period 2.
            t-=t1;

            vr=v1;
            sr=s1 + (v1*t);
            ar=0;

            r.sc_vr=vr;
            r.sc_sr=sr;
            r.sc_ar=ar;

            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
        if(t>t1+t2){ //! Period 3.
            t-=t1;
            t-=t2;

            vr=v1 + -a*t;
            sr=abs(s1+s2 + v1*t + 0.5*-a*(t*t));
            ar=-a;

            r=scurve_bck(gain,a,vs,ve,t);
            r.sc_sr+=s1;
            r.sc_sr+=s2;
            r.vr=vr;
            r.sr=sr;
            r.ar=ar;
            r.ct=ct;
            r.cs=cs;
            return r;
        }
    }
    return r;
}

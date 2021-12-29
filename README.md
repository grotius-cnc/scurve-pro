# scurve-pro
An improved scurve algoritme with lineair transition stage.

This algoritme is using a "gain" value to optimize the scurve displacement and velocity results.

A lower gain value will reduce machining time.

The effiecienty of this implementation relies on the acceleration stage time[t] wich is 2*max acceleration.

The code is using a c++ template [template<typename T>] structure [struct] with a few functions inside the structure.

        scurve <double> s;  //! Double presision
        scurve <float> s;    //! Float presision

        //! Calculate the periods.
        s.init();
    
        //! Get scurve state at time[t].
        s.calculate(t);
    
        //! Reqeust a value.
        double val=s.a      //! Acceleration.
                   s.vr     //! Velocity result.   
                   s.sr     //! Displacment result.
                   s.vl     //! Velocity traditional lineair.
                   s.sl     //! Displacement traditional lineair.
    
        //! Prints a output list.
        s.print_results();

![output](https://user-images.githubusercontent.com/44880102/147709503-2c9d1d2b-ead6-424c-8433-0a13b586b5c7.jpg)

        Time taken by function nanoseconds : ~1048 milliseconds: ~0.001048
        as: 2.000000 am: 1.000000 jm: 4.000000 
        t1: 0.500000 t2: 1.500000 t3: 0.500000 
        ct: 2.500000 
        v1: 0.500000 v2: 3.500000 v3: 4.000000 
        v3: 4.000000 
        s1: 0.083333 s2: 3.083333 s3: 5.000000 
        s3: 5.000000 
        sl: 3.125000 vl: 2.500000 
        Efficienty factor [scurve with lineair transition] versus [normal scurve]
        Displacement factor improvment [s3/sl]: 1.600000
        Velocity factor improvment [v3/vl]    : 1.600000

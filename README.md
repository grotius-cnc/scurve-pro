### Scurve-pro
An improved scurve algoritme with lineair transition stage and curve power indicator.

[![scurve-pro - bring your machine to the g-force limits](https://img.shields.io/static/v1?label=scurve-pro&message=bring+your+machine+to+the+g-force+limits&color=blue)](https://) [![powered by - linux](https://img.shields.io/static/v1?label=powered+by&message=linux&color=red)](https://) [![code - c++ template](https://img.shields.io/static/v1?label=code&message=c%2B%2B+template&color=green)](https://) [![provided by - skynet cyberdyne](https://img.shields.io/static/v1?label=provided+by&message=skynet+cyberdyne&color=blue)](https://)
     
This algoritme is using a "gain" value to optimize the scurve displacement and velocity results.

A lower gain value will reduce machining time.

The effiecienty of this implementation relies on the acceleration stage time[t] wich is 2*max acceleration.

### Capabilities

1. This algo is capable of calculating trajectory's. 
2. It can output several different solutions depending on the trajectory input values.
3. When a velocity end can not be reached by the displacement input value, a new velocity end value is calculated.
4. If a velocity max value can not be reached during a run because of a short pathlenght. The curves are sampled to fit the trajectory.

### Usage
               //! Header only
               #include "scurve.h"
               
               //! Result struct.
               scurve_pro::Sc_Result r;

               //! Displacement.
               double s=100;
               //! Velocity begin.
               double vo=0;
               //! Velocity end.
               double ve=0;
               //! Velocity max.
               double vs=10;
               //! Acceleration.
               double a=2;
               //! Gain 1-100%.
               double gain=80;
               //! Request at timestamp.
               double at_time=0.001;

               r=scurve_pro().motion(s, vo, ve, vs, a, at_time, gain);
               double distancetogo=res.tr_cs-res.sc_sr;
        
### Things to know

When user changes max velocity during a traject run. You have to realize that a new calculation is needed to avoid any machine shock's

     1. The new calculation has a velocity begin of your current velocity.
     2. The end velocity can stay the same value.
     3. The pathlenght has to be changed into [currrent position-end position], like a new distance to go [dtg]. 

### Reverse engineering strategy

In the ~/gui dir, the template_x files will show how the algoritme is evolved step by step.
The difficulty of coding this algo is solved by making the following structured step by step strategy :

     1. Maka a traditional lineair algoritme including all curve output scenario's.
     2. Apply the conventional scurve algo to 1. This is a scurve algo without lineair transition period.
     3. Edit 2 to a scurve algorimte including lineair transition stage and curve power [gain].
        
### Picture section 

template_5:

![scurve](https://user-images.githubusercontent.com/44880102/147933136-169aa8c8-93e9-4b6c-9b8c-ea3feeb12634.jpg)

### Video section

Video of ~/scurve_gui/cpp_templates/template_4:

https://user-images.githubusercontent.com/44880102/147923294-b816f551-958d-4547-b4b3-20e7d2e0536f.mp4


Hal-core performing a runtest with scurve-pro.

          gain: 100%   traject time sec: 4        //! This is the full scurve algo without lineair stage.
          gain: 50 %   traject time sec: 3.5      //! 12.5 % faster
          gain: 1  %   traject time sec: 3        //! 25   % faster.     

https://user-images.githubusercontent.com/44880102/148067684-3e63a697-efc1-45e7-94e2-d2f4879d0f6e.mp4


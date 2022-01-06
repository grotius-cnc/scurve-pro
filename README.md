# scurve-pro
An improved scurve algoritme with lineair transition stage.

[![scurve-pro - bring your machine to the g-force limits](https://img.shields.io/static/v1?label=scurve-pro&message=bring+your+machine+to+the+g-force+limits&color=blue)](https://) [![powered by - linux](https://img.shields.io/static/v1?label=powered+by&message=linux&color=red)](https://) [![code - c++ template](https://img.shields.io/static/v1?label=code&message=c%2B%2B+template&color=green)](https://) [![provided by - skynet cyberdyne](https://img.shields.io/static/v1?label=provided+by&message=skynet+cyberdyne&color=blue)](https://)
     
There are several types of curve's to use:

1. Template class traditional lineair curve + scurve.
          
          scurve_pro_orig.cpp
          scurve_pro_orig.h
          
2. Template class optimized scurve with gain input [curve power]

          scurve_pro_gain.cpp
          scurve_pro_gain.h
           
3. Header only optimized scurve with gain input [curve power].

          scurve.h  

Video of template_4 testing acc & dcc interupts during runtime:

https://user-images.githubusercontent.com/44880102/148428147-78f2b0ea-c10e-4864-9f79-4a5ba2f59735.mp4

Implemenation example :

          scurve_pro_orig<double>::Result res;

          res=scurve_pro_orig<double>().motion(s, vo, ve, vs, a, at_time, gain);

          std::cout<<"curvel:"<<res.sc_vr<<std::endl;

          at_time+=0.001;

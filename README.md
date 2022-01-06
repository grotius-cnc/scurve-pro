# scurve-pro
An improved scurve algoritme with lineair transition stage.

[![scurve-pro - bring your machine to the g-force limits](https://img.shields.io/static/v1?label=scurve-pro&message=bring+your+machine+to+the+g-force+limits&color=blue)](https://) [![powered by - linux](https://img.shields.io/static/v1?label=powered+by&message=linux&color=red)](https://) [![code - c++ template](https://img.shields.io/static/v1?label=code&message=c%2B%2B+template&color=green)](https://) [![provided by - skynet cyberdyne](https://img.shields.io/static/v1?label=provided+by&message=skynet+cyberdyne&color=blue)](https://)
     
This algoritme is using a "gain" value to optimize the scurve displacement and velocity results.

A lower gain value will reduce machining time.

The effiecienty of this implementation relies on the acceleration stage time[t] wich is 2*max acceleration.

Video of template_4 testing acc & dcc interupts:

https://user-images.githubusercontent.com/44880102/148428147-78f2b0ea-c10e-4864-9f79-4a5ba2f59735.mp4

Implemenation example :

          scurve_pro_orig<double>::Result res;

          res=scurve_pro_orig<double>().motion(s, vo, ve, vs, a, at_time, gain);

          std::cout<<"curvel:"<<res.sc_vr<<std::endl;

          at_time+=0.001;

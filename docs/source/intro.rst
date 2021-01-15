Introduction
============

STracking is a stand alone C++ implementation of particle tracking algorithms. These algorithms are usefull in
the field of bio image analysis to follow sub cellular trafficking.

A particle tracking algorithm is splitted into 2 steps. First particles detections on each frames and second linking 
detections between frames. 
The STracking library focuses on the linking. The detection is thus assumed to be done by another tool. The linking needs
as inputs: 1- The image series to analys, 2- a list of txt file containing the coordinates and features of the particles 
and 3- a parameter file. More details can be foud in the *usage* page.

Context
-------
STracking is developped at Inria by **Sylvain Prigent**

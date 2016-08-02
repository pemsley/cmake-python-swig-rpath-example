
%module simple_module

%include "std_vector.i"
%include "std_pair.i"
%template(vector_pair) std::vector <std::pair <double,double> >;
%template(pair_double) std::pair <double,double>;

%{
#include "Python.h"
#include "stats.hh"
%}

%include "stats.hh"


#include <math.h>
#include <iostream>

#include "stats.hh"

void
stats::add(const std::pair<double, double> &datum) {

   data.push_back(datum);
}

void
stats::add(double x, double y) {
   std::pair<double, double> p(x,y);
   data.push_back(p);
}

double
stats::mean_x() const {

   double sum = 0;
   unsigned int n = data.size();
   for (unsigned int i=0; i<n; i++)
      sum += data[i].first;
   return sum/double(n);
}

double
stats::mean_y() const {

   double sum = 0;
   unsigned int n = data.size();
   for (unsigned int i=0; i<data.size(); i++)
      sum += data[i].second;
   return sum/double(n);
}

double
stats::variance_y() const {

   unsigned int n = data.size();
   if (n> 0) {
      double sum_sq = 0;
      for (unsigned int i=0; i<data.size(); i++)
	 sum_sq += data[i].second * data[i].second;

      double my = mean_y();
      double t = sum_sq/double(n) - my * my;
      if (t<0) t = 0;
      return t;
   } else {
      return 0;
   }
}

double
stats::standard_deviation_y() const {
   return sqrt(variance_y());
}

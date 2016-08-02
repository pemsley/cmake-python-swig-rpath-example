
#include <vector>
#include <utility>

class stats {

   std::vector<std::pair<double, double> > data;

public:

   void add(const std::pair<double, double> &datum);
   void add(double x, double y);

   double mean_x() const;
   double mean_y() const;
   double variance_y() const;
   double standard_deviation_y() const;

};

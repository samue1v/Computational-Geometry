#include "wykobi/wykobi.hpp"
#include "wykobi/wykobi_utilities.hpp"
#include "wykobi/wykobi_algorithm.hpp"
#include "util.hpp"



int main()
{

  std::vector<wykobi::point2d<double>> point_list;

  point_list.reserve(100);
  
  
  parseOBJ("crownDef.obj",point_list);

  wykobi::polygon<double,2> convex_hull;


  wykobi::algorithm::convex_hull_graham_scan<wykobi::point2d<double>>
  (
    point_list.begin(),
    point_list.end(),
    std::back_inserter(convex_hull)
  );

  writeOBJ("crownRes.obj",convex_hull);

  return 0;
}
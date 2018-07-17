#include <Rcpp.h>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace Rcpp;


const static double EarthRadius = 6371230;

inline double DegreeToRadian(double angle)
{
  return M_PI * angle / 180.0;
}

//  Function to estimate the Harvesine distance between 
// [[Rcpp::export]]
NumericVector haversineDistance(NumericVector fromLat, NumericVector fromLon,
                                NumericVector toLat, NumericVector toLon) {
  
  double fromLatRad = 0;
  double toLatRad = 0; 
  double fromLonRad = 0;
  double toLonRad = 0;
  
  double diffLat, diffLon, distComp;
  
  // Initialising distances array
  int vectorSize = fromLat.size();
  double distances[vectorSize];
  
  NumericVector results;
  
  // Checking if the vectors are all the same size
  
  
  // Calculating the harvesine distance for each pair of locations
  for(int i = 0; i < vectorSize; ++i)
  {
    fromLatRad = DegreeToRadian(fromLat[i]);
    toLatRad = DegreeToRadian(toLat[i]);
    fromLonRad = DegreeToRadian(fromLon[i]);
    toLonRad = DegreeToRadian(toLon[i]);
    
    diffLat = toLatRad - fromLatRad;
    diffLon = toLonRad - fromLonRad;
    
    distComp = asin(sqrt(sin(diffLat / 2) * sin(diffLat / 2) + 
                              cos(fromLatRad) * cos(toLatRad) * sin(diffLon / 2) * sin(diffLon / 2)));
    
    distances[i] = 2 * EarthRadius * distComp;
  }
  
  // Creating the R vector of distances
  results = NumericVector(distances, distances + sizeof(distances)/sizeof(*distances));
  
  return results;
}


//
// Tetsing in R
//

/*** R
haversineDistance(fromLat = c(-27.499322), fromLon = c(153.014925), 
                  toLat = c(-27.499190), toLon = c(153.015378))
*/

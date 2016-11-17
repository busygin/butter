//
// Created by busygin on 11/16/16.
//

#include <iostream>
#include <vector>
#include "butter.h"


int main() {
  std::vector<double> b;
  std::vector<double> a;
  highpass_butter(4, 0.1, b, a);

  for(std::vector<double>::const_iterator pb=b.begin(); pb!=b.end(); ++pb)
    std::cout << ' ' << *pb;
  std::cout << '\n';

  for(std::vector<double>::const_iterator pa=a.begin(); pa!=a.end(); ++pa)
    std::cout << ' ' << *pa;
  std::cout << '\n';

  return 0;
}
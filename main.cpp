//
// Created by busygin on 11/16/16.
//

#include <iostream>
#include <vector>
#include "butter.h"


int main() {
  size_t N;
  double Wn;

  while (true) {
    std::cout << "Input Butterworth highpass filter order and cutoff frequency (as fraction of Nyquist): ";
    std::cin >> N >> Wn;
    if (N==0) break;

    std::vector<double> b;
    std::vector<double> a;
    highpass_butter(N, Wn, b, a);

    std::cout << " b = [";
    for (std::vector<double>::const_iterator pb = b.begin(); pb != b.end(); ++pb)
      std::cout << ' ' << *pb;
    std::cout << " ]\n";

    std::cout << " a[1:] = [";
    for (std::vector<double>::const_iterator pa = a.begin(); pa != a.end(); ++pa)
      std::cout << ' ' << *pa;
    std::cout << " ]\n";
  }

  return 0;
}

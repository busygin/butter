#include <cmath>
#include <complex>
#include <algorithm>

#include "butter.h"


template<typename T>
void convolve(const std::vector<T>& a, const std::vector<T>& b, std::vector<T>& c) {
  size_t na = a.size();
  size_t nb = b.size();
  c.resize(na+nb-1);
  std::fill(c.begin(), c.end(), static_cast<T>(0.0));
  for (size_t i=0; i<na; ++i)
    for (size_t j=0; j<nb; ++j)
      c[i+j] += a[i]*b[j];
}

template<typename T>
void poly(const std::vector<T>& roots, std::vector<T>& coeffs) {
  std::vector<T> a(2);
  a[1] = 1.0;
  coeffs.resize(2);
  coeffs[0] = -roots[0];
  coeffs[1] = 1.0;
  for (typename std::vector<T>::const_iterator pr=roots.begin()+1; pr!=roots.end(); ++pr) {
    std::vector<T> b(coeffs);
    a[0] = -(*pr);
    convolve(b, a, coeffs);
  }
}

void highpass_butter(size_t N, double Wn, std::vector<double>& b, std::vector<double>& a) {
  std::vector< std::complex<double> > poles(N);
  std::vector< std::complex<double> > zeros;

  int m = 1-static_cast<int>(N);
  for (size_t i=0; i<N; ++i,m+=2) {
    double phi = M_PI*m/(2*N);
    poles[i] = std::complex<double>(-cos(phi),-sin(phi));
  }

  const double fs = 2.0;
  double wo = 2.0 * fs * tan(M_PI*Wn/fs);

  // transform to highpass
  for (std::vector< std::complex<double> >::iterator pp=poles.begin(); pp!=poles.end(); ++pp)
    *pp = wo * std::conj(*pp);
  zeros.resize(N, 0.0);

  double fs2 = 2.0*fs;

  std::complex<double> prod_p=1.0, prod_z=1.0;
  for (size_t i=0; i<N; ++i) {
    std::complex<double> tmp1 = -poles[i]+fs2;
    std::complex<double> tmp2 = -zeros[i]+fs2;
    poles[i] = (poles[i]+fs2) / tmp1;
    zeros[i] = (zeros[i]+fs2) / tmp2;
    prod_p *= tmp1;
    prod_z *= tmp2;
  }

  double k = (prod_z / prod_p).real();

  std::vector< std::complex<double> > c_b;
  poly(zeros,c_b);
  size_t nb = c_b.size();
  b.resize(nb);
  for (size_t i=0; i<nb; ++i) b[nb-i-1] = k * c_b[i].real();

  std::vector< std::complex<double> > c_a;
  poly(poles,c_a);
  size_t na = c_a.size()-1;
  a.resize(na);
  for (size_t i=0; i<na; ++i) a[na-i-1] = c_a[i].real();
}

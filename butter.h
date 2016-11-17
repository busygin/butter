//
// Created by busygin on 11/16/16.
//

#ifndef BUTT_BUTTER_H
#define BUTT_BUTTER_H

#include <cstddef>
#include <vector>

void highpass_butter(size_t N, double Wn, std::vector<double>& b, std::vector<double>& a);

#endif //BUTT_BUTTER_H

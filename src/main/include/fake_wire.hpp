#pragma once

#include <chrono>
#include <algorithm>
#include <cstdio>
#include <thread>
#include <cstring>
#include <iostream>

inline decltype(auto) millis() noexcept{
    using namespace std::chrono;
    return high_resolution_clock::now();
}

inline decltype(auto) micros() noexcept{
    using namespace std::chrono;
    return high_resolution_clock::now();
}
template<typename A, typename B>
inline decltype(auto) min(A a, B b){
    return std::min(a, b);
}

inline long map(int x, int in_min, int in_max, int out_min, int out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline decltype(auto) pgm_read_byte(const uint8_t* data){
    return *data;
}

inline char *dtostrf(double val, signed char width, unsigned char prec, char *sout)
{
  //Commented code is the original version
  /*char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;*/

  // Handle negative numbers
  uint8_t negative = 0;
  if (val < 0.0) {
    negative = 1;
    val = -val;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (int i = 0; i < prec; ++i) {
    rounding /= 10.0;
  }

  val += rounding;

  // Extract the integer part of the number
  unsigned long int_part = (unsigned long)val;
  double remainder = val - (double)int_part;

  if (prec > 0) {
    // Extract digits from the remainder
    unsigned long dec_part = 0;
    double decade = 1.0;
    for (int i = 0; i < prec; i++) {
      decade *= 10.0;
    }
    remainder *= decade;
    dec_part = (int)remainder;
    using namespace std;
    if (negative) {
      sprintf(sout, "-%ld.%0*ld", int_part, prec, dec_part);
    } else {
      sprintf(sout, "%ld.%0*ld", int_part, prec, dec_part);
    }
  } else {
    if (negative) {
      sprintf(sout, "-%ld", int_part);
    } else {
      sprintf(sout, "%ld", int_part);
    }
  }
  // Handle minimum field width of the output string
  // width is signed value, negative for left adjustment.
  // Range -128,127
  char fmt[129] = "";
  unsigned int w = width;
  if (width < 0) {
    negative = 1;
    w = -width;
  } else {
    negative = 0;
  }

  if (strlen(sout) < w) {
    memset(fmt, ' ', 128);
    fmt[w - strlen(sout)] = '\0';
    if (negative == 0) {
      char *tmp = reinterpret_cast<char*>(malloc(strlen(sout) + 1));
      strcpy(tmp, sout);
      strcpy(sout, fmt);
      strcat(sout, tmp);
      free(tmp);
    } else {
      // left adjustment
      strcat(sout, fmt);
    }
  }

  return sout;
}

inline void delay(unsigned int time){
    using namespace std::chrono;
    using namespace std::this_thread;
    sleep_for(milliseconds(time));
}

struct serial_t{
  template<typename T>
    void print(T stuff){
        std::cout << stuff;
    }
  template<typename T>
    void write(T stuff){
        std::cout << stuff;
    }
};
inline serial_t Serial;
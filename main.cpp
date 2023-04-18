#include <stdlib.h>
#include <stdio.h>
#include <temperature.h>
#include <msp430.h>
#if CONFIG_LIBTINYALLOC
#include <tinyalloc.hpp>
#elif CONFIG_LIBALLOCNV
#include <allocnv.hpp>
#endif


class AvgStore {
    public:
        int samples = 0;
        int sum = 0;
        AvgStore() {
            printf("New AvgStore created.\n");
          }
        void addSample(int sample) {
          sum += sample;
          samples++;
          printf("Registered new sample: %d\n", sample);
        }
        void printStats() {
          printf("Samples: %d, Avg: %d\n", samples, sum / samples);
        }

};

void sleep() {
  for (long i = 0; i < 1000000; i++) {
    __no_operation();
  }
}

int main() {
  initTempsensor();
  #if CONFIG_LIBTINYALLOC
  AvgStore *myAvgStr = new AvgStore();  // Create an object of AvgStore
  #elif CONFIG_LIBALLOCNV
  AvgStore *myAvgStr = cine<AvgStore>(16);  // Create a persistent object of AvgStore
  #endif
  while (1) {
    myAvgStr->addSample(getTemp());
    myAvgStr->printStats();
    sleep();
  }
  return 0;
}


#include <tinyalloc.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <temperature.h>
#include <msp430.h>

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
          printf("Registerd new sample: %d\n", sample);
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
  AvgStore *myAvgStr = cine<AvgStore>(16);  // Create an object of AvgStore
  while (1) {
    myAvgStr->addSample(getTemp());
    myAvgStr->printStats();
    sleep();
  }
  return 0;
}


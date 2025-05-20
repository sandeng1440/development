#include <stdio.h>

#define FRAC (4.0f / 3.0f)
#define PI 3.1415f

int main(void){
  // float volume = (4.0f/3.0f)* 4.1415f * 1000.0f;
  float radius = 10.0f;
  float volume = FRAC * PI * radius * radius * radius;
  printf("Volume of sphere is: %.2f\n", volume);
  return 0;
}

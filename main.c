#include <stdio.h>

int main()
{
  printf("Hello World\n");
  
  FILE *config;
  float mean_interarrival, mean_service;
  int delays_required;
  config = fopen("config.in","r");
  fscanf(config, "%f %f %d", &mean_interarrival, &mean_service, &delays_required);
  printf("Mean interarrival time: %f\nMean service time: %f\nNumber of required delays: %d\n",mean_interarrival, mean_service, delays_required);
  
  return 0;
}

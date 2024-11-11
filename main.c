#include <stdio.h>

int main()
{
  FILE *config, *report;
  float mean_interarrival, mean_service;
  int delays_required;
  
  /* Open files */
  config = fopen("config.in","r");
  report = fopen("report.txt","w");
  
  /* Check files exist */
  if(config == NULL || report == NULL)
  {
    printf("File read error!");
    exit(1);
  }  
  
  fscanf(config, "%f %f %d", &mean_interarrival, &mean_service, &delays_required);
  fclose(config);
  printf("Mean interarrival time: %f\nMean service time: %f\nNumber of required delays: %d\n",mean_interarrival, mean_service, delays_required);
  
  /* Write heading of report */
  fprintf(report, "Test write");
  fclose(report);
  
  /* Simulation Loop */
  
  
  return 0;
}

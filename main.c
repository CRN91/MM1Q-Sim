#include <stdio.h>
#include <math.h>

/* Initialises the sim */
void initialise_sim()
{

}

/* Update time average stats */
void update_time_avg_stats()
{

}

/* Calculates and writes report to file */
void report()
{

}

/* Determine next event and advance sim clock */
void timing()
{

}

/* Next departure event */
void depart()
{

}

/* Next arrival event */
void arrive()
{

}

/* Generate random uniformly distribute variate between 0 and 1 */
float random_uniform()
{

}

/* Generate random exponentially distributed variate between 0 and 1 */
float random_exponential(float uniform)
{

} 

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
    printf("Error! File not read.");
    exit(1);
  }  
  
  fscanf(config, "%f %f %d", &mean_interarrival, &mean_service, &delays_required);
  fclose(config);
  printf("Mean interarrival time: %f\nMean service time: %f\nNumber of required delays: %d\n",mean_interarrival, mean_service, delays_required);
  
  /* Write heading of report */
  fprintf(report, "Test write");
  
  /* Simulation Loop */
  int delays;
  while (delays < delays_required)
  {
    delays = 1000;
    /* Timing event to determine next event */
    
    /* Update Time Average Statistical Counters */
    
    /* Call correct event function */
    int event_type = 1;
    switch (event_type){
      case 1:
        break;
      case 2:
        break;
      default:
        printf("Error! Event type incorrect.");
        exit(1);
  }
  
  /* Call the report writing function */
  fclose(report);
  
  return 0;
}

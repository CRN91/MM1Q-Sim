#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define Q_LIMIT 100
#define BUSY 1
#define IDLE 0

float mean_interarrival, mean_service, uniform_rand, sim_clock, time_last_event;
int delays_required, num_in_q, server_status;
float event_list[2] = {0};
float *event_list_ptr = event_list;

/* Initialises the sim */
void initialise_sim()
{
  // Initialise Sim Variables
  sim_clock = 0.0;
  num_in_q = 0;
  time_last_event = 0;
  server_status = IDLE;
  
  // Initialise Statistical Counters
  customers_delayed = 0;
  total_time_delayed = 0.0;
  area_num_in_q = 0.0;
  area_server_status = 0.0;
  
  // Initialise event list
  *event_list_ptr = sim_clock + gen_rand_exponential(mean_interarrival);
  *(event_list_ptr + 1) = FLT_MAX;
  }
  
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
  // Determine next event
  int event_type;
  int next_event_type = 0;
  float min_time = FLT_MAX - 1;
  for (event_type = 0; event_type < 2; event_type++)
  {
    if (event_list[event_type] < min_time)
    {
      min_time = event_list[event_type];
      next_event_type = event_type;
    }
  }
  
  // Advance sim clock
  sim_clock = min_time;
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
float gen_rand_uniform()
{  
  // Generates variate between 0 and 1
  float random_variate = (float)rand() / RAND_MAX;
   
  return random_variate;
}

/* Generate random exponentially distributed variate between 0 and 1 with a mean of beta */
float gen_rand_exponential(float beta)
{
  return -1 * beta * log(gen_rand_uniform());
} 

int main()
{
  FILE *config, *report;
  // Open files
  config = fopen("config.in","r");
  report = fopen("report.txt","w");
  
  // Check files exist
  if(config == NULL || report == NULL)
  {
    printf("Error! File not read.");
    exit(1);
  }  
  
  // Load input parameters
  fscanf(config, "%f %f %d", &mean_interarrival, &mean_service, &delays_required);
  fclose(config);
  
  printf("Mean interarrival time: %f\nMean service time: %f\nNumber of required delays: %d\n",mean_interarrival, mean_service, delays_required);
  for (int i = 0; i < 2; i++){
    uniform_rand = gen_rand_uniform();
    printf("uniform random variate: %f\n", uniform_rand);
    printf("exponential random variate: %f\n", gen_rand_exponential(uniform_rand, mean_interarrival));
  }
  
  // Write heading of report
  fprintf(report, "Test write");
  
  // Initialise sim
  initialise_sim();
  
  // Simulation Loop
  int delays;
  while (delays < delays_required)
  {
    delays = 1000;
    // Timing event to determine next event
    
    // Update Time Average Statistical Counters
    
    // Call correct event function
    int event_type = 1;
    switch (event_type)
    {
      case 1:
        break;
      case 2:
        break;
      default:
        printf("Error! Event type incorrect.");
        exit(1);
    }
  }
  
  // Call the report writing function
  fclose(report);
  
  return 0;
}

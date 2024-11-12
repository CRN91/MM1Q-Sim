#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define Q_LIMIT 100
#define BUSY 1
#define IDLE 0

float mean_interarrival, mean_service, uniform_rand, sim_clock, time_last_event, total_time_delayed, area_num_in_q, area_server_status, time_arrival[Q_LIMIT+1];
int delays_required, num_in_q, server_status, customers_delayed;
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
  
  // Set all values in queue to -1
  for (int i = 0; i < Q_LIMIT; i++)
  {
    time_arrival[i] = -1;
  }
}

/* Update time average stats */
void update_time_avg_stats()
{
  // Calculate time since last event and update time last event to current time
  float time_since_last_event = sim_clock - time_last_event; // Delta x in equations
  time_last_event = sim_clock;
  
  /* Update stats where area_num_in_q is the cumulative area under the graph where the y axis is the number of customers in the queue
  and the x axis is the time. We can later use this to calculate the average number of customers in the queue during the simulation.
  The area_server_status is the cumulative area under the graph with y axis being the server utilisation (0 or 1 for idle / busy) and the
  x axis is time. This will allow us to calculate the proportion of server utilisation during the simulation. */
  
  area_num_in_q += num_in_q * time_since_last_event;
  area_server_status += server_status * time_since_last_event;

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
  // If queue is empty
  if (time_arrival[0] == -1){
    // Make server idle
    server_status = IDLE;
    
    // Remove departure from consideration
    *(event_list_ptr + 1) = FLT_MAX;
  } else{
    // Reduce the queue by 1
    num_in_q--;
    
    // Compute delay of customer entering service
    total_delay += sim_clock - time_arrival[0];
    customers_delayed++;
    
    // Schedule departure event
    *(event_list_ptr + 1) = sim_clock + gen_rand_exponential(mean_service);
    
    // Move other customers in the queue up one place
    for (int i = 0; i < num_in_q; i++)
    {
      time_arrival[i] = time_arrival[i+1];
    }  
}

/* Next arrival event */
void arrive()
{
  new_arrival = sim_clock + gen_rand_exponential(mean_interarrival);
  
  if (server_status == IDLE){
    // Set delay for current customer as 0 and add 1 to number of delayed customers
    float current_delay = 0.0;
    customers_delayed++;
  
    // Make server busy
    server_status = BUSY
    
    // Schedule departure event for current customer
    *(event_list_ptr + 1) = sim_clock + gen_rand_exponential(mean_service);
  } else {
    // Number of customers in queue increases by 1
    num_in_q++;
    
    // Stop simulation if queue is full
    if (num_in_q > Q_LIMIT){
      printf("Error! Stack Overflow in queue");
      exit(1);
    }
    
    // Add new customer to the queue
    time_arrival[num_in_q] = sim_clock;
  }
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
    timing()
    
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define Q_LIMIT 100
#define BUSY 1
#define IDLE 0

float mean_interarrival, mean_service, uniform_rand, sim_clock, time_last_event, total_time_delayed, area_num_in_q, area_server_status, time_arrival[Q_LIMIT+1];
int delays_required, num_in_q, server_status, customers_delayed, event_type;
float event_list[2] = {0};
float *event_list_ptr = event_list;

void arrive(void);
void depart(void);
void update_time_avg_stats(void);
void write_report(FILE *);
int timing(void);
float gen_rand_uniform(void);
float gen_rand_exponential(float);

/* Initialises the sim */
void initialise_sim(void)
{
  // Seed random number generator with current time
  srand(time(NULL));

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
  *event_list_ptr = gen_rand_exponential(mean_interarrival);
  *(event_list_ptr + 1) = FLT_MAX;
  
  // Set all values in queue to -1
  for (int i = 0; i < Q_LIMIT; i++)
  {
    time_arrival[i] = -1;
  }
  
  //printf("arrival: %f\ndeparture: %f\n", event_list[0], event_list[1]);
}

/* Update time average stats */
void update_time_avg_stats(void)
{
  // Calculate time since last event and update time last event to current time
  float time_since_last_event = sim_clock - time_last_event; // Delta x in equations
  //printf("time since last event %f\n",time_since_last_event); 
  time_last_event = sim_clock;
  
  /* Update stats where area_num_in_q is the cumulative area under the graph where the y axis is the number of customers in the queue
  and the x axis is the time. We can later use this to calculate the average number of customers in the queue during the simulation.
  The area_server_status is the cumulative area under the graph with y axis being the server utilisation (0 or 1 for idle / busy) and the
  x axis is time. This will allow us to calculate the proportion of server utilisation during the simulation. */
  
  area_num_in_q += num_in_q * time_since_last_event;
  area_server_status += server_status * time_since_last_event;
}

/* Calculates performance metrics and writes report to file */
void write_report(FILE * report)
{
  // Average delay and size in the queue and server utilisation | sim_clock should be total time at the end of the sim
  float avg_q_delay = total_time_delayed / customers_delayed;
  float avg_q_size = area_num_in_q / sim_clock;
  float server_utilisation = area_server_status / sim_clock;
  
  fprintf(report, "\nAverage delay in the queue: %f\nAverage number of customers in the queue: %f\nAverage server utilisation: %f", avg_q_delay, avg_q_size, server_utilisation);
}

/* Determine next event and advance sim clock */
int timing()
{
  //printf("sim clock: %f\nnum in q: %d\narrival: %f\ndeparture: %f\n\n\n", sim_clock, num_in_q, event_list[0], event_list[1]);

  // Determine next event
  int next_event_type = 0;
  float min_time = FLT_MAX - 1;
  for (int i = 0; i < 2; i++)
  {
    if (event_list[i] < min_time)
    {
      min_time = event_list[i];
      next_event_type = i;
    }
  }
  
  // Advance sim clock
  sim_clock = min_time;
  
  // 0 for arrival, 1 for departure
  return next_event_type;
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
    total_time_delayed += sim_clock - time_arrival[0];
    customers_delayed++;
    
    // Schedule departure event
    *(event_list_ptr + 1) = sim_clock + gen_rand_exponential(mean_service);
    
    // Move other customers in the queue up one place
    for (int i = 0; i < num_in_q; i++)
    {
      time_arrival[i] = time_arrival[i+1];
    }
    time_arrival[num_in_q] = -1;
  }
}

/* Next arrival event */
void arrive()
{
  // Schedule next arrival
  *(event_list_ptr) = sim_clock + gen_rand_exponential(mean_interarrival);
  
  if (server_status == IDLE){
    // Add 1 to customers delayed but don't add any time delayed as they are served instantly
    customers_delayed++;
  
    // Make server busy
    server_status = BUSY;
    
    // Schedule departure event for current customer
    *(event_list_ptr + 1) = sim_clock + gen_rand_exponential(mean_service);
  } else {
    // Stop simulation if queue is full
    if (num_in_q > Q_LIMIT){
      printf("Error! Stack Overflow in queue");
      exit(1);
    }
    
    // Add new customer to the queue
    time_arrival[num_in_q] = sim_clock;
    
    // Number of customers in queue increases by 1
    num_in_q++;
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

int main(void)
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
  
  //printf("Mean interarrival time: %f\nMean service time: %f\nNumber of required delays: %d\n",mean_interarrival, mean_service, delays_required);
  
  // Write heading of report
  fprintf(report, "Report");
  
  // Initialise sim
  initialise_sim();
  
  // Simulation Loop
  while (customers_delayed < delays_required)
  {
    // Timing event to determine next event
    event_type = timing();
    
    // Update Time Average Statistical Counters
    update_time_avg_stats();
    
    //printf("cust_delay: %d\ntotal time delayed: %f\n", customers_delayed, total_time_delayed);
    
    // Call correct event function
    switch (event_type){
      case 0: // arrival
        arrive();
        break;
      case 1: // departure
        depart();
        break;
      default:
        printf("Error! Event type incorrect.");
        exit(1);
    
    }
  }
  
  // Call the report writing function
  write_report(report);
  fclose(report);
  
  return 0;
}
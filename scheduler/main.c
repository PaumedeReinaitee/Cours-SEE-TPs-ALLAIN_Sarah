#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 10

typedef struct {
    const char *name;
    uint32_t period_ms;
    uint32_t max_runs;
    uint64_t last_run_ms;
    uint32_t run_count;
    void (*func)(void);
} task_t;

static task_t tasks[MAX_TASKS];
static int task_count = 0;

uint64_t get_time_ms(void) {
    // TODO: return current time
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t darwin_time_t_ms = (uint64_t)ts.tv_sec * 1000;
    uint64_t long_ms = (uint64_t)ts.tv_nsec / 1000000;
    uint64_t test = darwin_time_t_ms + long_ms;
    printf("Valeur : %llu\n", test);
    return darwin_time_t_ms + long_ms;
}

void task_register(const char *name, uint32_t period_ms, uint32_t max_runs, void (*func)(void)) {
    // !!! Check max tasks
    if(task_count >= MAX_TASKS){
        return;
    }
    // register a task
    task_t t1 = {.name = name,.period_ms = period_ms,.max_runs = max_runs,.run_count = 0,.last_run_ms = get_time_ms(),.func = func};
    printf("Tâche : %s, période : %d ms, max : %d, run : %d, denrier run : %llu, func : %p\n", t1.name, t1.period_ms, t1.max_runs, t1.run_count, t1.last_run_ms, t1.func);   
    task_count = task_count+1;
    // TODO

}

void task_1_handler(void) {
    printf("-> Task 1 logic executed\n");
}

void task_2_handler(void) {
    printf("-> Task 2 logic executed\n");
}

int main(void) {
    task_register("SensorTask", 100, 12, task_1_handler); // Runs 12 times
    task_register("LoggerTask", 500, 2, task_2_handler); // Runs 2 time

    while (true) {
        //get_time_ms();
        // TODO: complete the loop
    }

    return 0;
}

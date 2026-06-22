#include <stdio.h>

typedef struct Task Task;

typedef struct TaskManager{
    struct Task *tail;
    int size;
    int next_id;
} TaskManager;

typedef enum {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
} Priority;

int addTask(TaskManager *manager, char *task_name, int priority, int day, int month, int year);
int deleteTask(TaskManager *manager, int del_task_id);
int completeTask(TaskManager *manager, int complete_task_id);
int printList(TaskManager *manager);
void freeList(TaskManager *manager);
void editTask(TaskManager *manager, int task_id);
void searchTaskByName(TaskManager *manager, char* task_name);
void searchTaskById(TaskManager *manager, int task_id);
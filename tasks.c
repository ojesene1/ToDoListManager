#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
} Priority; 

typedef struct Task{
    char *name;
    int complete;
    int priority;
    int task_id;
    struct Task *next;
} Task;

int addTask(Task **tail, char *task_name, int task_id, int priority){
    Task *newTask = malloc(sizeof(Task));
    if(newTask == NULL || task_name == NULL){
        printf("Add Task Failure.\n");
        return 0;
    }
    newTask->name = strdup(task_name);
    newTask->complete = 0;
    newTask->priority = priority;
    newTask->task_id = task_id;
    newTask->next = newTask ;

    if (*tail == NULL){
        *tail = newTask;
        return 1;
    }

    // Circular tail pointer makes insertion O(1) complexity.
    newTask->next = (*tail)->next;
    (*tail)->next = newTask;    //updates the tail pointer to point to the newest node (task id start - 1 2 3 4 - task id tail)
    *tail = newTask; //tail should be the last node in the list
    return 1;

}

int deleteTask(Task **tail, int del_task_id){
    if(*tail == NULL){
        printf("There are no list items to delete.\n");
        return 0;
    }
    Task *temp = (*tail)->next;
    Task *prev = *tail;
    do{
        if(temp->task_id == del_task_id){
            prev->next = temp->next;

            if(temp == *tail && temp->next == temp){ // Need extra case for when the tail deletion is the last node in the list
                free(temp->name);
                free(temp);
                *tail = NULL;   // Sets the tail ptr to null
                return 1;
            }
            if (temp == *tail) {
                *tail = prev;
            }
            
            free(temp->name); //needed because we allocated name earlier with strdup()
            free(temp);
            return 1;
        }
        prev = prev->next;
        temp = temp->next;
    }while(temp != (*tail)->next);
    return 0;
}

int completeTask(Task *tail, int complete_task_id){
    if(tail == NULL){
        printf("There are no list items to complete.\n");
        return 0;
    }
    Task *temp = tail->next;
    do{
        if(temp->task_id == complete_task_id){
            temp->complete = !temp->complete;
            return 1;
        }
        temp = temp->next;
    }while(temp != tail->next);
    return 0;
}

int printList(Task *tail){
    if(tail == NULL){
        printf("To-Do List is EMPTY!\nGO FIND SOMETHING TO DO!!\n");
        return 0;
    }

    Task *temp = tail->next;

    printf("\n== HIGH PRIORITY TASKS ==");
    printf("\n------------------------------");
    do{
        if(temp->priority == HIGH){ //PRINTING THE HIGH PRIO TASKS
            printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " ")); 
        }
        temp = temp->next;
    } while(temp != tail->next);

    printf("\n\n== MEDIUM PRIORITY TASKS ==");
    printf("\n------------------------------");
    do{
        if(temp->priority == MEDIUM){ //PRINTING THE MED PRIO TASKS
            printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " ")); 
        }
        temp = temp->next;
    } while(temp != tail->next);

    printf("\n\n== LOW PRIORITY TASKS ==");
    printf("\n------------------------------");
    do{
        if(temp->priority == LOW){ //PRINTING THE LOW PRIO TASKS
            printf("\n[%d] %s [%s]", temp->task_id, temp->name, (temp->complete ? "DONE" : " ")); 
        }
        temp = temp->next;
    } while(temp != tail->next);
    return 1;
}

void freeList(Task **tail){
    if(*tail == NULL){
        printf("List already Empty Gang...\n");
    }
    else{
        Task *cur;
        Task *prev = (*tail)->next;
        Task *head = (*tail)->next; //holds the head ptr so we make sure this address is cleared.

        do{
            cur = prev->next;
            free(prev->name);
            free(prev);
            prev = cur;
        } while(cur != head);

        *tail = NULL;
    }
}

void editTask(Task *tail, int task_id){
    Task *temp = tail->next;
    int found = 0;
    do{
        if(temp->task_id == task_id){
            found = !found;
            break;
        }
        temp = temp->next;
    } while(temp != tail->next);

    if(!found){
        printf("Task mentioned was not found. Sorry!");
    }
    else{
        while(found){
            int choice;
            printf("What would you like to change about %s?\n", temp->name);
            printf("1. Change task Name.\n");
            printf("2. Update task Priority.\n");
            printf("3. Update task Completion.\n");
            printf("4. Exit Task Editing\n");
            printf("Your Choice: ");
            char buff1[10];
            fgets(buff1, sizeof(buff1), stdin);
            choice = atoi(buff1);
            
            switch(choice){
                case 1:
                    printf("What would you like the new task name to be: ");
                    char name[100];
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    free(temp->name);
                    temp->name = strdup(name);
                    printf("Edit Successful!");
                    break;
                case 2:
                    printf("What should the new Priority be? (1 = LOW, 2 = MEDIUM, 3 = HIGH): ");
                    char buff2[10];
                    fgets(buff2, sizeof(buff2), stdin);
                    int priority = atoi(buff2);
                    if(priority != LOW && priority != MEDIUM && priority != HIGH){
                        printf("Wrong priority, try again.");
                        break;
                    }
                    temp->priority = priority;
                    printf("Priority updated!");
                    break;
                case 3:
                    completeTask(tail, temp->task_id);
                    printf("Toggled Task Completion!");
                    break;
                case 4:
                    printf("Exitting task editing...");
                    found = !found;
                    break;
                default: 
                    printf("Wrong choice, try again.");
                    break;
            }
            printf("\n");
        }
    }
    
}
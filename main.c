#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.c"

int main(){
    int choice;
    char name[100];
    int task_id = 1, comp_task_id, task_prio;
    Task *tail = NULL;

    printf("Welcome to To-Do List Manager!\n");
    while(1){
        printf("\n1. Add a Task to the List!");
        printf("\n2. Mark a Task as Complete!");
        printf("\n3. Remove a Task from the List.");
        printf("\n4. Edit a Task.");
        printf("\n5. Print the Task List.");
        printf("\n6. Empty the List.");
        printf("\n7. Quit Task Manager.");
        
        printf("\nChoose your action: ");
        char buff1[10];
        fgets(buff1, sizeof(buff1), stdin);
        choice = atoi(buff1);

        switch(choice){
            case 1:
                printf("Type the name of the Task: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';   //remove the newline from the input

                printf("What is the Priority of this Task (1 = LOW, 2 = MEDIUM, 3 = HIGH): ");
                char buff2[10];
                fgets(buff2, sizeof(buff2), stdin);
                task_prio = atoi(buff2);
                if(task_prio != LOW && task_prio != MEDIUM && task_prio != HIGH){
                    printf("Wrong Priority input. Try again.");
                }
                else if (addTask(&tail, name, task_id, task_prio)){
                    printf("\nSuccessfully added task %d: %s!", task_id++, name);
                }
                else{
                    printf("\nInvalid Task name, try again.");
                }
                break;
            case 2:
                printf("\nType the id of the completed task: ");
                char buff3[10];
                fgets(buff3, sizeof(buff3), stdin);
                comp_task_id = atoi(buff3);    //mixing scanf will leave the newline for the fgets next call - leading to unexpected behaviour
                if(completeTask(tail, comp_task_id)){
                    printf("\nSuccessfully completed task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 3:
                printf("\nType the id of the task you wish to Remove: ");
                char buff4[10];
                fgets(buff4, sizeof(buff4), stdin);
                comp_task_id = atoi(buff4);
                if(deleteTask(&tail, comp_task_id)){
                    printf("\nSuccessfully deleted task %d!", comp_task_id);
                }
                else{
                    printf("\nInvalid Task id, try again.");
                }
                break;
            case 4:
                printf("Which task would you like to edit: ");
                char buff5[10];
                fgets(buff5, sizeof(buff5), stdin);
                comp_task_id = atoi(buff5);
                editTask(tail, comp_task_id);
                break;
            case 5:
                printList(tail);
                break;
            case 6:
                freeList(&tail);
                printf("List is EMPTY!");
                task_id = 1;
                break;
            case 7: 
                printf("Thanks for using us!\n");
                exit(1);
                break;
            default:
                printf("Make a choice or Quit!");
                break;
        }
        printf("\n");
    }
}
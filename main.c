#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

int main(){
    char name[100];
    int isDue = 0;
    int comp_task_id, task_prio;
    TaskManager manager = {.tail = NULL, .size = 0, .next_id = 1};

    printf("Welcome to To-Do List Manager!\n");
    while(1){
        printf("\n1. Add a Task to the List!");
        printf("\n2. Mark a Task as Complete!");
        printf("\n3. Remove a Task from the List.");
        printf("\n4. Edit a Task.");
        printf("\n5. Print the Task List.");
        printf("\n6. Empty the List.");
        printf("\n7. Search the List.");
        printf("\n8. Quit Task Manager.");
        
        printf("\nChoose your action: ");
        char buff1[10];
        fgets(buff1, sizeof(buff1), stdin);
        int choice = atoi(buff1);

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
                    break;
                }

                printf("Do you want to enter a due date for this task? (0 = NO, 1 = YES): ");
                char buffD[10];
                fgets(buffD, sizeof(buffD), stdin);
                isDue = atoi(buffD);
                int day, month, year;
                if(isDue){
                    printf("Enter the day as a number: ");
                    char buffd[10];
                    fgets(buffd, sizeof(buffd), stdin);
                    day = atoi(buffd);
                    printf("Enter the month as a number: ");
                    char buffm[10];
                    fgets(buffm, sizeof(buffm), stdin);
                    month = atoi(buffm);
                    printf("Enter the year as a number: ");
                    char buffy[10];
                    fgets(buffy, sizeof(buffy), stdin);
                    year = atoi(buffy);
                }
                if (addTask(&manager, name, task_prio, day, month, year)){
                    printf("\nSuccessfully added task %d: %s!", manager.next_id-1, name);
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
                if(completeTask(&manager, comp_task_id)){
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
                if(deleteTask(&manager, comp_task_id)){
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
                editTask(&manager, comp_task_id);
                break;
            case 5:
                printList(&manager);
                break;
            case 6:
                freeList(&manager);
                printf("List is EMPTY!");
                break;
            case 7:
                while(1){
                    printf("1. Search by Name?");
                    printf("\n      or");
                    printf("\n2. Search by ID?\n");
                    printf("Choice: ");
                    char buffsearch[10];
                    fgets(buffsearch, sizeof(buffsearch), stdin);
                    int search = atoi(buffsearch);
                    if(search == 1){
                        printf("Enter the name of the task you wish to find: ");
                        char buffsearchname[100];
                        fgets(buffsearchname, sizeof(buffsearchname), stdin);
                        buffsearchname[strcspn(buffsearchname, "\n")] = '\0';
                        searchTaskByName(&manager, buffsearchname);
                        break;
                    }
                    else if(search == 2){
                        printf("Enter the ID of the task you wish to find: ");
                        char buffsearchid[10];
                        fgets(buffsearchid, sizeof(buffsearchid), stdin);
                        searchTaskById(&manager, atoi(buffsearchid));
                        break;
                    }
                    else{
                        printf("Incorrect option. Try again.\n");
                    }
                }
                break;

            case 8: 
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
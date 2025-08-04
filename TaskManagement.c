#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct personalTasks{
    char status[100];
    char tasks[100];
    char category[100];
    int day, month, year;
};

struct personalTasks t;

long int size = sizeof(t);

FILE * fp, *fp1;

void listDesc(){ // view list by date descending order
    struct personalTasks swap_var, t[100];
    system("cls");
    fp = fopen("Personal Task Management.txt", "r");
    fseek(fp, 0, SEEK_END); // moves file pointer to the end of the file
    int n = ftell(fp)/size; // total number of tasks
    int i, j;
    rewind(fp);
    for (i = 0; i < n; i++)
        fread(&t[i], size, 1, fp); //read file contents
    for (i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            if (t[j].year < t[i].year){ // if second year value is less than firt year value
                swap_var = t[j]; //value of k changes to value of second year value
                t[j] = t[i]; // value of second year value changes to first year value
                t[i] = swap_var; // value of first year value changes to value of k
            }
            else {
                if (t[j].year == t[i].year){ //if second year value is same as first year value
                    if(t[j].month < t[i].month){
                        swap_var = t[j];
                        t[j] = t[i];
                        t[i] = swap_var; 
                    }
                    else {
                        if (t[j].month == t[i].month){
                            if(t[j].day < t[i].day){
                                swap_var = t[j];
                                t[j] = t[i];
                                t[i] = swap_var; 
                            }
                        }
                    }
                }
            }
        }
    }
    printf("    Tasks\t\t  Category\t\t  Status\t  Due Date\n");
    printf("============================================================================\n");
    for (i = 0; i < n; i++){;
        printf("%s\t|\t%s\t|\t%s\t|  %d-%d-%d\n",t[i].tasks, t[i].category, t[i].status, t[i].day, t[i].month, t[i].year);    
    }
    fclose(fp);
    system("pause");
}

void listAsc(){ // view list by date ascending order
    struct personalTasks swap_var, t[100];
    system("cls");
    fp = fopen("Personal Task Management.txt", "r");
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp)/size;
    int i, j;
    rewind(fp);
    for (i = 0; i < n; i++)
        fread(&t[i], size, 1, fp);
    for (i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            if (t[j].year > t[i].year){ // if second year value is greater than first year value
                swap_var = t[j];
                t[j] = t[i];
                t[i] = swap_var; 
            }
            else {
                if (t[j].year == t[i].year){
                    if(t[j].month > t[i].month){
                        swap_var = t[j];
                        t[j] = t[i];
                        t[i] = swap_var; 
                    }
                    else {
                        if (t[j].month == t[i].month){
                            if(t[j].day > t[i].day){
                                swap_var = t[j];
                                t[j] = t[i];
                                t[i] = swap_var; 
                            }
                        }
                    }
                }
            }
        }
    }
    printf("    Tasks\t\t  Category\t\t  Status\t  Due Date\n");
    printf("============================================================================\n");
    for (i = 0; i < n; i++){;
        printf("%s\t|\t%s\t|\t%s\t|  %d-%d-%d\n",t[i].tasks, t[i].category, t[i].status, t[i].day, t[i].month, t[i].year);    
    }
    fclose(fp);
    system("pause");
}

void taskList(){
    system("cls");
    fp = fopen("Personal Task Management.txt", "r");
    printf("    Tasks\t\t  Category\t\t  Status\t  Due Date\n");
    printf("============================================================================\n");
    while (fread(&t, size, 1, fp)){
        printf("%s\t|\t%s\t|\t%s\t|  %d-%d-%d\n",t.tasks, t.category, t.status, t.day, t.month, t.year); // all tasks data
    }
    fclose(fp);
    system("pause");
}

void taskListMenu(){ // options to choose how to view the list
    int option;
    printf("1. View tasks in ascending order (by date)\n2. View tasks in descending order (by date)\n3. View tasks by recently added");
    printf("\nHow would you like to view your task: ");
    scanf("%d", &option);
    
    switch (option){
        case 1:
            listAsc();
            break;
        case 2:
            listDesc();
            break;
        case 3:
            taskList();
            break;
    }
    
}

void addTask(){ // add task to the list
    system("cls");
    char another = 'y';
    char buffer[100];
    int ch;

    while (another == 'y'){ //continues to loop while another variable is still 'y'
        fp = fopen("Personal Task Management.txt", "a");
        if(fp == NULL) {
            printf("Error opening file!\n");
            return;
        }

        while((ch = getchar()) != '\n' && ch != EOF);
        
        printf("Enter the task name: ");
        fgets(t.tasks, sizeof(t.tasks), stdin);
        t.tasks[strcspn(t.tasks, "\n")] = 0;

        printf("Enter the task category: ");
        fgets(t.category, sizeof(t.category), stdin);
        t.category[strcspn(t.category, "\n")] = 0;

        printf("Enter the task status: ");
        fgets(t.status, sizeof(t.status), stdin);
        t.status[strcspn(t.status, "\n")] = 0;
        
        printf("Enter the task due date (dd-mm-yy): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d-%d-%d", &t.day, &t.month, &t.year);

        fwrite(&t, size, 1, fp);
        fclose(fp);
        
        printf("Would you like to add another task? (y/n) : ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, " %c", &another);
    }
}

void updateTask(){
    system("cls");
    char chosenTask[100], another = 'y';
    int option, found =0;
    
    while (another == 'y'){
        printf("Which task would you like to update: ");
        fflush(stdin);
        gets(chosenTask);
        fp = fopen("Personal Task Management.txt", "r");
        fp1 = fopen("temp.txt", "w"); //write updated data into temporary file
        while (fread(&t, size, 1, fp)){
            if (strcmp(chosenTask, t.tasks) == 0){
                found = 1;
                printf("Task found!\n");
                printf("    Tasks\t\t  Category\t\t  Status\t  Due Date\n");
                printf("============================================================================\n");
                printf("%s\t|\t%s\t|\t%s\t|  %d-%d-%d\n",t.tasks, t.category, t.status, t.day, t.month, t.year); 
                printf("1. Update task name\n2. Update task category\n3. Update task status\n4. Update task due date");
                printf("\nWhat would you like to update specifically: ");
                scanf("%d", &option);                 
                switch(option){
                    case 1:
                        printf("Enter new task name: ");
                        fflush(stdin);
                        scanf("%[^\n]s", t.tasks);
                        break;
                    case 2:
                        printf("Enter new task category: ");
                        fflush(stdin);
                        scanf("%[^\n]s", t.category);
                        break;
                    case 3:
                        printf("Enter new task status: ");
                        fflush(stdin);
                        scanf("%[^\n]s", t.status);
                        break;
                    case 4:
                        printf("Enter new task due date (dd-mm-yy): ");
                        fflush(stdin);
                        scanf("%d-%d-%d", &t.day, &t.month, &t.year);  
                        break;
                    
                }
            }
            fwrite(&t, size, 1, fp1); 
        }
        fclose(fp);
        fclose(fp1);

        if(found){
            fp1 = fopen("temp.txt", "r");
            fp = fopen("Personal Task Management.txt", "w");
            while(fread(&t, size, 1, fp1)){
                fwrite(&t, size, 1, fp); // overwrite task file with
            }
            fclose(fp);
            fclose(fp1);

            printf("Task Updated!\n");
            printf("Would you like to update another task? (y/n): ");
            fflush(stdin);
            scanf("%c", &another);
        }
        else{
            printf("Task Not Found\n");
        }
    }
}

void deleteTask(){
    system("cls");
    char chosenTask[100], another = 'y';
    int found =0;
    
    while (another == 'y'){
        printf("Which task would you like to delete: ");
        fflush(stdin);
        gets(chosenTask);
        fp = fopen("Personal Task Management.txt", "r");
        fp1 = fopen("temp.txt", "w");
        while (fread(&t, size, 1, fp)){
            if (strcmp(chosenTask, t.tasks) == 0){
                found = 1;
            }
            else{
               fwrite(&t, size, 1, fp1);  
            }             
        }
        fclose(fp);
        fclose(fp1);

        if(found){
            fp1 = fopen("temp.txt", "r");
            fp = fopen("Personal Task Management.txt", "w");
            while(fread(&t, size, 1, fp1)){
                fwrite(&t, size, 1, fp);
            }
            fclose(fp);
            fclose(fp1);

            printf("Task Deleted!\n");
            printf("Would you like to delete another task? (y/n): ");
            fflush(stdin);
            scanf("%c", &another);
        }
        else
            printf("Task Not Found\n");
    }
}

int main(){
    int operation;
    while (1){
        system("cls");
        printf("Personal Task Management\n");
        printf("1) View Tasks\n2) Add A New Task\n3) Update A Task\n4) Delete A Task\n5) Exit Program");
        printf("\nSelect Operation Number: ");
        fflush(stdin);
        scanf("%d", &operation);
        switch (operation){
            case 1:
                taskListMenu();
                break;

            case 2:
                addTask();
                break;

            case 3:
                updateTask();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                printf("Have A Nice Day");
                exit(0);
                break;
        }
    }
    return 0;
}
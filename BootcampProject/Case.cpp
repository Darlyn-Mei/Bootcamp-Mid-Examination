#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mainMenu();

struct Node{
    char dish[255];
    struct Node *next;
} *head = NULL, *curr = NULL;

struct Node *createNode(char dish[]){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->dish, dish);
    newNode->next = NULL;
    return newNode;
}

void printOS(){
    #ifdef _WIN32
        printf("System: Windows OS\n");
    #elif __linux__
        printf("System: Linux OS\n");
    #elif _WIN64
        printf("Syetem: Windows OS\n");
    #elif __APPLE__
        printf("System: Mac OS\n");
    #endif
    return;
}

void printTime(){
    time_t t = time(NULL);
    printf("%s", ctime(&t));
    return;
}

void pushHead(char dish[]){
    curr = createNode(dish);
    
    if (head == NULL){
        head = curr;
    }else{
        curr->next = head;
        head = curr;
    }

    mainMenu();
}

void popHead(){
    if (head == NULL){
        return;
    }else{
        if (head->next == NULL){
            free(head);
            head = NULL;
        }else{
            curr = head;
            head = head->next;
            free(curr);
            curr = NULL;
        }
    }

    mainMenu();
}

// void printMap(){
//     curr = head;
//     if (head == NULL){
//         printf("Data is empty\n");
//         return;
//     }

//     int a = 1;

//     while (curr){
//         printf("%d. %s\n", a, curr->dish);
//         a++;
//         curr = curr->next;
//     }
// }


int check(char str[], int len){
    int count = 0;
    for(int i=0;i<len;i++){
        if((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' '){
            count++;
        }
    }
    if (count == len){
        return 1;
    }
    else{
        return 0;
    }
}

void addDish(){
	char name[300];
	int price, quantity, len;
	
    printf("Insert the name of the dish [Lowercase letters]: ");
    scanf("%[^\n]", name); getchar();
    len = strlen(name);
    while(check(name, len) == 0){
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", name); getchar();
    }

	printf("Insert the price of the dish [1000..50000]: ");
	scanf("%d", &price); getchar();
    while (price < 1000 || price > 50000){
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price); getchar();
    }

	printf("Insert the quantity of the dish [1..999]: ");
	scanf("%d", &quantity); getchar();
    while (quantity < 1 || quantity > 999){
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity); getchar();
    }
	
	puts("The dish has been added!");
	puts("Press enter to continue...");	
	
}

void mainMenu(){
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");
}

int main(){
    int choice;

    do{
        system("cls");
        printOS();
        printTime();
        // printMap();
        mainMenu();
        puts("");
    
        printf(">> ");
        scanf("%d", &choice); getchar();
        if (choice == 1){
            addDish();
        }
        // else if (choice == 2){
        //     popHead();
        // }
        
    } while (choice != 8);


    return 0;
}
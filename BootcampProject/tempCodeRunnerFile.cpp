#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int MAX_BUCKET = 30;
const int MAX_CHAR = 755;
const int MAX_ORDER = 755;
char hashtable[MAX_BUCKET][MAX_CHAR];
char hashName[MAX_BUCKET][MAX_CHAR];
int hashPrice[MAX_BUCKET];
int hashQuan[MAX_BUCKET];

int hashQuantity[MAX_BUCKET];
char hashMAKANAN[MAX_BUCKET][MAX_ORDER][MAX_CHAR];
int hashJUMLAHMAKANAN[MAX_BUCKET][MAX_ORDER];

struct Node{
    char dishName[255];
    int dishPrice;
    int dishQuan;
    struct Node *next;
};

struct Node *createNode(char name[], int price, int quantity){
    struct Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->dishName, name);
    newNode->dishPrice = price;
    newNode->dishQuan = quantity;
    newNode->next = NULL;
    
    return newNode;
}

void printOS(){
    #ifdef _WIN32
        puts("System: Windows OS");
    #elif __linux__
        puts("System: Linux OS");
    #elif _WIN64
        puts("Syetem: Windows OS");
    #elif __APPLE__
        puts("System: Mac OS");
    #endif
    return;
}

void printTime(){
    time_t t = time(NULL);
    printf("%s", ctime(&t));
    return;
}

void printMap(){
    int Numb = 1;

    puts("             Bude's Menu");
    puts("=========================================");
    puts("No.      Name         Quantity     Price");
    for(int i = 0; i < MAX_BUCKET; i++){
        if(hashtable[i][0] != '\0'){
    printf("%d.       %s           %03d       Rp.%d\n", Numb, hashtable[i], hashQuan[i], hashPrice[i]);
            Numb++;
        }
    }

    puts("=========================================");
}

unsigned long djb2(char str[]) {
  unsigned long key = 5381;

  for(int i = 0; str[i] != '\0'; i++) {
    int ascii = int(str[i]);
    key = (key << 5) + key + ascii;
}

  return key % MAX_BUCKET;
};

void linearProbing(int idx, const char *str)
{
  for (int i = (idx + 1) % MAX_BUCKET; i != idx; i = (i + 1) % MAX_BUCKET)
  {
    if (!hashtable[i][0])
    { 
        strcpy(hashtable[i], str);
        return;
    }
  }
}

int check(char str[], int len){
    int count = 0;
    for(int i=0;i<len;i++){
        if((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' '){
            count++;
        }
    }
    if(count == len){
        return 1;
    }else{
        return 0;
    }
}

void input(char name[], int price, int quantity){
    Node *newNode = createNode(name, price, quantity);
    int idx = djb2(name);

    if (!hashtable[idx][0]){
    strcpy(hashtable[idx], name);
    hashPrice[idx] = price;
    hashQuan[idx] = quantity;
    }else{
    linearProbing(idx, name);
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
    while(price < 1000 || price > 50000){
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price); getchar();
    }

	printf("Insert the quantity of the dish [1..999]: ");
	scanf("%d", &quantity); getchar();
    while (quantity < 1 || quantity > 999){
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity); getchar();
    }
	
    input(name, price,quantity);
	puts("The dish has been added!");
	puts("Press enter to continue...");	
}

void removeDish(char name[]){
    int idx = djb2(name);

    hashPrice[idx] = NULL;
    hashQuan[idx] = NULL;
    hashtable[idx][0] = NULL;

    puts("The dish has been removed!");
    puts("Press enter to continue...");
}

struct NodeName
{
    char name[755];
    Node *next;
};

struct NodeName *createNodeName(char name[]){
  NodeName *newNode = (NodeName*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  return newNode;
}

void nameLinearProbing(int idx, const char *str)
{
  // loop dari idx sampai N, kemudian dari 0 sampai idx-1 (basically loop biasa, tapi startnya bukan 0)
  for (int i = (idx + 1) % MAX_BUCKET; i != idx; i = (i + 1) % MAX_BUCKET)
  {
    if (!hashName[i][0])
    { // if specified index is empty
      strcpy(hashName[i], str);
      return;
    }
  }
}

void addCust(){
    char name[755];

    printf("Insert the customer's name [Without space]: ");
    scanf("%[^\n]", name); getchar();
    NodeName *newNode = createNodeName(name);
    int idx = djb2(name);
        
    if (!hashtable[idx][0]){
        strcpy(hashName[idx], name);

        puts("Customer has been added!");
        puts("Press any key to continue:");
    }else{
        nameLinearProbing(idx, name);

        puts("Customer has been added!");
        puts("Press any key to continue:");
    }
}

void checkCust(char name[]){
    int idx = djb2(name);
    
    if(hashName[idx][0] != '\0'){
        printf("%s is present.\n", name);
    }
    else{
        printf("%s is not present.\n", name);
    }

    puts("Press Any Key to Continue");  
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
        system("clear");
        printOS();
        printTime();
        mainMenu();
        printf(">> ");
        
        scanf("%d", &choice); getchar();
        if (choice == 1){
            addDish();
        }else if (choice == 2){
            char name[755];
            printMap();
            printf("Insert dish's name to be deleted: ");
            scanf("%[^\n]", name); getchar();
            removeDish(name);
        }else if (choice == 3){
            addCust();
        }else if (choice == 4){
            char name[755];
            
            printf("Insert the customer name: ");
            scanf("%s", name); getchar();
            checkCust(name);  
        }else if (choice == 5){
            
        }else if (choice == 6){
            
        }else if (choice == 7){
            
        }
        system("clear");   
    }while(choice != 8);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//This displays the max lines of string and max length of the string for the text file
#define MAX_LINES 100
#define MAX_LEN 100

struct Customer {
    char name[100];
    char cart[5][100];
    int total;
};



//Displays the Customer's Order
void displayOrder(struct Customer *customer, int cartSize){
    printf("%s's Order:\n",customer->name);

    printf("Name\tPrice\tDesc.\t\tCatalog Number\n");
    printf("----------------------------------------------\n");
    for(int i=0; i<cartSize; i++){
        printf("%s", customer->cart[i]);
    }

    printf("\nNumber of Items in Cart: %d\n",customer->total);
}



//Inserting the item into shopping cart
void insertItem(int strLength,char itemName[100], char items[MAX_LINES][MAX_LEN], struct Customer *customer, int cartSize){ 

    //Asks for user input
    printf("\nPlease insert an item to add to your cart (Max: 5 items): ");
    fgets(itemName, 100, stdin);
    itemName[0] = toupper(itemName[0]);
    itemName[strlen(itemName)-1] = '\0';
    int cartIndex = 0;

    //Loop through the items
    for(int i=0;i<strLength; i++){
        if(strstr(items[i],itemName)){
            system("CLS");
            if(itemName[0] == '\0'){
                printf("Invalid Input");
                break;
            }
            //Checks to if the cart index is not null and as long as the cart index is less than the customer's cart 
            while(customer->cart[cartIndex][0] != '\0' && cartIndex < cartSize){
                cartIndex++;
            }

            if(cartIndex < cartSize){
                strcpy(customer->cart[cartIndex], items[i]);

                customer->total++;
                break;
            }
            else{
                printf("Limit Has Been Reached\n");
                break;
            }
        }        
        else{
            system("CLS");
            printf("Item Not Found\n");
        }
    }
    printf("\n%s's Cart:\n", customer->name);

    for(int i=0; i<cartSize; i++){
        printf("%s",customer->cart[i]);
    }

}

    

//Input customer name
void inputCustomer(struct Customer *customer, char name[100]){
    printf("Please insert your name[max: 100]: ");
    fgets(name, 100, stdin);
    name[strcspn(name,"\n")] = 0;
    strcpy(customer->name, name);
    system("CLS");
}



//Shows all items
void showItems(int strLength,int itemSize,char items[MAX_LINES][MAX_LEN]){
    system("CLS");
    printf("***********************************************************************\n");
    printf("\tName\tPrice\tDesc.\t\tCatalog Number\n");
    for(int i=0;i<strLength;i++){
        printf("\t%s",items[i]);
    }
    printf("\n***********************************************************************\n");
}



//Searches for an item
void searchItem(int strLength,char search[100], char items[10][100]){
    system("CLS");
    printf("Search For an Item: ");
    fgets(search,100,stdin);

    search[0] = toupper(search[0]);    
    search[strlen(search)-1] = 0;
    
    for(int i=0;i<strLength;i++){
        if(strstr(items[i],search)){
            system("CLS");
            printf("Name\tPrice\tDesc.\t\tCatolog Number\n");
            printf("%s",items[i]);
            break;
        }
        else{
            system("CLS");
            printf("Item Not Found\n");
        }
    }
}



//Returns how many strings there are in an array
int numStrings(char array[][100]){
    int num;

    for(int i=0; array[i][0] != '\0'; i++){
        num++;
    }
    return num;
}



int main(){

    //Variables
    char items[MAX_LINES][MAX_LEN];
    int options;
    char name[100];
    char search[100];
    struct Customer customer;
    char itemName[100];
    int cartSize = sizeof(customer.cart) / sizeof(customer.cart[0]);

    //Reading catalog file
    FILE *file;
    file = fopen("catalog.txt", "r");
    if(file==NULL){
        printf("Cannot open file");
    }

    //Adding the file into an array called items
    int line = 0;
    while(!feof(file) && !ferror(file)){
        if(fgets(items[line], 100, file) != NULL){
            line++;
        }
    }
    fclose(file);

    //Catalog file size
    int strLength = numStrings(items);
    int itemSize = sizeof(items) / sizeof(items[0]);

    //Program starts here
    printf("Welcome to the shop!\n");
    do{
        printf("\n1. Input Customer Name\n");
        printf("2. Add a Product to a Customer's shopping cart\n");
        printf("3. Display the Customer's Order\n");
        printf("4. Search For an Item\n");
        printf("5. Show all Items\n");
        printf("6. Exit the Program\n");
        scanf("%d",&options);
        getchar();

        //Quits the Program
        if(options==6){
            break;
        }

        //Inputs the Customer's name by passing the memory address of the structure to a pointer in the function
        else if(options==1){
            system("CLS");
            if(customer.name[0] != '\0'){
                system("CLS");
                printf("A Name is Already in Use");
            }
            else{
                inputCustomer(&customer, name);
                printf("Hello %s",customer.name);
            }
        }

        //Checks to see if a customer's name exists, then it will insert the requested items in the cart
        else if(options==2){
            system("CLS");
            if(customer.name[0] == '\0'){
                system("CLS");
                printf("You Need to Have a Customer Name to Continue\n");
            }
            else{
                system("CLS");
                insertItem(strLength,itemName,items, &customer, cartSize);

            }
        }

        else if(options==3){
            system("CLS");

            if(customer.name[0] == '\0'){
                system("CLS");
                printf("You Need to Have a Customer Name to Continue\n");
            }
            else{
                system("CLS");
                displayOrder(&customer, cartSize);
            }
        }

        else if(options==4){
            system("CLS");
            searchItem(strLength,search, items);
        }
 
        else if(options==5){
            system("CLS");
            showItems(strLength,itemSize,items);
        }
        else{
            system("CLS");
            printf("Invalid Input");
        }

    }while(options!=6);

    printf("Thank You for Trying Out the Program");
    printf("\n");
    return 0;
}
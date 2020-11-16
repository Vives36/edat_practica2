#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "menu_template.h"
#include "products.h"
#include "orders.h"
#include "customers.h"


void ShowProductsMenu(){
    int nChoice = 0;
    do{
        nChoice = ShowProductsSubMenu();
        switch (nChoice){
            case 1: {
                if(stockProductsQuery() == EXIT_SUCCESS){
                    ShowProductsMenu();
                }
            }
                break;
            
            case 2: {
                if(findProductsQuery() == EXIT_SUCCESS){
                    ShowProductsMenu();
                }
            }
                break;
            
            case 3: {
                
            }
                break;
        }
    }while(nChoice !=3);

}


int ShowProductsSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {
        printf(" (1) Stock of a given ProductCode\n"
               " (2) List of products given a part of the ProductName\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");

        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");
        if ((nSelected < 1) || (nSelected > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }

    } while ((nSelected < 1) || (nSelected > 3));


    return nSelected;
}


void ShowOrdersMenu(){
    int nChoice = 0;
    do{
        nChoice = ShowOrdersSubMenu();
        switch (nChoice){
            case 1: {
                if(openOrdersQuery() == EXIT_SUCCESS){
                    ShowOrdersMenu();
                }
            }
                break;
            
            case 2: {
                if(rangeOrdersQuery() == EXIT_SUCCESS){
                    ShowOrdersMenu();
                }
            }
                break;

            case 3: {
                printf("Aqui hace detail");
            }
                break;
            
            case 4: {
                
            }
                break;
        }
    }while(nChoice !=4);
}


int ShowOrdersSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {
        printf(" (1) List of orders not shipped\n"
               " (2) Orders between two dates\n"
               " (3) List of products given an OrderNumber\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");

        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");
        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }

    } while ((nSelected < 1) || (nSelected > 4));


    return nSelected;
}



void ShowCustomersMenu(){
    int nChoice = 0;
    do{
        nChoice = ShowCustomersSubMenu();
        switch (nChoice){
            case 1: {
                if(findCustomersQuery() == EXIT_SUCCESS){
                    ShowCustomersMenu();
                }
            }
                break;
            
            case 2: {
                printf("Aqui hace List Products");
            }
                break;

            case 3: {
                printf("Aqui hace Balance");
            }
                break;
            
            case 4: {
                
            }
                break;
        }
    }while(nChoice !=4);
}




int ShowCustomersSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {
        printf(" (1) List of customers given a part of its name\n"
               " (2) List of products order by a customer\n"
               " (3) Balance of a customer given its CustomerNumber\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");

        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");
        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }

    } while ((nSelected < 1) || (nSelected > 4));


    return nSelected;
}

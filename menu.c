#include <stdlib.h>
#include <stdio.h>
#include "menu_template.h"



/**
 * @brief Llama a la funcion para imprimir menu principal
 *        y lo ejecuta
 *
 * Esta funcion implementa un bucle que imprime el menu 
 * principal, analiza la entrada del usuario y llama a 
 * la funcion que corresponde
 *
 * @return 0 if no error
 * @author Carlos Vives y Alberto Rodado
 */
int main() {
    int nChoice = 0;

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu();
            }
                break;

            case 2: {
                ShowOrdersMenu();
            }
                break;

            case 3: {
                ShowCustomersMenu();
            }
                break;

            case 4: {
                printf("Bye Bye!");
                break;
            } 
        }
    } while (nChoice != 4);
    return 0;
}


/**
 * @brief Imprime el menu principal y da acceso a una entrada
 *        de seleccion
 *
 * @return seleccion de menu
 * @author Carlos Vives y Alberto Rodado
 */

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; 

    do {
        printf("This is a classic models auto store,\n"
               "Here you can get information about all\n"
               "our products and store information.\n\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit\n\n"
               "Enter a number that corresponds to your choice > ");
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








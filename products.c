#include "products.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "menu_template.h"


int stockQuery() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    char x[512]; /* Ahora es un char porque lo esta cogiendo del teclado */
    SQLINTEGER y;
    char query[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* Preguntamos al cliente por el codigo */
    printf("Introduce el codigo de producto: \n");
    fflush(stdout);

    /* Guardamos codigo en 'x' */
    fgets(x, sizeof(x), stdin);
    x[strlen(x)-1]='\0';

    
    /* Guardamos en 'query' la consulta */
    sprintf(query, "select p.quantityinstock from products p where p.productcode = \'%s\';", x);
	printf("%s\n", query);   /* IMPORTANTISIMO IMPRIMIR CONSULTA */

    /* Guarda resultado de la consulta en stmt */
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);


    SQLBindCol(stmt, 1, SQL_C_LONG, &y, sizeof(SQLINTEGER), NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Quantity in stock = %d\n", y);
    }
	
	
    SQLCloseCursor(stmt);  /* IMPORTANTISIMO */
	
    printf("\n");
    
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int findQuery(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    char x[512]; /* Ahora es un char porque lo esta cogiendo del teclado */
    SQLCHAR y[512];
    SQLCHAR z[512];
    char query[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* Preguntamos al cliente por el codigo */
    printf("Introduce parte del nombre del producto: \n");
    fflush(stdout);

    /* Guardamos codigo en 'x' */
    fgets(x, sizeof(x), stdin);
    x[strlen(x)-1]='\0';
    
    /* Guardamos en 'query' la consulta */
    sprintf(query, "select p.productcode, p.productname from products p where p.productname position() order by p.productcode;", x);
	printf("%s\n", query);   /* IMPORTANTISIMO IMPRIMIR CONSULTA */

    /* Guarda resultado de la consulta en stmt */
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t", buf);
    }
    
    printf("\n");

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, z, sizeof(z), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
        printf("%s\t%s\n", z, y);
    }


	
    SQLCloseCursor(stmt);  /* IMPORTANTISIMO */
	
    printf("\n");
    
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

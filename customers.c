#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "menu_template.h"
#include "customers.h"




int findCustomersQuery(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt; /* CONTENEDOR */
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLCHAR buf[512];
    SQLINTEGER cusnum;
    SQLCHAR confn[512], conln[512];
    char x[512]; /* NOMBRE */
    char query[512]; /* Char en el que guardar consulta */

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* Preguntamos al cliente el nombre de contacto */
    printf("Enter customer name > ");
    /* Guardamos codigo en 'x' */
    fgets(x, sizeof(x), stdin);
    x[strlen(x)-1]='\0';
    fflush(stdout);

    /* Guardamos en 'query' la consulta */
    sprintf(query, "select c.customernumber, c.customername, c.contactfirstname, c.contactlastname from customers c where (position (\'%s\' in c.contactfirstname)>0) or (position (\'%s\' in c.contactlastname)>0) order by c.customernumber", x, x);
	printf("%s\n", query);   /* IMPORTANTISIMO IMPRIMIR CONSULTA */
    printf("\n");

    /* Busqueda en base de datos y ejecucion */
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);


    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t\t", buf);
    }
    printf("\n");

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {

        ret = SQLGetData(stmt, 1, SQL_C_LONG, &cusnum, sizeof(SQLINTEGER), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, confn, sizeof(confn), NULL);
        ret = SQLGetData(stmt, 3, SQL_C_CHAR, conln, sizeof(conln), NULL);
        ret = SQLGetData(stmt, 4, SQL_C_CHAR, x, sizeof(x), NULL);
        printf("%d\t\t\t%s\t\t%s\t\t\t%s\n", cusnum, confn, conln, x);
    }

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




int listProductsCustomersQuery();
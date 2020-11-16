#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "menu_template.h"
#include "orders.h"


int openOrdersQuery(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt; /* CONTENEDOR */
    SQLRETURN ret; /* ODBC API return status */
    SQLINTEGER x;
    SQLCHAR buf[512];
    char query[512]; /* Char en el que guardar consulta */

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* Guardamos en 'query' la consulta */
    sprintf(query, "select o.ordernumber from orders o where o.shippeddate is null order by o.ordernumber;");
	printf("%s\n\n", query);   /* IMPORTANTISIMO IMPRIMIR CONSULTA */
 
    /* Busqueda en base de datos y ejecucion */
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);
    
    SQLBindCol(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);

    SQLDescribeCol(stmt, 1, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
    printf("%s\n", buf);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%d\n", x);
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


int rangeOrdersQuery(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt; /* CONTENEDOR */
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    char x[512], y[512]; /* FECHAS */
    SQLINTEGER ordnum;
    SQLCHAR orddate[512], shdate[512];
    char query[512]; /* Char en el que guardar consulta */


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* Preguntamos al cliente por las fechas */

    printf("Introduce la primera fecha (YYYY-MM-DD): \n");
    /* Guardamos codigo en 'x' */
    fgets(x, sizeof(x), stdin);
    x[strlen(x)-1]='\0';
    fflush(stdout);

    printf("Introduce la segunda fecha (YYYY-MM-DD): \n");
    /* Guardamos codigo en 'y' */
    fgets(y, sizeof(y), stdin);
    y[strlen(y)-1]='\0';
    fflush(stdout);

    /* Guardamos en 'query' la consulta */
    sprintf(query, "select o.ordernumber, o.orderdate, o.shippeddate from orders o  where"
                   "(o.orderdate>=\'%s\') and (o.orderdate <= \'%s\') order by o.ordernumber; ", x, y);
	printf("%s\n", query);   /* IMPORTANTISIMO IMPRIMIR CONSULTA */
    printf("\n");

    /* Busqueda en base de datos y ejecucion */
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
        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &ordnum, sizeof(SQLINTEGER), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, orddate, sizeof(orddate), NULL);
        ret = SQLGetData(stmt, 3, SQL_C_CHAR, shdate, sizeof(shdate), NULL);
        printf("%d\t\t%s\t%s\n", ordnum, orddate, shdate);
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




int detailOrdersQuery();
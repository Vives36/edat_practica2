#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "menu_template.h"
#include "orders.h"


int openQuery(){
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







int rangeQuery();
int detailQuery();
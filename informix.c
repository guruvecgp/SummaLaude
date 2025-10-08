#include <stdio.h>

EXEC SQL INCLUDE SQLCA; // Include SQL Communication Area

int main() {
    EXEC SQL BEGIN DECLARE SECTION;
    char db_name[20] = "stores_demo";
    char server_name[20] = "ol_informix1210"; // Replace with your Informix server name
    int customer_id;
    char customer_name[50];
    EXEC SQL END DECLARE SECTION;

    // Connect to the database
    EXEC SQL CONNECT TO :db_name AT :server_name;
    if (SQLCODE != 0) {
        fprintf(stderr, "Error connecting to database: %d\n", SQLCODE);
        return 1;
    }
    printf("Connected to Informix database.\n");

    // Select data
    EXEC SQL SELECT customer_id, customer_name INTO :customer_id, :customer_name FROM customers WHERE customer_id = 101;
    if (SQLCODE == 0) {
        printf("Customer ID: %d, Name: %s\n", customer_id, customer_name);
    } else if (SQLCODE == 100) { // Not found
        printf("Customer not found.\n");
    } else {
        fprintf(stderr, "Error selecting data: %d\n", SQLCODE);
    }

    // Disconnect from the database
    EXEC SQL DISCONNECT CURRENT;
    if (SQLCODE != 0) {
        fprintf(stderr, "Error disconnecting from database: %d\n", SQLCODE);
        return 1;
    }
    printf("Disconnected from Informix database.\n");

    return 0;
}

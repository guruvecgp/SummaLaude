#include <stdio.h>
#include <string.h>
#include <esql.h> // Informix ESQL/C header file

int main() {
    /* Declare host variables */
    char student_name[50];
    int student_score;

    /* Connect to the database */
    EXEC SQL CONNECT TO 'your_database_name';
    if (SQLCODE < 0) {
        fprintf(stderr, "Error connecting to database: %d\n", SQLCODE);
        return 1;
    }
    printf("Connected to database.\n");

    /* Get data from user */
    printf("Enter student name: ");
    scanf("%s", student_name);
    printf("Enter student score: ");
    scanf("%d", &student_score);

    /* Insert data into a table */
//    EXEC SQL INSERT INTO students (name, score) VALUES (:student_name, :student_score);
   EXEC SQL INSERT INTO students (name, score) VALUES (:student_name, :student_score);
    if (SQLCODE < 0) {
        fprintf(stderr, "Error inserting data: %d\n", SQLCODE);
        EXEC SQL ROLLBACK WORK;
        EXEC SQL DISCONNECT CURRENT;
        return 1;
    }
    printf("Data inserted successfully.\n");

    /* Commit the transaction */
    EXEC SQL COMMIT WORK;
    printf("Transaction committed.\n");

    /* Disconnect from the database */
    EXEC SQL DISCONNECT CURRENT;
    printf("Disconnected from database.\n");

    return 0;
}

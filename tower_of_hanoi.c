#include <stdio.h>

// Function to solve Tower of Hanoi puzzle
void towerOfHanoi(int n, char source, char destination, char auxiliary) {
    // Base case: If only one disk, move it directly
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", source, destination);
        return;
    }

    // Move n-1 disks from source to auxiliary, using destination as temporary
    towerOfHanoi(n - 1, source, auxiliary, destination);

    // Move the nth disk from source to destination
    printf("Move disk %d from rod %c to rod %c\n", n, source, destination);

    // Move n-1 disks from auxiliary to destination, using source as temporary
    towerOfHanoi(n - 1, auxiliary, destination, source);
}

int main() {
    int numberOfDisks;

    printf("Enter the number of disks: ");
    scanf("%d", &numberOfDisks);

    printf("The sequence of moves for Tower of Hanoi with %d disks:\n", numberOfDisks);
    // Call the function with initial rods A, B, C
    towerOfHanoi(numberOfDisks, 'A', 'C', 'B');

    return 0;
}

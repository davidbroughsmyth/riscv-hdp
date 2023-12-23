#include <stdio.h>

int main() {
    int a, b, result = 0;
    char operation;

    printf("Enter two 4-bit binary numbers (A and B): ");
    scanf("%d %d", &a, &b);

    printf("Enter the operation (+, -, *, /, &, |, ^): ");
    scanf(" %c", &operation);

    switch (operation) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                return 1;
            }
            result = a / b;
            break;
        case '&':
            result = a & b;
            break;
        case '|':
            result = a | b;
            break;
        case '^':
            result = a ^ b;
            break;
        default:
            printf("Invalid operation\n");
            return 1;
    }

    printf("Result: %d\n", result & 0xF); // Mask to ensure 4-bit output

    return 0;
}

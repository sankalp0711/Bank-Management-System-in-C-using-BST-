#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Account {
    int accNumber;
    char name[50];
    float balance;
    struct Account *left, *right;
} Account;

// Function to create a new account node
Account* createAccount(int accNumber, char name[], float balance) {
    Account* newAcc = (Account*)malloc(sizeof(Account));
    newAcc->accNumber = accNumber;
    strcpy(newAcc->name, name);
    newAcc->balance = balance;
    newAcc->left = newAcc->right = NULL;
    return newAcc;
}

// Insert a new account in BST
Account* insertAccount(Account* root, int accNumber, char name[], float balance) {
    if (root == NULL)
        return createAccount(accNumber, name, balance);
    if (accNumber < root->accNumber)
        root->left = insertAccount(root->left, accNumber, name, balance);
    else if (accNumber > root->accNumber)
        root->right = insertAccount(root->right, accNumber, name, balance);
    else
        printf("Account with number %d already exists!\n", accNumber);
    return root;
}

// Search account
Account* searchAccount(Account* root, int accNumber) {
    if (root == NULL || root->accNumber == accNumber)
        return root;
    if (accNumber < root->accNumber)
        return searchAccount(root->left, accNumber);
    else
        return searchAccount(root->right, accNumber);
}

// Display account details
void showAccount(Account* acc) {
    if (acc == NULL) {
        printf("Account not found!\n");
        return;
    }
    printf("\nAccount Number: %d\nName: %s\nBalance: %.2f\n", acc->accNumber, acc->name, acc->balance);
}

// Deposit money
void deposit(Account* acc, float amount) {
    if (acc) {
        acc->balance += amount;
        printf("Deposited %.2f. New Balance: %.2f\n", amount, acc->balance);
    }
}

// Withdraw money
void withdraw(Account* acc, float amount) {
    if (acc) {
        if (acc->balance >= amount) {
            acc->balance -= amount;
            printf("Withdrawn %.2f. New Balance: %.2f\n", amount, acc->balance);
        } else {
            printf("Insufficient Balance!\n");
        }
    }
}

// In-order traversal to list all accounts
void listAccounts(Account* root) {
    if (root != NULL) {
        listAccounts(root->left);
        showAccount(root);
        listAccounts(root->right);
    }
}

int main() {
    Account* root = NULL;
    int choice, accNumber;
    char name[50];
    float amount;

    while (1) {
        printf("\n--- Bank Menu ---\n");
        printf("1. Create Account\n");
        printf("2. Display Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. List All Accounts\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Account Number: ");
                scanf("%d", &accNumber);
                printf("Enter Name: ");
                getchar();  // Clear buffer
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline
                printf("Enter Initial Balance: ");
                scanf("%f", &amount);
                root = insertAccount(root, accNumber, name, amount);
                break;

            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &accNumber);
                showAccount(searchAccount(root, accNumber));
                break;

            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &accNumber);
                printf("Enter Deposit Amount: ");
                scanf("%f", &amount);
                deposit(searchAccount(root, accNumber), amount);
                break;

            case 4:
                printf("Enter Account Number: ");
                scanf("%d", &accNumber);
                printf("Enter Withdraw Amount: ");
                scanf("%f", &amount);
                withdraw(searchAccount(root, accNumber), amount);
                break;

            case 5:
                listAccounts(root);
                break;

            case 6:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

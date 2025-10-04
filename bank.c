#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct account {
    int accountNumber;
    char name[50];
    float balance;
};

struct account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Bank is full!\n");
        return;
    }
    struct account acc;
    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);
    getchar(); // clear newline
    printf("Enter account holder name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;
    printf("Enter initial balance: ");
    scanf("%f", &acc.balance);
    accounts[accountCount++] = acc;
    printf("Account created successfully!\n");
}

void depositMoney() {
    int accNum, found = 0;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) {
            accounts[i].balance += amount;
            printf("Amount deposited successfully! New balance: %.2f\n", accounts[i].balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

void withdrawMoney() {
    int accNum, found = 0;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", accounts[i].balance);
            } else {
                printf("Insufficient balance!\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

void checkBalance() {
    int accNum, found = 0;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) {
            printf("Current balance: %.2f\n", accounts[i].balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

void displayAccountDetails() {
    int accNum, found = 0;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) {
            printf("Account Number: %d\n", accounts[i].accountNumber);
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

void closeAccount() {
    int accNum, found = 0;
    printf("Enter account number to close: ");
    scanf("%d", &accNum);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) {
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            printf("Account closed successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

void displayAllAccounts() {
    printf("\n%-15s %-20s %-10s\n", "Account Number", "Name", "Balance");
    for (int i = 0; i < accountCount; i++) {
        printf("%-15d %-20s %-10.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}

void saveDataToFile() {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Failed to save data!\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d,%s,%.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
    fclose(file);
    printf("Data saved to accounts.txt\n");
}

void loadDataFromFile() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No data file found. Starting fresh.\n");
        return;
    }
    accountCount = 0;
    while (fscanf(file, "%d,%49[^,],%f\n", &accounts[accountCount].accountNumber, accounts[accountCount].name, &accounts[accountCount].balance) == 3) {
        accountCount++;
        if (accountCount >= MAX_ACCOUNTS) break;
    }
    fclose(file);
    printf("Data loaded from accounts.txt\n");
}

int main() {
    int choice;
    loadDataFromFile();
    while (1) {
        printf("\nBank Management System\n");
        printf("1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Check Balance\n5. Display Account Details\n6. Close Account\n7. Display All Accounts\n8. Save Data\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAccountDetails(); break;
            case 6: closeAccount(); break;
            case 7: displayAllAccounts(); break;
            case 8: saveDataToFile(); break;
            case 9: saveDataToFile(); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
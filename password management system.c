#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100 // Maximum number of users the program can handle.
#define PASSWORD_LENGTH 100 // Maximum password length.

typedef struct { // Creates a User structure with username and password fields.
    char username[50];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS]; // Array to store user details.
int user_count = 0; //	Tracks the number of registered users.

// Function to check password complexity
int is_valid_password(const char *password) { // Ensures that passwords meet security standards 
    int length = strlen(password);
    if (length < 8) return 0; // Password must be at least 8 characters long

    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int i; // Declare loop variable outside the loop
    
    for (i = 0; i < length; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
        if (ispunct(password[i])) has_special = 1;
    }
    
    return has_upper && has_lower && has_digit && has_special;
}
 
// Function to add a new user
void add_user() { // Adds a new user with a unique username and a valid password.
    if (user_count >= MAX_USERS) {
        printf("Cannot add more users. User limit reached.\n");
        return;
    }
    
    char username[50], password[PASSWORD_LENGTH];
    int i; // Declare loop variable outside the loop
    
    printf("Enter username: ");
    scanf("%s", username);

    // Check for duplicate username
    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists. Try a different one.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", password);

    // Validate password
    if (!is_valid_password(password)) {
        printf("Password must be at least 8 characters long and include upper/lowercase letters, digits, and special characters.\n");
        return;
    }

    // Store the user data
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    printf("User added successfully.\n");
}

// Function to delete a user
void delete_user() {
    char username[50];
    int i, j; // Declare loop variables outside the loop
    
    printf("Enter username to delete: ");
    scanf("%s", username);

    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Shift users to delete the user
            for (j = i; j < user_count - 1; j++) {
                users[j] = users[j + 1];
            }
            user_count--;
            printf("User deleted successfully.\n");
            return;
        }
    }

    printf("User not found.\n");
}

// Function to search for a user
void search_user() {
    char username[50];
    int i; // Declare loop variable outside the loop
    
    printf("Enter username to search: ");
    scanf("%s", username);

    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username: %s\n", users[i].username);
            printf("Password: %s\n", users[i].password);
            return;
        }
    }

    printf("User not found.\n");
}

// Menu function
void menu() { // Provides a user-friendly interface to access system functions
    int choice;
    do {
        printf("\nPassword Management System\n");
        printf("1. Add User\n");
        printf("2. Delete User\n");
        printf("3. Search User\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_user();
                break;
            case 2:
                delete_user();
                break;
            case 3:
                search_user();
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}

int main() { // Entry point of the program.
    menu();
    return 0;
}

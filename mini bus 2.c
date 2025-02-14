#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 30             
#define MAX_NAME_LENGTH 50
#define MAX_USERS 100

struct User {
    char username[50];
    char password[50];
};

struct Booking {
    char name[MAX_NAME_LENGTH];
    int seatNo;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    // Add more fields as needed
};

struct Booking bookings[MAX_SEATS];
int bookedSeats = 0;

void displayMainMenu();      // Function to display main menu
void create(struct User users[], int *numUsers);       // Function to create an account
int loginUser(struct User users[], int numUsers, char username[], char password[]);   // Function to login User
void bookSeat();             // Function to book a seat
void viewReservation();      // Function to check Reservation
void editReservation();      // Function to edit Reservation
void printTicket();          // Function to print ticket
void cancelTicket();         // Function to cancel ticket

int main() {
    // Initialize user data
    struct User users[MAX_USERS];
    int numUsers = 0;
    int loggedInUserId = -1; // Index of the logged-in user

    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                create(users, &numUsers);
            } else if (choice == 2) {
                char username[50];
                char password[50];

                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1) {
                    printf("Login failed. Please check your username and password.\n");
                } else {
                    printf("Login successful. Welcome, %s!\n", username);
                }
            } else if (choice == 3) {
                printf("Exiting the program.\n");
                exit(0);
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        } else {
            int userChoice;
            printf("\n=== Bus Booking Menu ===\n");
            printf("1. Book a seat\n");
            printf("2. View reservations\n");
            printf("3. Edit a reservation\n");
            printf("4. Print a ticket\n");
            printf("5. Cancel Ticket\n");
            printf("6. Logout\n");
            printf("Enter your choice: ");

            scanf("%d", &userChoice);

            switch (userChoice) {
                case 1:
                    bookSeat();
                    break;
                case 2:
                    viewReservation();
                    break;
                case 3:
                    editReservation();
                    break;
                case 4:
                    printTicket();
                    break;
                case 5:
                    cancelTicket();
                    break;  
                case 6:
                    printf("Logging Out\n");
                    loggedInUserId = -1;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}

void displayMainMenu() {
    printf("\n=== Main Menu ===\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

void create(struct User users[], int *numUsers) {
    if (*numUsers >= MAX_USERS) {
        printf("User limit reached. Cannot create more accounts.\n");
        return;
    }

    printf("\nEnter Username: ");
    scanf("%s", users[*numUsers].username);
    printf("Enter Password: ");
    scanf("%s", users[*numUsers].password);

    (*numUsers)++;
    printf("Account created successfully!\n");
}

int loginUser(struct User users[], int numUsers, char username[], char password[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Return the index of the logged-in user
        }
    }
    return -1; // Return -1 if login fails
}

void bookSeat() {
    if (bookedSeats >= MAX_SEATS) {
        printf("No more seats available.\n");
        return;
    }

    struct Booking newBooking;

    printf("Enter Name: ");
    scanf("%s", newBooking.name);

    printf("Enter Seat Number: ");
    scanf("%d", &newBooking.seatNo);

    printf("Enter Source: ");
    scanf("%s", newBooking.source);

    printf("Enter Destination: ");
    scanf("%s", newBooking.destination);

    // Add more input fields as needed

    bookings[bookedSeats++] = newBooking;
    printf("Seat booked successfully.\n");
}

void viewReservation() {
    if (bookedSeats == 0) {
        printf("No reservations made yet.\n");
        return;
    }

    printf("All reservations:\n");
    printf("%-10s %-20s %-20s %-20s\n", "Seat No.", "Name", "Source", "Destination");
    for (int i = 0; i < bookedSeats; ++i) {
        printf("%-10d %-20s %-20s %-20s\n", bookings[i].seatNo, bookings[i].name, bookings[i].source, bookings[i].destination);
    }
}

void editReservation() {
    int seatToEdit;
    printf("Enter Seat number to edit: ");
    scanf("%d", &seatToEdit);

    int found = 0;
    for (int i = 0; i < bookedSeats; ++i) {
        if (bookings[i].seatNo == seatToEdit) {
            printf("Enter new Name: ");
            scanf("%s", bookings[i].name);

            printf("Enter new Source: ");
            scanf("%s", bookings[i].source);

            printf("Enter new Destination: ");
            scanf("%s", bookings[i].destination);
            // Add more fields to edit as needed

            printf("Reservation edited successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Reservation not found.\n");
    }
}

void printTicket() {
    int seatToPrint;
    printf("Enter seat number to print ticket: ");
    scanf("%d", &seatToPrint);

    int found = 0;
    for (int i = 0; i < bookedSeats; ++i) {
        if (bookings[i].seatNo == seatToPrint) {
            printf("Ticket for Seat No. %d\n", bookings[i].seatNo);
            printf("Passenger Name: %s\n", bookings[i].name);
            printf("Source: %s\n", bookings[i].source);
            printf("Destination: %s\n", bookings[i].destination);
            // Add more fields to print as needed

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Reservation not found.\n");
    }
}

void cancelTicket() {
    int seatToCancel;
    printf("Enter seat number to cancel: ");
    scanf("%d", &seatToCancel);

    int found = 0;
    for (int i = 0; i < bookedSeats; ++i) {
        if (bookings[i].seatNo == seatToCancel) {
            for (int j = i; j < bookedSeats - 1; ++j) {
                bookings[j] = bookings[j + 1];
            }
            bookedSeats--;
            printf("Ticket for seat number %d canceled successfully.\n", seatToCancel);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Reservation not found.\n");
    }
}


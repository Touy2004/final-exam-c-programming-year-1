#include <stdio.h>
#include <time.h>

#define MAX_EMPLOYEES 100
int employeeId;

struct Employee {
    char name[50];
    int id;
    time_t checkin_time;
    time_t checkout_time;
};

struct Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Function prototypes
void loadEmployeesFromFile();
void saveEmployeesToFile();
void recordCheckin();
void recordCheckout();
void displayEmployee();

void main() {
    loadEmployeesFromFile();
    int choice;

    do {
        printf("\nHR Management System\n");
        printf("1. Record Check-in\n");
        printf("2. Record Check-out\n");
        printf("3. Display Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                recordCheckin();
                break;
            case 2:
                printf("Enter employee ID: ");
                scanf("%d", &employeeId);
                recordCheckout();
                break;
            case 3:
                printf("Enter employee ID: ");
                scanf("%d", &employeeId);
                displayEmployee();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);

}

void loadEmployeesFromFile() {
    FILE *file = fopen("employees.csv", "r");
    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%[^,],%d,%lld,%lld\n", employees[employeeCount].name, &employees[employeeCount].id,
                  &employees[employeeCount].checkin_time, &employees[employeeCount].checkout_time) == 4) {
        employeeCount++;
    }

    fclose(file);
}

void saveEmployeesToFile() {
    FILE *file = fopen("employees.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        fprintf(file, "%s,%d,%lld,%lld\n", employees[i].name, employees[i].id,
                employees[i].checkin_time, employees[i].checkout_time);
    }

    fclose(file);
}

void recordCheckin() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Maximum employee limit reached.\n");
        return;
    }

    struct Employee newEmployee;
    printf("Enter employee name: ");
    scanf("%s", newEmployee.name);
    printf("Enter employee ID: ");
    scanf("%d", &newEmployee.id);

    time(&newEmployee.checkin_time);
    newEmployee.checkout_time = 0;

    employees[employeeCount++] = newEmployee;
    printf("Employee added.\n");
    saveEmployeesToFile();
}

void recordCheckout() {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == employeeId) {
            time(&employees[i].checkout_time);
            printf("Checkout recorded for employee %d.\n", employeeId);
            saveEmployeesToFile();
            return;
        }
    }
    printf("Employee ID not found.\n");
}

void displayEmployee() {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == employeeId) {
            printf("Employee Name: %s\n", employees[i].name);
            printf("Employee ID: %d\n", employees[i].id);
            printf("Check-in Time: %s", ctime(&employees[i].checkin_time));
            if (employees[i].checkout_time != 0) {
                printf("Check-out Time: %s", ctime(&employees[i].checkout_time));
            } else {
                printf("Check-out Time: Not recorded yet.\n");
            }
            return;
        }
    }
    printf("Employee ID not found.\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
struct Customer
{
    char name[50]; 
    int age;
    long long int mobileno;
    float height;
    float weight;
    int slotTime;
}; 

void displaySlots()
{
    printf("1. 9:00 AM - 10:00 AM\n");
    printf("2. 10:00 AM - 11:00 AM\n");
    printf("3. 11:00 AM - 12:00 PM\n");
    printf("4. 12:00 PM - 1:00 PM\n");
    printf("5. 1:00 PM - 2:00 PM\n");
    printf("6. 2:00 PM - 3:00 PM\n");
    printf("7. 3:00 PM - 4:00 PM\n");
    printf("8. 4:00 PM - 5:00 PM\n");
}  


void addCustomer()  //the function adds a new customer to a file in customers.txt
{
    struct Customer c; // c is variable of struture which store customer details
    FILE *fp;  //then we make a file inwhich storing some value in .txt file

    // Open file for appending
    fp = fopen("customers.txt", "a");

    // Check if file opened successfully
    if (fp == NULL)  
    {
        printf("Error opening file.\n");
        exit(1);
    }

    // Geting customer details from the user
    printf("Enter customer name: ");
    scanf("%s", c.name);
    printf("Enter customer age: ");
    scanf("%d", &c.age);
    printf("Enter customer's contact no: ");
    scanf("%lld", &c.mobileno);
    printf("Enter customer height (in meters): ");
    scanf("%f", &c.height);
    printf("Enter customer weight (in kilograms): ");
    scanf("%f", &c.weight);

    // Display available slots
    printf("Available slots: \n");

    displaySlots();
    printf("Enter slot time: ");
    scanf("%d", &c.slotTime);

    // Write customer details to file
    fprintf(fp, "%s %d %lld %.2f %.2f %d\n", c.name, c.age, c.mobileno, c.height, c.weight, c.slotTime);

    // Close file
    fclose(fp);

    printf("Customer record added successfully.\n");
}

void deleteCustomer()
{
    char name[50];
    FILE *fp, *tempfp;
    char line[100];
    int found = 0;   
    fp = fopen("customers.txt", "r");

    // Open temporary file for writing in customer.txt
    tempfp = fopen("temp.txt", "w");

    // Check if file opened successfully
    if (fp == NULL || tempfp == NULL) // if any one of the file not found 
    {
        printf("Error opening file.\n");
        exit(1);
    }

    // Get customer name to delete
    printf("Enter customer name to delete: ");
    scanf("%s", name);

    // Reading the original file line by line and copy all lines except the one that matches the customer name to a temporary file
    while (fgets(line, 100, fp) != NULL)  //If the line doesn't contain the name of the customer to delete
    {
        if (strstr(line, name) == NULL)  // it writes the line to the temporary file 
        {
            fputs(line, tempfp);  
        }
        else
        {
            found = 1;  //If the line does contain the name of the customer to delete, it sets found to 1 to indicate that the record was found but not yet deleted.
        }
    }

    // after reading the file the function close both files
    fclose(fp);  
    fclose(tempfp);

    // function Delete original file
    remove("customers.txt");

    // Rename temporary file to original file name
    rename("temp.txt", "customers.txt");

    if (found)  // if my record was found and deleted  the function print successfully
    {
        printf("Customer record deleted successfully.\n");
    }
    else
    {
        printf("Customer record not found.\n");
    }
}

void searchCustomer()
{
    char name[50];
    FILE *fp;
    char line[100];
    int found = 0;
    long long int mobileno;

    // Open file for reading
    fp = fopen("customers.txt", "r");

    // Check if file opened successfully
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    // Get customer name to search for
    printf("Enter customer name to search for: ");
    scanf("%s", name);
    printf("\nEnter cusomer's contact no: ");
    scanf("%lld", &mobileno);
    // Search for customer name in file
   while (fgets(line, 100, fp) != NULL) {
    if (strstr(line, name) != NULL) {
        // Display customer details
        printf("Customer details: %s", line);
        found = 1;
        break;
    }
}
// Close file
fclose(fp);

if (!found) {
    printf("Customer record not found.\n");
}
   
}
void display(){
    char name[50];
    FILE *fp;
    char line[100];
    fp = fopen("customers.txt", "r");  //it opens the "customers.txt" file in read mode using fopen and assigns the file pointer to fp. If the file fails to open, it displays an error message and exits the program using exit
     while (fgets(line, 100, fp) != NULL) // fgets means it read the file line by line 
    {
        
            printf("Customer details: %s", line); // Each line is stored in the line variable
         
    }

    // Close file
    fclose(fp);

} //This function is called in the main function when the user selects option 5 to display all customer details.
int main()
{
    int choice;
    do
    {
        printf("\n*** FITNESS CLUB MANAGEMENT SYSTEM ***\n");
        printf("1. Add Customer\n");
        printf("2. Delete Customer\n");
        printf("3. Search Customer\n");
        printf("4. Display Customer details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCustomer();
            break;
        case 2:
            deleteCustomer();
            break;
        case 3:
            searchCustomer();
            break;
        case 4:
        display();
        break;
        case 5:
            printf("Goodbye!\n");
            
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

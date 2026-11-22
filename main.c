
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student
{
    int rollno;
    char name[50];
    int age;
    char department[30];
    float marks;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("====================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

// 1. Add Student
void addStudent()
{
    FILE *fp;
    struct Student s;
    struct Student temp;

    int found = 0;

    fp = fopen(FILE_NAME, "a+");

    if (fp == NULL)
    {
        printf("Unable to open file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollno);

    rewind(fp);

    while (fscanf(fp, "%d|%49[^|]|%d|%29[^|]|%f\n",
                  &temp.rollno,
                  temp.name,
                  &temp.age,
                  temp.department,
                  &temp.marks) == 5)
    {
        if (temp.rollno == s.rollno)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nRoll number already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Department: ");
    scanf(" %29[^\n]", s.department);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d|%s|%d|%s|%.2f\n",
            s.rollno,
            s.name,
            s.age,
            s.department,
            s.marks);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

// 2. View All Students
void viewStudents()
{
    FILE *fp;
    struct Student s;
    int count = 0;

    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    printf("%-10s %-20s %-6s %-15s %-10s\n",
           "Roll No", "Name", "Age", "Department", "Marks");

    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%29[^|]|%f\n",
                  &s.rollno,
                  s.name,
                  &s.age,
                  s.department,
                  &s.marks) == 5)
    {
        printf("%-10d %-20s %-6d %-15s %-10.2f\n",
               s.rollno,
               s.name,
               s.age,
               s.department,
               s.marks);

        count++;
    }

    if (count == 0)
    {
        printf("No student records found!\n");
    }

    fclose(fp);
}

// 3. Search Student
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int rollno;
    int found = 0;

    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d|%49[^|]|%d|%29[^|]|%f\n",
                  &s.rollno,
                  s.name,
                  &s.age,
                  s.department,
                  &s.marks) == 5)
    {
        if (s.rollno == rollno)
        {
            printf("\nStudent Found!\n");

            printf("Roll Number: %d\n", s.rollno);
            printf("Name       : %s\n", s.name);
            printf("Age        : %d\n", s.age);
            printf("Department : %s\n", s.department);
            printf("Marks      : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent not found!\n");
    }

    fclose(fp);
}

// 4. Update Student
void updateStudent()
{
    FILE *fp, *temp;
    struct Student s;

    int rollno;
    int found = 0;

    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d|%49[^|]|%d|%29[^|]|%f\n",
                  &s.rollno,
                  s.name,
                  &s.age,
                  s.department,
                  &s.marks) == 5)
    {
        if (s.rollno == rollno)
        {
            found = 1;

            printf("\nEnter New Name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Department: ");
            scanf(" %29[^\n]", s.department);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d|%s|%d|%s|%.2f\n",
                s.rollno,
                s.name,
                s.age,
                s.department,
                s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        if (remove(FILE_NAME) == 0 &&
            rename("temp.txt", FILE_NAME) == 0)
        {
            printf("\nStudent updated successfully!\n");
        }
        else
        {
            printf("\nError replacing student file!\n");
            printf("Updated data remains in temp.txt\n");
        }
    }
    else
    {
        remove("temp.txt");
        printf("\nStudent not found!\n");
    }
}

// 5. Delete Student
void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;

    int rollno;
    int found = 0;

    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d|%49[^|]|%d|%29[^|]|%f\n",
                  &s.rollno,
                  s.name,
                  &s.age,
                  s.department,
                  &s.marks) == 5)
    {
        if (s.rollno == rollno)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%d|%s|%.2f\n",
                s.rollno,
                s.name,
                s.age,
                s.department,
                s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        if (remove(FILE_NAME) == 0 &&
            rename("temp.txt", FILE_NAME) == 0)
        {
            printf("\nStudent deleted successfully!\n");
        }
        else
        {
            printf("\nError replacing student file!\n");
            printf("Remaining data is in temp.txt\n");
        }
    }
    else
    {
        remove("temp.txt");
        printf("\nStudent not found!\n");
    }
}


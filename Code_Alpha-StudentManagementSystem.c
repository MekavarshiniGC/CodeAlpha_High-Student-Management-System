#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    char name[20];
    int rollno;
    long long phone;
    float att;
    int total;
    float per;
};

void addRecord();
void displayRecords();
void searchRecord();
void updateRecord();
void deleteRecord();

int main()
{
    int choice;

    do
    {
        printf("\n\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: 
				addRecord(); 
				break;
            case 2: 
				displayRecords(); 
				break;
            case 3: 
				searchRecord(); 
				break;
            case 4: 
				updateRecord(); 
				break;
            case 5: 
				deleteRecord(); 
				break;
            case 6: 
				printf("Exiting...\n"); 
				break;
            default: 
				printf("Invalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}

void addRecord()
{
    FILE *fp;
    struct student s;

    fp = fopen("Student.data","ab");

    printf("\nEnter Name: ");
    scanf("%s",s.name);

    printf("Enter Roll No: ");
    scanf("%d",&s.rollno);

    printf("Enter Phone: ");
    scanf("%lld",&s.phone);

    printf("Enter Attendance: ");
    scanf("%f",&s.att);

    printf("Enter Total Marks: ");
    scanf("%d",&s.total);

    printf("Enter Percentage: ");
    scanf("%f",&s.per);

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);

    printf("\nRecord Added Successfully!\n");
}

void displayRecords()
{
    FILE *fp;
    struct student s;

    fp = fopen("Student.data","rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n--------------------------------------------------------------------------------\n");
    printf("NAME\tROLLNO\tPHONE\t\tATT\tTOTAL\tPER\n");
    printf("--------------------------------------------------------------------------------\n");

    while(fread(&s,sizeof(s),1,fp))
    {
        printf("%s\t%d\t%lld\t%.1f\t%d\t%.2f\n",
               s.name,s.rollno,s.phone,s.att,s.total,s.per);
    }

    fclose(fp);
}

void searchRecord()
{
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("Student.data","rb");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.rollno == roll)
        {
            printf("\nRecord Found\n");
            printf("Name       : %s\n",s.name);
            printf("Roll No    : %d\n",s.rollno);
            printf("Phone      : %lld\n",s.phone);
            printf("Attendance : %.1f\n",s.att);
            printf("Total      : %d\n",s.total);
            printf("Percentage : %.2f\n",s.per);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("Record Not Found!\n");

    fclose(fp);
}

void updateRecord()
{
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("Student.data", "rb+");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct student), 1, fp) == 1)
    {
        if(s.rollno == roll)
        {
            printf("\nRecord Found!\n");

            printf("Enter New Name: ");
            scanf("%s", s.name);

            printf("Enter New Phone: ");
            scanf("%lld", &s.phone);

            printf("Enter New Attendance: ");
            scanf("%f", &s.att);

            printf("Enter New Total Marks: ");
            scanf("%d", &s.total);

            printf("Enter New Percentage: ");
            scanf("%f", &s.per);

            /* Move file pointer back to current record */
            fseek(fp, -sizeof(struct student), SEEK_CUR);

            /* Overwrite the record */
            fwrite(&s, sizeof(struct student), 1, fp);

            found = 1;
            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if(!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}
void deleteRecord()
{
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("Student.data","rb");

    if(fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    temp = fopen("Temp.data","wb");

    printf("Enter Roll Number to Delete: ");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.rollno == roll)
        {
            found = 1;
            continue;
        }

        fwrite(&s,sizeof(s),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("Student.data");
    rename("Temp.data","Student.data");

    if(found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
}
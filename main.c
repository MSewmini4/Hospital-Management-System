#include <stdio.h>
#include <string.h>
#include "hospital.h"

int findPatientById(const char *id)
{
    int i;

    for (i=0;i<patientCount;i++)
    {
        if (strcmp(patientID[i], id)==0)
        {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    int choice;
    char id[MAX_ID];
    int index;
    initializeSystem();
    loadData();

    do
    {
        displayMainMenu();

        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid input.\n");

            while(getchar()!= '\n')
            {

            }
            continue;
        }

        switch(choice)
        {
        case 1:
            displayLookupTables();
            break;

        case 2:
            registerPatient();
            break;

        case 3:
            displayBedMatrix();
            break;

        case 4:
            displayPatientsByPriority();
            break;

        case 5:
            if (patientCount==0)
            {
                printf("\nNo patients registered.\n");
            }
            else
            {
                printf("\nEnter patient ID: ");
                scanf("%19s",id);

                index=findPatientBy(id);

                if(index==-1)
                {
                    printf("\nPatient not found.\n");

                }
                else
                {
                    printfPatientBill(index);
                }
            }
            break;

        case 6:
            generateReports();
            break;

        case 7:
            saveData();
            break;

        case 8:
            saveData();

                printf("\nThank you fod using Smart Hospital System.\n");

                break;

        default:
            printf("\nInvalid choice. "
                   "Please select 1-8.\n");

        }


           } while(choice!=8);

        return 0;

}

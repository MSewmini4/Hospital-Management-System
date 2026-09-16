#include<stdio.h>
#include "hospital.h"

void saveData(void)
{
    FILE *bedFile;
    FILE *patientFile;

    int w;
    int b;
    int i;

    bedFile=fopen("beds_status.txt","w");
    patientFile=fopen("patient_records.txt","w");

    if(bedFile==NULL||patientFile==NULL)
    {
        printf("Error opening files.\n");

        if(bedFile!=NULL)
        {
            fclose(bedFile);
        }

        if(patientFile!=NULL)
        {
            fclose(patientFile);
        }

        return;
    }

    for(w=0; w<MAX_WARDS; w++)
    {

        for(b=0; b<wardCapacities[w]; b++)
        {
            fprintf(bedFile,"%d %d %d\n",w,b,bedOccupancy[w][b]);
        }
    }

    fprintf(patientFile,"%d\n",patientCount);

    for(i=0;i<patientCount;i++)
    {
        fprintf(patientFile,"%s|%s|%d|%d|%d|%d|%d|%d|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n",
                patientId[i],patientName[i],patientAge[i],patientUrgency[i],patientSpecialty[i],patientAdmitted[i],patientWard[i],patientDays[i],patientBed[i],patientBaseFee[i],patientSurchage[i],patientWardCost[i],patientGross[i],patientDiscount[i],patientFinal[i],patientWait[i]);

    }

    fclose(bedFile);
    fclose(patientFile);

    printf("\nData saved successfully.\n");
}

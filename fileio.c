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
                patientID[i],patientName[i],patientAge[i],patientUrgency[i],patientSpecialty[i],patientAdmitted[i],patientWard[i],patientDays[i],patientBed[i],patientBaseFee[i],patientSurchage[i],patientWardCost[i],patientGross[i],patientDiscount[i],patientFinal[i],patientWait[i]);

    }

    fclose(bedFile);
    fclose(patientFile);

    printf("\nData saved successfully.\n");
}

void loadData(void)
{
    FILE *bedFile;
    FILE *patientFile;

    int w;
    int b;
    int status;
    int count;
    int i;

    bedFile=fopen("beds_status.txt","r");
    patientFile=fopen("patient_records.txt","r");

    if(bedFile!=NULL)
    {
        while(fscanf(bedFile,"%d %d %d", &w,&b,&status)==3)
        {
            if(w>=0 && w<MAX_WARDS && b>=0 && b<wardCapacities[w])
            {
                bedOccupancy[w][b]=status?1:0;
            }
        }
        fclose(bedFile);
    }

    if(patientFile!=NULL)
    {
        if(fscanf(patientFile,"%d\n",&count)==1)
        {
            if(count<0)
            {
                count=0;
            }

            if(count>MAX_PATIENTS)
            {
                count=MAX_PATIENTS;
            }

            patientCount=0;

            for(i=0;i<count;i++)
            {
                if(fscanf(patientFile,"%19[^|]|%99[^|]|%d|%d|%d|%d|%d|%d|%d|%lf|%lf|%lf|%lf|%lf|%lf|%lf\n",
patientID[i],patientName[i],&patientAge[i],&patientUrgency[i],&patientSpecialty[i],&patientAdmitted[i],&patientWard[i],&patientDays[i],&patientBed[i],&patientBaseFee[i],&patientSurchage[i],&patientWardCost[i],&patientGross[i],&patientDiscount[i],&patientFinal[i],&patientWait[i])==16)
{
    patientCount++;
}
            }
        }

        fclose(patientFile);
    }

    printf("Existing data loaded.patients: %d\n",patientCount);
}

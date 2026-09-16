#include<stdio.h>
#include "hospital.h"

void generatereports(void)
{
    int i;
    int w;

    int urgencyCounts[4]={0,0,0,0};

    double totalRevenue=0.0;
    double totalDiscount=0.0;

    int highestIndex=-1;
    double highestBill=-1.0;

    if(patientCount==0)
    {
        printf("\nNo patient data available.\n");
        return;
    }

    for(i=0;i<patientCount;i++)
    {
        urgencyCounts[patientUrgency[i]]++;
        totalRevenue+=patientFinal[i];
        totalDiscount+=patientDiscount[i];

        if(patientFinal[i]>highestBill)
        {
            highestBill=patientFinal[i];
            highestIndex=i;
        }
    }

    printf("\n===============================================\n");
    printf("        SMART HOSPITAL PERFORMANCE REPORT\n");
    printf("===============================================\n");

    printf("Normal Patients   : %d\n",urgencyCounts[1]);
    printf("urgency Patients  : %d\n",urgencyCounts[2]);
    printf("Critical Patients : %d\n",urgencyCounts[3]);
    printf("Total Revenue     : LKR %.2f\n",totalRevenue);
    printf("Total discounts   : LKR %.2f\n",totalDiscount);

    printf("\n---------------BED OCCUPANCY----------------\n");

    for(w=0;w<MAX_WARDS;w++)
    {
        int occupied=0;
        int capacity=wardCapacities[w];

        for(i=0;i<capacity;i++)
        {
            occupied+=bedOccupancy[w][i];
        }

        printf("%-30s : %d / %d  (%.2f%%)\n",wardNames[w],occupied,capacity,((double)occupied / capacity)*100.0);
    }

    if(highestIndex>=0)
    {
        printf("\n-------------HIGHEST BILL ------------------\n");
        printf("Patient Name : %s\n",patientName[highestIndex]);
        printf("Patient ID   : %s\n",patientId[highestIndex]);
        printf("Final Bill   : LKR %.2f\n",patientFinal[highestIndex]);

    }

    printf("===============================================\n");
}

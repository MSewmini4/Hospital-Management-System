#include<stdio.h>
#include<string.h>
#include "hospital.h"

const char *specialtyName[SPECIALTIES]=
{
    "General practice(OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};


const double specialtyFees[SPECIALTIES]=
{
    1500.0,
    2500.0,
    4500.0,
    5000.0
};

const int specialtyTimes[SPECIALTIES]=
{
    15,
    20,
    30,
    30
};


const int specialtyCaps[SPECIALTIES]=
{
    30,
    20,
    12,
    10
};

const char *wardNames[MAX_WARDS]=
{
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU(Intensive Carre Unit)"
};

const double wardRates[MAX_WARDS]=
{
    3000.0,
    6000.0,
    12000.0,
    25000.0
};

const int wardCapacities[MAX_WARDS]=
{
    20,
    10,
    10,
    5
};

int bedOccupancy[MAX_WARDS][MAX_BEDS];
int patientCount=0;

char patientId[MAX_PATIENTS][MAX_ID];
char patientName[MAX_PATIENTS][MAX_NAME];

int patientAge[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];
int patientBed[MAX_PATIENTS];

double patientBaseFee[MAX_PATIENTS];
double patientSurchage[MAX_PATIENTS];
double patientWardCost[MAX_PATIENTS];
double patientGross[MAX_PATIENTS];
double patientDiscount[MAX_PATIENTS];
double patientFinal[MAX_PATIENTS];
double patientWait[MAX_PATIENTS];

void initializeSystem(void)
{
    int w;
    int b;

    for(w=0; w<MAX_WARDS; w++)
    {
        for(b=0; b<MAX_BEDS; b++)
        {
            bedOccupancy[w][b]=0;
        }
    }

    patientCount=0;

}

void displayMainMenu(void)

{
    printf("\n===============================================\n");
    printf("     SMART HOSPITAL SYSTEM\n");
    printf("===============================================\n");

    printf("1.Display lookup tables\n");
    printf("2.Register patient\n");
    printf("3.Display bed occupancy matrix\n");
    printf("4.Display patients by priority\n");
    printf("5.Display patient bill\n");
    printf("6.Generate performance reports\n");
    printf("7.Save data\n");
    printf("8.Exit\n");

    printf("-----------------------------------------------\n");
    printf("Enter your choice: ");

}

void displayLookupTables(void)
{
    int i;
    printf("\n-------------DOCTOR SPECIALTIES------------\n");

    printf("%-4s %-28s %-12s %-10s %-10s\n",
           "ID","Specialty","Fee","Minutes","Capacity");

    for(i=0; i<SPECIALTIES; i++)
    {
        printf("%-4d %-28s %-12.2f %-10d %-10d\n",
               i+1,
               specialtyNames[i],
               specialtyFees[i],
               specialtyTimes[i],
               specialtyCaps[i]);
    }

    printf("\n------------------WARDS --------------------\n");

    printf("%-4s %-30s %-15s %-10s \n",
           "ID","Ward","Daily Rate","Capacity");

    for(i=0; i<MAX_WARDS; i++)
    {
        printf("%-4d %-30s %-15.2f %-10d\n",
               i+1,
               wardNames[i],
               wardRates[i],
               wardCapacities[i]);
    }

}

void displayBedMatrix(void)
{
    int w;
    int b;

    printf("\n---------BED OCCUPANCY MATRRIX---------\n");
    printf("0=Available\n");
    printf("1=Occupied\n\n");

    for(w=0; w<MAX_WARDS; w++)
    {
        printf("%s : ",wardNames[w]);

        for(b=0; b < wardCapacities[w];b++)
        {
            printf("%d",bedOccupancy[w][b]);
        }

        printf("\n");

    }
}

int getFreeBed(int wardIndex)
{
    int b;



if(wardIndex<0||wardIndex>=MAX_WARDS)
{
    return -1;

}

for(b=0; b<wardCapacities[wardIndex]; b++)
{
    if(bedOccupancy[wardIndex][b]==0)
    {
        return b;
    }
}
return -1;
}


int calculateWaitingTime(int specialtyIndex)
{
    int i;
    int queueCount=0;

    for(i=0; i<patientCount;i++)
    {
        if(patientSpecialty[i]==specialtyIndex)
        {
            queueCount++;

        }
    }
    return queueCount *specialtyTimes[specialtyIndex];
}

double calculateEmergencySurcharge(double baseFee,int urgencyLevel)
{
    if(urgencyLevel==2)
    {
        return baseFee*0.20;

    }

    if(urgencyLevel==3)
    {
        return baseFee*0.30;
    }
    return 0;
}

double calculateWardCost(int wardIndex,int days)
{
    if(wardIndex<0||wardIndex>=MAX_WARDS||days<=0)
    {
        return 0.0;
    }

    return wardRates[wardIndex]*days;
}

double calculateAgeDiscount(double gross,int age)
{
    if(age<5||age>65)
    {
        return gross*0.15;
    }
    return 0.0;
}

const char *urgencyText(int level)
{
    if(level==3)
    {
        return "Level 3 (Critical)";

    }

    if(level==2)
    {
        return "Level 2 (Urgent)";
    }

    return "Level 1 (Normal)";
}

void registerPatient(void)
{
    int i;
    int specialty;
    int urgency;
    int admitted;
    int ward;
    int days;
    int bed;
    int wait;



if(patientCount>=MAX_PATIENTS)
{
    printf("\nPatient limit reached.\n");
    return;
}

i=patientCount;

printf(patientId[i],"PAT-%04d",1001+i);


printf("\n===============================================\n");
printf("          PATIENT REGISTRATION\n");
printf("===============================================\n");

printf("Patient ID:%s\n",patientId[i]);

printf("Enter patient name:");
scanf("%99[^\n]",patientName[i]);

       do
{
    printf("Enter patient age(0-120):");
    scanf("%d",&patientAge[i]);

}
while(patientAge[i]<0||patientAge[i]>120);


do
{
    printf("\nUrgency Levels\n");
        printf("1.Normal\n");
        printf("2.Urgent\n");
        printf("3.Critical\n");

        printf("Select urgency:");
        scanf("%d",&urgency);

    }
    while(urgency<1||urgency>3);

    patientUrgency[i]=urgency;

                      printf("\nSpecialties\n");

                      for(int s=0; s<SPECIALTIES; s++)
    {
        printf("%d. %s\n",s+1,specialtyNames[s]);

        }

do
{
    printf("select specialty(1-4):");
    scanf("%d",&specialty);

}
while(specialty<1||specialty>4);

patientSpecialty[i]=specialty-1;

                    do
{
    printf("\nAdmitted to a ward?\n");
        printf("1.Yes\n");
        printf("0.No\n");
        printf("Choice:");
        scanf("%d",&admitted);

    }
    while(admitted!=0 && admitted!=1);

    patientAdmitted[i]=admitted;

                       patientWard[i]=-1;
                       patientBed[i]=-1;
                       patientDays[i]=0;

                       if(admitted==1)
    {
        printf("\nAvailable Wards\n");

            for(int w=0; w<MAX_WARDS; w++)
            {
                printf("%d. %s | Capacity:%d | Rate:%.2f/day\n",
                       w+1,wardNames[w],wardCapacities[w],wardRates[w]);



            }

            do
            {
                printf("Select ward(1-4): ");
                scanf("%d",&ward);

            }
            while(ward<1||ward>4);

            ward--;

            bed=getFreeBed(ward);

            if(bed==-1)
            {
                printf("\nSelected ward is  full.\n");
                printf("Patient will be registered as OPD.\n");

                patientAdmitted[i]=0;
            }
            else
            {
                do
                {
                    printf("Enter number of days(1-365): ");
                    scanf("%d",&days);

                }
                while(days<1||days>365);

                patientWard[i]=ward;
                patientBed[i]=bed;
                patientDays[i]=days;

                bedOccupancy[ward][bed]=1;
            }
        }


wait=calculateWaitingTime(patientSpecialty[i]);

patientWait[i]=(double)wait;

patientBaseFee[i]=specialtyFees[patientSpecialty[i]];

patientSurchage[i]=calculateEmergencySurcharge(patientBaseFee[i],patientUrgency[i]);

patientWardCost[i]=calculateWardCost(patientWard[i],patientDays[i]);

patientGross[i]=patientBaseFee[i]+patientSurchage[i]+patientWardCost[i];

patientDiscount[i]=calculateAgeDiscount(patientGross[i],patientAge[i]);

patientFinal[i]=patientGross[i]-patientDiscount[i];

patientCount++;

printf("\nPatient registered successfully!\\n");

printPatientBill(i);

}



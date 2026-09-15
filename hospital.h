#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define MAX_NAME 100
#define MAX_ID 20
#define MAX_WARDS 4
#define MAX_BEDS 20
#define SPECIALTIES 4

extern const char *specialtyNames[SPECIALTIES];
extern const double specialtyFees[SPECIALTIES];
extern const int specialtyTimes[SPECIALTIES];
extern const int specialtyCaps[SPECIALTIES];

extern const char *wardNames[MAX_WARDS];
extern const double wardRates[MAX_WARDS];
extern const int wardCapaities[MAX_WARDS];

extern int bedOccupancy[MAX_WARDS][MAX_BEDS];
extern int patientCount;

extern char patientID[MAX_PATIENTS][MAX_ID];
extern char patientName[MAX_PATIENTS][MAX_NAME];
extern int patientAge[MAX_PATIENTS];
extern int patientUrgency[MAX_PATIENTS];
extern int patientSpecialty[MAX_PATIENTS];
extern int patientAdmitted[MAX_PATIENTS];
extern int patientWard[MAX_PATIENTS];
extern int patientDays[MAX_PATIENTS];
extern int patientBed[MAX_PATIENTS];

extern double patientBaseFee[MAX_PATIENTS];
extern double patientSurchage[MAX_PATIENTS];
extern double patientWardCost[MAX_PATIENTS];
extern double patientGross[MAX_PATIENTS];
extern double patientDiscount[MAX_PATIENTS];
extern double patientFinal[MAX_PATIENTS];
extern double patientWait[MAX_PATIENTS];

void initializeSystem(void);
void displayMainMenu(void);
void displayLookupTables(void);
void displayBedMatrix(void);
void displayPatient(void);
void registerPatient(void);
void printPatientBill(int index);
void displaypatientsByPriority(void);
void generatereports(void);
void saveData(void);
void loadData(void);

int getFreeBed(int wardIndex);
int calculateWaitingTime(int specialtyIndex);
double calculateEmergencySurchage(double baseFee,int urgencyLevel);
double calculateWardCost(int wardIndex,int days);
double calculateAgeDiscount(double gross,int age);
const char *urgencyText(int level);

#endif

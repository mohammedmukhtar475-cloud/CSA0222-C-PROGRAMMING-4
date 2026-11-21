#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    int day, month, year;
} VisitDate;

typedef struct {
    char name[50];
    int age;
    char phone[16];
    BloodPressure bp;
    VisitDate visitDate;
} Patient;

void addPatient(Patient *p, const char *name, int age,
                const char *phone, int systolic,
                int diastolic, VisitDate date)
{
    if (p == NULL)
        return;

    snprintf(p->name, sizeof(p->name), "%s", name);
    p->age = age;
    snprintf(p->phone, sizeof(p->phone), "%s", phone);
    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;
    p->visitDate = date;
}

void printPatient(const Patient *p)
{
    printf("%s Age:%d Phone:%s BP:%d/%d Date:%02d/%02d/%04d\n",
           p->name, p->age, p->phone,
           p->bp.systolic, p->bp.diastolic,
           p->visitDate.day, p->visitDate.month,
           p->visitDate.year);
}

int main()
{
    Patient patients[MAX_PATIENTS];
    int count = 0;

    VisitDate d = {21, 11, 2026};

    addPatient(&patients[count++], "Arun", 35,
               "9876543210", 120, 80, d);

    addPatient(&patients[count++], "Meena", 42,
               "9123456780", 130, 85, d);

    printf("Patient Register:\n");

    for (int i = 0; i < count; i++)
        printPatient(&patients[i]);

    return 0;
}

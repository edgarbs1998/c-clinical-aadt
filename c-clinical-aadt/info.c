#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info.h"
#include "listTad.h"
#include "patient.h"
#include "utils.h"

//LOAD
void importPatientsFromFile(char* fileNamePatients, char* fileNameClinicalData, PtList patients) {
	FILE* f;
	int error = fopen_s(&f, fileNamePatients, "r"); //opens the file in read mode

	if (error) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatients);
		return;
	}

	int patientID;
	char nextLine[1024];
	int countPatients = 0; //Patients count
	int clinicalDataCount = 0; //ClinicalData count

	while (fgets(nextLine, sizeof(nextLine), f)) {
		if (strlen(nextLine) < 1)
			continue;

		nextLine[strlen(nextLine) - 1] = '\0';

		char** tokens = split(nextLine, 5, ";");
		//tokens[0] - id
		//tokens[1] - birthdate
		//tokens[2] - gender
		//tokens[3] - hospital
		//tokens[4] - district

		patientID = atoi(tokens[0]);
		int day, month, year;
		sscanf_s(tokens[1], "%d/%d/%d", &day, &month, &year);

		Date date = dateCreate(day, month, year);
		Patient newPatient = createPatient(patientID, date, tokens[2][0], tokens[3], tokens[4]);
		int size;
		listSize(patients, &size);
		listAdd(patients, size, newPatient);

		free(tokens);
		countPatients++;
	}


	FILE* f2;
	int error2 = fopen_s(&f2, fileNameClinicalData, "r"); //opens the file in read mode

	if (error2) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatients);
		return;
	}

	char nextLine2[1024];

	while (fgets(nextLine2, sizeof(nextLine2), f2)) {
		if (strlen(nextLine2) < 1)
			continue;
		
		nextLine[strlen(nextLine2) - 1] = '\0';

		char** tokens = split(nextLine2, 6, ";");
		//tokens[0] - id
		//tokens[1] - date
		//tokens[2] - bmi
		//tokens[3] - glucose
		//tokens[4] - insulin
		//tokens[5] - mcp1

		int idPatient = atoi(tokens[0]);

		Patient patient1;
		int pos;
		if (findPatientById(patients, idPatient, &patient1, &pos) == 0) {
			printf("Error finding patient id!\n");
			system("pause");
			return;
		};


		int day, month, year;
		sscanf_s(tokens[1], "%d/%d/%d", &day, &month, &year);
		Date registDate = dateCreate(day, month, year);

		patient1.clinicalData.age = (float) getAge(registDate, patient1.birthdate);
		patient1.clinicalData.bmi = incrementalAverage(patient1.clinicalData.bmi, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[2]));
		patient1.clinicalData.glucose = incrementalAverage(patient1.clinicalData.glucose, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[3]));
		patient1.clinicalData.insulin = incrementalAverage(patient1.clinicalData.insulin, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[4]));
		patient1.clinicalData.mcp1 = incrementalAverage(patient1.clinicalData.mcp1, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[5]));


		clinicalDataCount++;


		Patient oldElem;
		listSet(patients, pos, patient1, &oldElem);
		
	}
	fclose(f2);
	printf("Foram lidos %d pacientes e informação sobre %d dados clinicos \n", countPatients, clinicalDataCount);
}

float incrementalAverage(float avg_n, int n, float v_n1) {
	if (n == 0) {
		return v_n1;
	}

	return (avg_n*n + v_n1) / n + 1;
}

int findPatientById(PtList list, int id, Patient* patient, int* pos) {
	int size;
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, patient);
		if (patient->id == id) {
			*pos = i;
			return 1;
		}
	}
	return 0;
}


int getAge(Date actualdate, Date birthdate) {
	int age = actualdate.year - birthdate.year;
	if (actualdate.month < birthdate.month)
		age--;
	else if (actualdate.month == birthdate.month) {
		if (actualdate.day < birthdate.day)
			age--;
	}
	return age;
}

//CLEAR
void clearData(PtList *list) {
	int size;
	listSize(*list, &size);
	printf("Foram apagados %d registos de pacientes\n", size);
	listDestroy(list);

	// TODO After CLEAR command LOAD not working
}

//SHOW
void showData(PtList list) {
	if (listIsEmpty(list)) {
	}
	listPrint(list);
}

// QUIT
void QuitProgram(PtList list) {
	int size;
	listSize(list, &size);
	if (size > 0) {	
	listDestroy(&list);
	}
	exit(0);
}

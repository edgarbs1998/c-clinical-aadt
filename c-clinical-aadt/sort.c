#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "string.h"
#include "utils.h"


//Sort by birthdate
void sortByBirthDate(PtList list) {
	int size;
	listSize(list, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	bubbleSortBirthDate(auxList, size);

	listPrint(auxList);
}


//bubble sort
void bubbleSortBirthDate(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {

			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			int cmp = dateCmp(elem1.birthdate, elem2.birthdate);

			if (cmp > 0) {

				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}
		}
	}
}

//Sort by hospital
void sortByHospital(PtList list) {
	int size = 0;
	ListElem elem;
	PtList auxList = listCreate(10);
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	int size2 = 0;
	listSize(auxList, &size2);
	bubbleSortHospital(auxList, size2);

	listPrint(auxList);
}

//bubble sort
void bubbleSortHospital(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {

			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			if (strcmp(elem1.hospital, elem2.hospital) > 0)

			{
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}

			if (strcmp(elem1.hospital, elem2.hospital) == 0) {

				int cmp = dateCmp(elem1.birthdate, elem2.birthdate);

				if (cmp > 0) {

					listSet(list, j + 1, elem1, &elem2);
					listSet(list, j, elem2, &elem1);
				}
			}
		}
	}
}

//Sort by district
void sortByDistrict(PtList list) {
	int size = 0;
	ListElem elem;
	PtList auxList = listCreate(10);
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	int size2 = 0;
	listSize(auxList, &size2);
	bubbleSortDistrict(auxList, size2);

	listPrint(auxList);
}

//buble sort
void bubbleSortDistrict(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {

			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			if (strcmp(elem1.district, elem2.district) > 0)

			{
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}

			if (strcmp(elem1.district, elem2.district) == 0) {

				if (strcmp(elem1.hospital, elem2.hospital) > 0)

				{
					listSet(list, j + 1, elem1, &elem2);
					listSet(list, j, elem2, &elem1);
				}

			}
		}
	}
}

// Sort menu
void showSortMenu(PtList list) {
	String command;
	int option;
	printf("\n===================================================================================");
	printf("\n                                        SORT                                       ");
	printf("\n===================================================================================");
	printf("\n0 - Ordenar por data de nascimento");
	printf("\n1 - Ordenar por hospital");
	printf("\n2 - Ordenar por distrito");
	printf("\nOption> ");

	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	option = atoi(command);

	// TODO Keep sort menu after execution

	switch (option)
	{
	case 0: sortByBirthDate(list);
		break;
	case 1: sortByHospital(list);
		break;
	case 2: sortByDistrict(list);
		break;
	default: showSortMenu(list);
	}
}
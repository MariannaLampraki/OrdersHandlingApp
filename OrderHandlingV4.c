#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int choice, n=0, k=0;
int* p=&n;
int* r=&k;
FILE *orders;
float discount(int bigBottles, int smallBottles, int initalCost);
typedef struct date {
	int day;
	int month;
	int year;
}DATE;
typedef struct orders {
	int BigBottles; //0.02
	int SmallBottles; //0.008
	char clientName[10];
	DATE creationDate;
	DATE dueDate;
	float initialCost;
	float finalCost;
	int dateExecuted;
	char status[7];
}ORDER;
ORDER makeOrder();
ORDER allOrders[10];
void DisplayOrders(ORDER list[], int length);
void DisplayPendingOrders(ORDER list[], int length);
void ExecuteOrder();
void SaveToFile(ORDER list[], int length);


int main(int argc, char *argv[]) {
	orders = fopen("data.txt", "w");
	fclose(orders);
	printf("Menu: 0.Exit, 1.Create Order, 2.Display Client Orders, 3.Display Pending Orders, 4.Save Pending Orders to File, 5.Load Pending Orders from File, 6.Execute Order\n");
	scanf("%d", &choice);
	while (choice != 0) {
		switch (choice) {
			case 0:
				break;
			case 1:
				makeOrder();
				break;
			case 2:
				if (n>0) {
					DisplayOrders(allOrders, n);
				}
				break;
			case 3:
				DisplayPendingOrders(allOrders, n);
				break;
			case 4:
				fopen("data.txt", "w");
				SaveToFile(allOrders, n);
				fclose(orders);
				break;
			case 5:
				ReadFromFile();
				break;
			case 6:
				ExecuteOrder(allOrders, n);
				break;
		}
		printf("Make another choice: ");
		scanf("%d", &choice);
	}
	return 0;
}

float discount(int bigBottles, int smallBottles, int initialCost) {
	int finalCost;
	if (initialCost > 600) {
		finalCost = initialCost*0.8;
	}
	else if ((initialCost > 200) || (bigBottles+smallBottles > 3000)) {
		finalCost = initialCost*0.92;
	}
	else {
		finalCost = initialCost;
	}
	return finalCost;
}

ORDER makeOrder() {
	ORDER currentOrder;
	printf("Client Name: ");
	scanf("%s", &currentOrder.clientName);
	printf("Creation Date(DD MM YYYY, where D=Day, M=Month, Y=Year): ");
	scanf("%d %d %d", &currentOrder.creationDate.day, &currentOrder.creationDate.month, &currentOrder.creationDate.year);
	printf("Due Date (DD MM YYYY, where D=Day, M=Month, Y=Year): ");
	scanf("%d %d %d", &currentOrder.dueDate.day, &currentOrder.dueDate.month, &currentOrder.dueDate.year);
	printf("How Many Big Bottles: ");
	scanf("%s", &currentOrder.BigBottles);
	printf("How Many Small Bottles: ");
	scanf("%d", &currentOrder.SmallBottles);
	strcpy(currentOrder.status, "Pending");
	currentOrder.initialCost = currentOrder.BigBottles*0.02 + currentOrder.SmallBottles*0.008;
	currentOrder.finalCost = discount(currentOrder.BigBottles, currentOrder.SmallBottles, currentOrder.initialCost);
	allOrders[n] = currentOrder;
	(*p)++;
}

void DisplayOrders(ORDER list[], int length) {
	int i, j;
	for (i=0; i<length; i++) {
		printf("%s\t", list[i].clientName);
		printf("%d/%d/%d\t", list[i].creationDate.day, list[i].creationDate.month, list[i].creationDate.year);
		printf("%d/%d/%d\t", list[i].dueDate.day, list[i].dueDate.month, list[i].dueDate.year);
		printf("%.4f\t", list[i].initialCost);
		printf("%.4f\t", list[i].finalCost);
		printf("%s\n", list[i].status);
	}
}

void DisplayPendingOrders(ORDER list[], int length) {
	int i, j;
	for (i=0; i<length; i++) {
		if (strcmp(list[i].status, "Pending")==0) {
			printf("%s\t", list[i].clientName);
			printf("%d/%d/%d\t", list[i].creationDate.day, list[i].creationDate.month, list[i].creationDate.year);
			printf("%d/%d/%d\t", list[i].dueDate.day, list[i].dueDate.month, list[i].dueDate.year);
			printf("%.4f\t", list[i].initialCost);
			printf("%.4f\t", list[i].finalCost);
			printf("%s\n", list[i].status);
		}
	}
}

void ExecuteOrder() {
	strcpy(allOrders[k].status, "Ready");
	(*r)++;
}

void SaveToFile(ORDER list[], int length) {
	FILE *output = fopen("data.txt", "w");
    int i;
    
    for (i=0; i<length; i++) {
        if (strcmp(list[i].status, "Pending")==0) {
            fprintf(output, "%s\t %d/%d/%d\t %d/%d/%d\t %.4f\t %.4f\t %s\n", list[i].clientName, list[i].creationDate.day, list[i].creationDate.month, list[i].creationDate.year,
                    list[i].dueDate.day, list[i].dueDate.month, list[i].dueDate.year, list[i].initialCost, list[i].finalCost, list[i].status);
        }
    }
    
    fclose(output);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car{
	int ID;
	char *model;
	int yearmake;
	char *color;
	int price;
	char *dealer;
};

void printCar(struct Car car)
{
	printf("%d | %s | %d | %s | %d | %s\n", car.ID, car.model, car.yearmake, car.color, car.price, car.dealer);
}

struct condition{
	int attr;
	void *value;
}

void *get_value(int attr, struct Car *table)
{

}
int *where()
{

}

int main(int argc, char **argv)
{
	struct Car cars[] = {
        	{1000, "Accord", 2008, "Gray", 10000, "Pohanka"},
        	{1001, "Corolla", 2015, "White", 18000, "AutoNation"},
	        {1012, "Civic", 2015, "Blue", 18000, "Mitsubishi"},
        	{1013, "Accord", 2015, "Green", 12000, "Sonic"},
        	{1014, "Accord", 2020, "Gray", 20000, "Suburban"},
        	{1015, "Maxima", 2016, "Red", 17000, "Atlantic"},
        	{1016, "Civic", 2021, "Red", 21000, "Ganley"},
        	{1017, "Focus", 2015, "Red", 12000, "Victory"},
        	{1018, "Camry", 2015, "White", 18000, "Atlantic"},
        	{1019, "Maxima", 2018, "Gray", 15000, "Pohanka"},
        	{1020, "Accord", 2015, "Blue", 16000, "Pohanka"},
        	{1021, "Accord", 2020, "Blue", 20000, "GM"}
    	};

	for(int i = 0; i<12; i++){
		printCar(cars[i]);
	}

	int cond1[12];

	for(int i =0; i<12; i++){
		if(!strcmp(cars[i].model, "Accord")){
			cond1[i] = 1;
			printf("Here is the row %d\n", cars[i].ID);
		}else{
			cond1[i] = 0;
		}
	}

	printf("\n");
	int cond2[12];
	for(int i = 0; i<12; i++){
		if(!strcmp(cars[i].dealer, "Pohanka")){
			cond2[i] = 1;
			printf("Here is the row %d\n", cars[i].ID);
		}else{
			cond2[i] = 0;
		}
	}

	int final[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	for(int i =0; i<12; i++){
		final[i] &= cond1[i]; 
		final[i] &= cond2[i];
	}

	for(int i = 0; i<12; i++){

		if(final[i] == 1){
			printCar( cars[i]);
		}
	}


	return 0;
}

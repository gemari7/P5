#include "QAPSolGenerator.h"
#include "QAPInstance.h"
#include "QAPSolution.h"
#include <stdlib.h>

void QAPSolGenerator::genRandomSol(QAPInstance &instance, QAPSolution &solution){

	int numBuildings=instance.getNumBuildings();
	int numLocations=numBuildings;

	for (int i = 0; i < numBuildings; i++){
		do{
			randomLocation=rand()%numLocations;

			if(!hasBuilding(randomLocation)){
				putBuildingIn(i,randomLocation);
			}
		}while(whereIsBuilding(i)!=randomLocation);
	}
}

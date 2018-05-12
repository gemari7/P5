#include "QAPSolGenerator.h"
#include "QAPInstance.h"
#include "QAPSolution.h"
#include <stdlib.h>

void QAPSolGenerator::genRandomSol(QAPInstance &instance, QAPSolution &solution){

	int numBuildings=instance.getNumBuildings();
	int numLocations=numBuildings;
	int randomLocation;

	for (int i = 0; i < numBuildings; i++){
		do{
			randomLocation=rand()%numLocations;

			if(!solution.hasBuilding(randomLocation)){
				solution.putBuildingIn(i,randomLocation);
			}
		}while(solution.whereIsBuilding(i)!=randomLocation);
	}
}

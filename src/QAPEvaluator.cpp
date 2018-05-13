#include <QAPEvaluator.h>
#include <QAPInstance.h>
#include <QAPSolution.h>

double QAPEvaluator::_numEvaluations = 0.;

double QAPEvaluator::computeFitness(QAPInstance &instance){
	double fitness = 0;
	
	for(int i=0;i<instance.getNumBuildings();i++){
		for(int j=0;j<instance.getNumBuildings();j++){
			fitness+=instance.getFlow(i,j)*instance.getDistance(i,j);
		}
	}

	_numEvaluations++;
	
	return fitness;
}

double QAPEvaluator::computeDeltaFitness(QAPInstance &instance,QAPSolution &solution,int indexBuilding,int indexLocation) {
	double deltaFitness;

	_numEvaluations += (1. / instance.getNumBuildings());

	int oldIndexLocation=solution.whereIsBuilding(indexBuilding);
	
	solution.putBuildingIn(indexBuilding,indexLocation);
	deltaFitness=computeFitness(instance);
	solution.putBuildingIn(indexBuilding,oldIndexLocation);
	
	return deltaFitness;
}

void QAPEvaluator::resetNumEvaluations() {
	_numEvaluations = 0;
}

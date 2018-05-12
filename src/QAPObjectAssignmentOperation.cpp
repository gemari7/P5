#include <QAPObjectAssignmentOperation.h>

QAPObjectAssignmentOperation::QAPObjectAssignmentOperation(){
	_indexLocation = 0;
	_indexBuilding = 0;
	_deltaFitness = 0;
}

QAPObjectAssignmentOperation::~QAPObjectAssignmentOperation() {
}

void QAPObjectAssignmentOperation::apply(QAPSolution& solution) {
	solution.putBuildingIn(_indexBuilding, _indexLocation);
	double actualFitness = solution.getFitness();
	double newFitness = actualFitness + _deltaFitness;
	solution.setFitness(newFitness);
}

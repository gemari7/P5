#include "QAPSolution.h"
#include "QAPInstance.h"
#include <iostream>

using namespace std;

QAPSolution::QAPSolution(QAPInstance &instance) {
	_numBuildings = instance.getNumBuildings();
	_fitness = 0;
	_fitnessAssigned = false;
	_sol = new int[_numBuildings];
	if (!_sol) {
		cerr << "No se ha reservado memoria correctamente para _sol" << endl;
		exit(-1);
	}
	int i;
	for (i = 0; i < _numBuildings; i++) {
		_sol[i] = 0;
	}
}

QAPSolution::~QAPSolution() {
	_numBuildings = 0;
	_fitness = 0;
	delete [] _sol;
}

void QAPSolution::putObjectIn(int object, int buildings) {
	_sol[object] = buildings;
	_fitnessAssigned = false;
}

int QAPSolution::whereIsObject(int object) {
	return _sol[object];
}

double QAPSolution::getFitness() const {
	return _fitness;
}

void QAPSolution::setFitness(double fitness) {
	_fitness = fitness;
	_fitnessAssigned = true;
}

void QAPSolution::copy(Solution& solution) {

	QAPSolution &auxSol = (QAKPSolution&) solution;

	for (int i = 0; i < _numBuildings; i++)
		_sol[i] = auxSol._sol[i];

	_fitness = auxSol._fitness;
	_fitnessAssigned = auxSol._fitnessAssigned;
}

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
	
	for (int i = 0; i < _numBuildings; i++) {
		_sol[i] = 0;
	}
}

QAPSolution::~QAPSolution() {
	_numBuildings = 0;
	_fitness = 0;
	delete [] _sol;
}

int QAPSolution::whereIsBuilding(int building) {
	for(int i;i<_numBuildings;i++){
		if(_sol[i]==building){
			return i;
		}
	}
	return 0;
}

void QAPSolution::copy(Solution& solution) {
	QAPSolution &auxSol = (QAPSolution&) solution;

	for (int i = 0; i < _numBuildings; i++)
		_sol[i] = auxSol._sol[i];

	_fitness = auxSol._fitness;
	_fitnessAssigned = auxSol._fitnessAssigned;
}

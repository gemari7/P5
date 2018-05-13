#include "QAPEvaluator.h"
#include "QAPObjectAssignmentOperation.h"
#include "QAPTabuSearch.h"
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void QAPTabuSearch::initialise(QAPInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void QAPTabuSearch::setSolution(QAPSolution* solution) {

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método QAPTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new QAPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void QAPTabuSearch::run(QAPStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();

	unsigned numBuildings = _instance->getNumBuildings();
	unsigned numIterations = 0;

	while (!stopCondition.reached()) {

		vector<int> perm;
		QAPInstance::randomPermutation(numBuildings, perm);
		double bestDeltaFitness = 0;
		bool initialisedDeltaFitness = false;
		QAPObjectAssignmentOperation bestOperation;

		for (unsigned i = 0; i < numBuildings; i++)
		{
			unsigned IndexBuilding = perm[i];
			
			if (_shortTermMem_aux.end() == _shortTermMem_aux.find(IndexBuilding)) {

				for (unsigned j =0 ; j<numBuildings; j++) {

					//? no estoy seguro si el algoritmo se ejecuta de la misma forma siendo QAP

					if (_solution->whereIsBuilding(IndexBuilding) == ((int)j))
						continue;

					if (_shortTermMem_aux.find(j) == _shortTermMem_aux.end()) {

						double deltaFitness = QAPEvaluator::computeDeltaFitness(*_instance, *_solution, IndexBuilding, (int)j); 

						if (deltaFitness < bestDeltaFitness	or initialisedDeltaFitness == false) { //? he puesto < en vez de >, not sure
							initialisedDeltaFitness = true;
							bestDeltaFitness = deltaFitness;
							bestOperation.setValues(IndexBuilding,j,deltaFitness);
						}
					}
				}
			}
		}

		

		bestOperation.apply(*_solution);
		
		_shortTermMem.push(bestOperation.getBuilding());
		_shortTermMem_aux.insert(bestOperation.getBuilding());
		
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);
		}

		
		if (QAPEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}

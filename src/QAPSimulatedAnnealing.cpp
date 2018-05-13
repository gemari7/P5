#include "QAPSimulatedAnnealing.h"
#include "QAPSolution.h"
#include "QAPSolGenerator.h"
#include "QAPEvaluator.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

void QAPSimulatedAnnealing::setSolution(QAPSolution* solution) {
	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método QAPTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL){
		_bestSolution = new QAPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void QAPSimulatedAnnealing::run(QAPStopCondition& stopCondition) {

	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution == NULL){
		cerr << "Simulated annealing has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numBuildings = _instance->getNumBuildings();
	unsigned numIterations = 0;

	while (stopCondition.reached()==false){

		int indexBuilding1 = rand()%numBuildings;
		int indexBuilding2 = rand()%numBuildings;

		double deltaFitness = QAPEvaluator::computeDeltaFitness(*_instance, *_solution, indexBuilding1, indexBuilding2);

		if (QAPSimulatedAnnealing::accept(deltaFitness)){

			int location1 = _solution->whereIsBuilding(indexBuilding1);
			int location2 = _solution->whereIsBuilding(indexBuilding2);
			_solution->putBuildingIn(indexBuilding1, location2);
			_solution->putBuildingIn(indexBuilding2, location1);
			_solution->setFitness(_solution->getFitness() + deltaFitness);

			if (QAPEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0){ //? mayor o menor que 0?
				_bestSolution->copy(*_solution);
			}
		}
		numIterations++;
		_results.push_back(_solution->getFitness());

		if (numIterations % _itsPerAnnealing){	
			_T *= _annealingFactor;
		}

		stopCondition.notifyIteration();
	}
}

bool QAPSimulatedAnnealing::accept(double deltaFitness) {

	double auxDeltaFitness = deltaFitness;

	if (QAPEvaluator::isToBeMinimised()){
		auxDeltaFitness=(-deltaFitness);

	}

	double prob = exp(auxDeltaFitness / _T);
	double randSample = ((double)rand() / RAND_MAX);

	return randSample<prob;
}

void QAPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, QAPInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	int numBuildings = _instance->getNumBuildings();
	double averageFDiffs = 0.;

	for (int i = 0; i < numInitialEstimates; i++){
		QAPSolution sol(instance);
		QAPSolGenerator::genRandomSol(instance, sol);
		sol.setFitness(QAPEvaluator::computeFitness(instance, sol));
		int indexBuilding1 = rand()%numBuildings;
		int indexBuilding2 = rand()%numBuildings;
		double deltaFitness = QAPEvaluator::computeDeltaFitness(instance, sol, indexBuilding1, indexBuilding2);
		averageFDiffs += max(fabs(deltaFitness),10.); 
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}

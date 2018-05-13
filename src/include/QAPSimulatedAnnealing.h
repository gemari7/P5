
#ifndef INCLUDE_QAPSIMULATEDANNEALING_H_
#define INCLUDE_QAPSIMULATEDANNEALING_H_

#include "QAPSolution.h"
#include "QAPInstance.h"
#include "QAPMetaheuristic.h"
#include "QAPStopCondition.h"
#include <cstdlib>

class QAPSimulatedAnnealing : public QAPMetaheuristic {

protected:
	
	double _T;
	double _initialProb;
	double _annealingFactor;
	unsigned _itsPerAnnealing;
	QAPSolution *_solution;
	QAPInstance *_instance;

	vector<double> _results;

	bool accept(double deltaFitness);

public:

	QAPSimulatedAnnealing(){
		_T = 0;
		_initialProb = 0;
		_annealingFactor = 0;
		_itsPerAnnealing = 0;
		_solution = NULL;
		_instance = NULL;
	}

	virtual ~QAPSimulatedAnnealing(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	virtual void run(QAPStopCondition &stopCondition);

	void setSolution(QAPSolution* solution);

	void initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, QAPInstance &instance);

	vector<double>& getResults() {
		return _results;
	}
};


#endif

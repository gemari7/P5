#ifndef INCLUDE_QAPTABUSEARCH_H_
#define INCLUDE_QAPTABUSEARCH_H_

#include "QAPSolution.h"
#include "QAPInstance.h"
#include "QAPMetaheuristic.h"
#include "QAPStopCondition.h"
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;

class QAPTabuSearch : public QAPMetaheuristic{
protected:

	QAPSolution *_solution;
	QAPInstance *_instance;
	queue<unsigned> _shortTermMem;
	set<unsigned> _shortTermMem_aux;
	unsigned _tabuTennure;

	vector<double> _results;

public:

	QAPTabuSearch(){
		_solution = NULL;
		_instance = NULL;
		_tabuTennure = 0;
	}

	virtual ~QAPTabuSearch(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	}

	void initialise(QAPInstance * instance, unsigned tabuTennure);

	void setSolution(QAPSolution* solution);

	virtual void run(QAPStopCondition &stopCondition);


	vector<double>& getResults() {
		return _results;
	}
};

#endif

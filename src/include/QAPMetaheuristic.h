#ifndef INCLUDE_MQKPMETAHEURISTIC_H_
#define INCLUDE_MQKPMETAHEURISTIC_H_

#include <QAPSolution.h>
#include <QAPStopCondition.h>
#include <cstdlib>

class QAPMetaheuristic {

protected:
	QAPSolution *_bestSolution;

public:
	QAPMetaheuristic(){
		_bestSolution = NULL;
	}

	virtual ~QAPMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	virtual void run (QAPStopCondition &stopCondition) = 0;

	QAPSolution*& getBestSolution(){
		return _bestSolution;
	}
};

#endif

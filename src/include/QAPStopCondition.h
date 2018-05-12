#ifndef INCLUDE_QAPSTOPCONDITION_H_
#define INCLUDE_QAPSTOPCONDITION_H_

#include "QAPEvaluator.h"
#include <Timer.h>
#include <iostream>

using namespace std;

class QAPStopCondition{
	unsigned _maxEvaluations;
	unsigned _maxIterations;
	double _maxTime;
	unsigned _numIterations;
	Timer _time;

public:
	QAPStopCondition(){
		_maxEvaluations = 0;
		_maxIterations = 0;
		_maxTime = 0;
		_numIterations = 0;
		_time.reset();
	}
	
	virtual ~QAPStopCondition(){};

	virtual bool reached(){
		bool result = false;

		double numEvaluations = QAPEvaluator::getNumEvaluations();
		double elapsedTime = _time.elapsed_time(Timer::VIRTUAL);
		unsigned numIterations = _numIterations;

		if (_maxEvaluations > 0 && numEvaluations >= _maxEvaluations)
			result = true;

		if (_maxIterations > 0 && numIterations >= _maxIterations)
			result = true;

		if (_maxTime > 0 && elapsedTime >= _maxTime)
			result = true;

		return result;
	}

	void setConditions(unsigned maxEvaluations, unsigned maxIterations, double maxTime){
		_maxEvaluations = maxEvaluations;
		_maxIterations = maxIterations;
		_maxTime = maxTime;
		_time.reset();
	}

	void notifyIteration(){
		_numIterations++;
	}
};

#endif

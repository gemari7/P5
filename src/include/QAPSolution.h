#ifndef __QAPSOLUTION_H__
#define __QAPSOLUTION_H__

#ifndef __QAPINSTANCE_H__
#include "QAPInstance.h"
#else
class QAPInstance;
#endif


class MQKPSolution : public Solution {
protected:
	
	int * _sol;
	int _numBuildings;
	double _fitness;
	bool _fitnessAssigned; 

public:
	
	QAPSolution(QAPInstance &instance);

	
	virtual ~QAPSolution();

	
	void putObjectIn(int object, int building);

	
	int whereIsObject(int object);

	
	virtual double getFitness() const;

	
	void setFitness(double fitness);

	
	virtual void copy(Solution &solution);

	
	bool hasValidFitness(){
		return _fitnessAssigned;
	}
};

#endif

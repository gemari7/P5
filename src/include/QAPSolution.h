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

	
	inline void putBuildingIn(int building, int location){
		_sol[location] = building;
		_fitnessAssigned = false;
	}

	int whereIsBuilding(int building);
	
	inline bool hasBuilding(int location){
		if(_sol[i]==0){
			return false;
		}

		else{
			return true;
		}
	}

	
	virtual inline double getFitness() const{
		return _fitness;
	}

	
	void setFitness(double fitness){
		_fitness = fitness;
		_fitnessAssigned = true;
	}

	
	virtual void copy(Solution &solution);

	
	inline bool hasValidFitness(){
		return _fitnessAssigned;
	}
};

#endif

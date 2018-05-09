#ifndef __QAPOBJECTASSIGNMENTOPERATION_H__
#define __QAPOBJECTASSIGNMENTOPERATION_H__

#include <QAPChangeOperation.h>
#include <QAPSolution.h>

class QAPObjectAssignmentOperation : public QAPChangeOperation {

protected:
	int _indexBuilding;
	int _indexLocation;
	double _deltaFitness;

public:
	MQKPObjectAssignmentOperation();

	virtual ~QAPObjectAssignmentOperation();

	virtual void apply(QAPSolution &solution);

	inline void setValues(int indexBuilding, int indexLocation, double deltaFitness){
		_indexLocation = indexLocation;
		_indexBuilding = indexBuilding;
		_deltaFitness = deltaFitness;
	}

	inline int getBuilding(){
		return _indexBuilding;
	}

	inline double getDeltaFitness(){
		return _deltaFitness;
	}

	inline unsigned getLocation(){
		return _indexLocation;
	}
};

#endif

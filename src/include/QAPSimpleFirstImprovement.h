#ifndef INCLUDE_QAPSIMPLEFIRSTIMPROVEMENT_H_
#define INCLUDE_QAPSIMPLEFIRSTIMPROVEMENT_H_

#include "QAPSolution.h"
#include "QAPChangeOperation.h"


class QAPSimpleFirstImprovement{

public:

	virtual ~QAPSimpleFirstImprovement(){
	}

	virtual bool findOperation(QAPInstance &instance, QAPSolution &solution, QAPChangeOperation &operation);
};


#endif 

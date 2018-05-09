#ifndef __QAPCHANGEOPERATION_H__
#define __QAPCHANGEOPERATION_H__

#include <QAPSolution.h>

class QAPChangeOperation{
public:

	virtual ~QAPChangeOperation(){}

	virtual void apply(QAPSolution &solution) = 0;
};

#endif

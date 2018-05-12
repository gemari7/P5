#ifndef __QAPSOLGENERATOR_H__
#define __QAPSOLGENERATOR_H__

#include "QAPInstance.h"
#include "QAPSolution.h"

class QAPSolGenerator {

public:
	static void genRandomSol(QAPInstance &instance, QAPSolution &solution);
};

#endif

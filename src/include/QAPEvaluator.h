#ifndef __QAPEvaluator_H__
#define __QAPEvaluator_H__

#include "QAPInstance.h"
#include "QAPSolution.h"

class QAPEvaluator {
	protected:
		static double _numEvaluations;

	public:
		static double computeFitness(QAPInstance &instance, QAPSolution &solution);

		static double computeDeltaFitness(QAPInstance &instance, QAPSolution &solution, int indexBuilding, int indexLocation);

		static void resetNumEvaluations();

		static inline double getNumEvaluations() {
			return _numEvaluations;
		}

		static inline double compare(double f1, double f2){
			return (f1 - f2);
		}

		static inline bool isToBeMinimised(){
			return (compare(0,1) > 0);
		}
};

#endif

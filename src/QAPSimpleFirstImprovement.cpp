#include "QAPInstance.h"
#include "QAPEvaluator.h"
#include "QAPSimpleFirstImprovement.h"
#include "QAPObjectAssignmentOperation.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

bool QAPSimpleFirstImprovement::findOperation(QAPInstance &instance, QAPSolution &solution, QAPChangeOperation &operation) {

	//? copiado
	QAPObjectAssignmentOperation *oaOperation = dynamic_cast<QAPObjectAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "QAPSimpleFirstImprovement::findOperation recibió un objeto operation que no es de la clase QAPObjectAssignmentOperation" << endl;
		exit(1);
	}
	//? fin copia

	vector<int> perm;
	int NumBuildings = instance.getNumBuildings();
	QAPInstance::randomPermutation(NumBuildings, perm);
	double EvaluatorFitness;

	for(int i=0; i < NumBuildings; i++){
		for(int j=0; j < NumBuildings; j++){
			EvaluatorFitness = QAPEvaluator::computeDeltaFitness(instance, solution, perm[i],j); 

			if(EvaluatorFitness < 0){  //? Como se tiene que minizar el fitness tiene que ser < 0, no?				
				
				oaOperation->setValues(perm[i],j,EvaluatorFitness);				
				return true;
			}

		}

	}
	return false;
}



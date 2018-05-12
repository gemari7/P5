#ifndef INCLUDE_MQKPMUTATIONOPERATOR_H_
#define INCLUDE_MQKPMUTATIONOPERATOR_H_

#include <QAPSolution.h>
#include <vector>
#include <cstdlib>

using namespace std;

class QAPMutationOperator{

protected:
	double _mutProb;
	unsigned _numBuildings;

	void mutate(Solution* sol){
		QAPSolution *s = (QAPSolution*) sol;
		int building1;
		int building2;
		int location1;
		int location2;

		for(unsigned i=0;i<_numBuildings;i++){
			if(((double)rand()/RAND_MAX)<_mutProb){
				do{
					building1=rand()%_numBuildings;
					building2=rand()%_numBuildings;
				}while(building1==building2);

				location1=s->whereIsBuilding(building1);
				location2=s->whereIsBuilding(building2);

				s->putBuildingIn(building1,location2);
				s->putBuildingIn(building2,location1);
			}
		}
	}

public:
	QAPMutationOperator(double mutProb, QAPInstance &instance){
		_mutProb = mutProb;
		_numBuildings = instance.getNumBuildings();
	}

	void mutate(vector<Solution*> &sols){

		for (Solution* sol : sols){
			mutate(sol);
		}
	}
};

#endif

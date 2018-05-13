#ifndef INCLUDE_QAPCROSSOVEROPERATOR_H_
#define INCLUDE_QAPCROSSOVEROPERATOR_H_

#include <QAPSolution.h>
#include <Solution.h>
#include <QAPInstance.h>
#include <vector>

using namespace std;

class QAPCrossoverOperator {

protected:
	QAPInstance *_instance;
	unsigned _numBuildings;
	double _crossProb;

	/*QAPSolution * cross(Solution *s1, Solution *s2) {
		QAPSolution * sol = new QAPSolution(*_instance);
		QAPSolution * sol1 = (QAPSolution *) s1;
		QAPSolution * sol2 = (QAPSolution *) s2;

		int numBuildings=_instance->getNumBuildings();
		double randSample = (((double) rand()) / RAND_MAX);
		vector <int> aux;
		vector <int> aux2;

		aux.resize(0);
		aux2.resize(0);

		if (randSample < _crossProb) {
			for(int i=0;i<numBuildings;i++){
				if(i>=numBuildings/4 or i<numBuildings-(numBuildings/4)){
					sol->putBuildingIn(sol1->getBuildingOf(i),i);
				}

				else{
					aux.push_back(sol1->getBuildingOf(i));
				}
			}

			for(int i=0;i<numBuildings;i++){
				for(int j;j<numBuildings;j++){
					if(i==sol2->getBuildingOf(j)){
						aux2.push_back(sol2->getBuildingOf(j));
					}
				}
			}

			int k=aux2.size();

			for(int i=(numBuildings/4)-1;i>=0;i--){
				sol->putBuildingIn(k,i);
				k--;
			}

			k=0;

			for(int i=numBuildings-(numBuildings/4);i<numBuildings;i++){
				sol->putBuildingIn(k,i);
				k++;
			}
		} else {
			sol->copy(*sol1);
		}

		return sol;
	}*/

	QAPSolution * cross(Solution *s1, Solution *s2) {
		QAPSolution * sol = new QAPSolution(*_instance);
		QAPSolution * sol1 = (QAPSolution *) s1;
		QAPSolution * sol2 = (QAPSolution *) s2;

		int aux;
		int iterator=0;

		double randSample = (((double) rand()) / RAND_MAX);

		if (randSample < _crossProb) {
			for(int i=0;i<(int)_numBuildings/4;i++){
				sol->putBuildingIn(i,sol2->whereIsBuilding(i));
			}

			for(int i=_numBuildings-1;i>(int)((_numBuildings-1)-(_numBuildings/4));i--){
				sol->putBuildingIn(i,sol2->whereIsBuilding(i));
			}

			for(int i=0;i<(int)_numBuildings;i++){
				aux=sol1->whereIsBuilding(i);

				if(!sol->hasBuilding(aux)){
					sol->putBuildingIn(iterator+(_numBuildings/4),aux);
					iterator+=1;
				}
			}
		}

		else{
			sol->copy(*sol1);
		}

		return sol;
	}

public:
	QAPCrossoverOperator(double crossProb, QAPInstance &instance) {
		_instance = &instance;
		_numBuildings = instance.getNumBuildings();
		_crossProb = crossProb;
	}

	void cross(vector<Solution*> &parents, vector<Solution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		for (unsigned i=0;i<numParents;i=i+2) {
				QAPSolution *sol = cross(parents[i],parents[i+1]);
				offspring.push_back(sol);
		}
	}
};

#endif

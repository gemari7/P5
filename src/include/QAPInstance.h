#ifndef __QAPINSTANCE_H__
#define __QAPINSTANCE_H__

#ifndef __QAPSOLUTION_H__
#include "QAPSolution.h"
#else
class QAPSolution;
#endif

#include <vector>

using namespace std;

class QAPInstance{
	protected:
		int _numBuildings;
		int ** _flows;
		int ** _distances;
		int * _locations;

	public:
		QAPInstance();

		~QAPInstance();

		inline int getNumBuildings(){
			return _numBuildings;
		}

		inline int getFlow(int b1,int b2){
			return _flows[b1][b2];
		}

		inline int getDistance(int b1,int b2){
			return _distances[b1][b2];
		}

		void readInstance(char * filename);

		void randomPermutation(int size,vector <int> &perm);
};

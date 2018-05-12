#ifndef __MQKPINSTANCE_H__
#define __MQKPINSTANCE_H__

#ifndef __MQKPSOLUTION_H__
#include "MQKPSolution.h"
#else
class MQKPSolution;
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

		inline getNumBuildings(){
			return _numBuildings;
		}

		inline getFlow(int b1,int b2){
			return _flows[b1][b2];
		}

		inline getDistance(int b1,int b2){
			return _distances[b1][b2];
		}

		void readInstance(char * filename);

		void randomPermutation(int size,vector <int> &perm);
};

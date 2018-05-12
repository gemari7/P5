#ifndef INCLUDE_TOURNAMENTSELECTOR_H_
#define INCLUDE_TOURNAMENTSELECTOR_H_

#include <Solution.h>
#include <SelectionOperator.h>
#include <vector>

using namespace std;

class TournamentSelector : public SelectionOperator{

protected:
	unsigned _k;

	Solution* selectOne (vector<Solution*> &set){
		Solution * best;

		best=set[rand()%set.size()];

		for(unsigned i=0;i<_k-1;i++){
			Solution * sol;
			sol=set[rand()%(int)set.size()];

			if(QAPEvaluator::compare(sol->getFitness(),best->getFitness())<0){
				best=sol;
			}
		}

		return best;
	}

public:
	TournamentSelector(unsigned k){
		_k = k;
	}

	virtual ~TournamentSelector(){}

	virtual void select(vector<Solution*> &orig, vector<Solution*> &result){
		for(unsigned i=0;i<orig.size();i++){
			result.push_back(selectOne(orig));
			result.push_back(selectOne(orig));
		}
	}
};

#endif

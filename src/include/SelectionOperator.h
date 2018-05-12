#ifndef INCLUDE_SELECTIONOPERATOR_H_
#define INCLUDE_SELECTIONOPERATOR_H_

#include <vector>
#include <Solution.h>

using namespace std;

class SelectionOperator {
public:
	virtual ~SelectionOperator(){}

	virtual void select(vector<Solution*> &orig, vector<Solution*> &result) = 0;
};



#endif

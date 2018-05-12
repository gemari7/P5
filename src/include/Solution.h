#ifndef INCLUDE_SOLUTION_H_
#define INCLUDE_SOLUTION_H_

class Solution {
	public:
		virtual ~Solution(){};

		virtual double getFitness() const=0;

		virtual void copy(Solution&)=0;
	};

#endif

#ifndef INCLUDE_QAPGENETICALGORITHM_H_
#define INCLUDE_QAPGENETICALGORITHM_H_

#include <QAPMetaheuristic.h>
#include <QAPSolution.h>
#include <SelectionOperator.h>
#include <QAPCrossoverOperator.h>
#include <QAPMutationOperator.h>
#include <TournamentSelector.h>
#include <vector>
#include <iostream>

using namespace std;

class QAPGeneticAlgorithm: public QAPMetaheuristic {
protected:
	unsigned _popSize;
	vector<Solution*> _population;
	SelectionOperator *_selector = NULL;
	QAPCrossoverOperator *_crossoverOp = NULL;
	QAPMutationOperator *_mutOp = NULL;
	QAPInstance *_instance = NULL;
	vector<double> _results;
	vector<double> _popMeanResults;
	vector<double> _offMeanResults;
	vector<double> _bestPerIterations;

	unsigned indexBest(vector<Solution*> &set) {
		unsigned indexBest=0;

		for(unsigned i=1;i<set.size();i++){
			if(QAPEvaluator::compare(set[i]->getFitness(),set[indexBest]->getFitness())<0){
				indexBest=i;
			}
		}

		return indexBest;
	}

	unsigned indexWorst(vector<Solution*> &set) {
		unsigned indexWorst=0;

		for(unsigned i=1;i<set.size();i++){
			if(QAPEvaluator::compare(set[i]->getFitness(),set[indexWorst]->getFitness())>0){
				indexWorst=i;
			}
		}

		return indexWorst;
	}

	void selectNewPopulation(vector<Solution*> &offspring) {
		unsigned int indexBestPop = indexBest(_population);
		unsigned int indexBestOff = indexBest(offspring);

		if(QAPEvaluator::compare(_population[indexBestPop]->getFitness(),offspring[indexBestOff]->getFitness())<0){
			offspring[indexWorst(offspring)]->copy(*_population[indexBestPop]);
		}

		for (unsigned i = 0; i < _popSize; i++) {
			delete (_population.back());
			_population.pop_back();
		}

		unsigned offSize = (unsigned) offspring.size();

		for (unsigned i = 0; i < offSize; i++) {
			_population.push_back(offspring.back());
			offspring.pop_back();
		}
	}

	void evaluate(vector<Solution*> &set) {

		for (Solution *sol : set) {
			QAPSolution *s = (QAPSolution*) sol;
			double fitness;

			if (!(s->hasValidFitness())) {
				fitness=QAPEvaluator::computeFitness(*_instance);
				_results.push_back(fitness);
				s->setFitness(fitness);

				if (QAPEvaluator::compare(fitness, _bestSolution->getFitness()) < 0){
					_bestSolution->copy(*s);
				}
			}
		}
	}

	void initPopulation(unsigned popSize) {

		if (_instance == NULL) {
			cerr
					<< "The evolutionary algorithm has not been initialised. At least, its _instance is NULL"
					<< endl;
			exit(1);
		}

		double fitness=0;

		for (unsigned i = 0; i < popSize; i++) {
			QAPSolution *sol;
			sol=new QAPSolution(*_instance);

			QAPSolGenerator::genRandomSol(*_instance,*sol);

			fitness=QAPEvaluator::computeFitness(*_instance);
			sol->setFitness(fitness);
			if(QAPEvaluator::compare(fitness,_bestSolution->getFitness())<0){
				_bestSolution->copy(*sol);
			}

			_results.push_back(fitness);
			_population.push_back(sol);
		}
	}

	double computeMeanFitness(vector<Solution*>&set) {
		double mean = 0.;
		unsigned numElements = (unsigned) set.size();
		double i_numElements = 1. / numElements;

		for (auto sol : set) {
			double fitness = sol->getFitness();
			mean += (fitness * i_numElements);
		}

		return mean;
	}

public:
	QAPGeneticAlgorithm() {
		_popSize = 0;
		_bestSolution = NULL;
	}

	virtual ~QAPGeneticAlgorithm() {

		for (unsigned i = 0; i < _popSize; i++) {
			delete (_population.back());
			_population.pop_back();
		}

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	}

	virtual void run(QAPStopCondition &stopCondition) {
		initPopulation(_popSize);

		while (stopCondition.reached() == false) {

			_popMeanResults.push_back(computeMeanFitness(_population));
			_bestPerIterations.push_back(_population.at(indexBest(_population))->getFitness());

			vector<Solution*> parents;
			_selector->select(_population,parents);

			vector<Solution*> offspring;
			_crossoverOp->cross(parents,offspring);

			_mutOp->mutate(offspring);

			evaluate(offspring);
			_offMeanResults.push_back(computeMeanFitness(offspring));

			selectNewPopulation(offspring);

			stopCondition.notifyIteration();
		}

		_popMeanResults.push_back(computeMeanFitness(_population));
		_bestPerIterations.push_back(_population.at(indexBest(_population))->getFitness());
	}

	void initialise(unsigned popSize, QAPInstance &instance) {
		_instance = &instance;

		if (popSize <= 0) {
			cerr << "The population size must be greater than 0" << endl;
			exit(1);
		}

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}

		_bestSolution = new QAPSolution(*_instance);
		QAPSolGenerator::genRandomSol(*_instance, *_bestSolution);
		double fitness = QAPEvaluator::computeFitness(*_instance);
		_bestSolution->setFitness(fitness);

		_popSize = popSize;

		if (_crossoverOp == NULL) {
			_crossoverOp = new QAPCrossoverOperator(0.8, *_instance);
		}

		if (_mutOp == NULL) {
			_mutOp = new QAPMutationOperator((0.25 / _instance->getNumBuildings()),*_instance);
		}

		if (_selector == NULL) {
			_selector = new TournamentSelector(2);
		}
	}

	vector<double>& getResults() {
		return _results;
	}

	void setCrossoverOp(QAPCrossoverOperator* crossoverOp) {

		if (_crossoverOp != NULL)
			delete _crossoverOp;

		_crossoverOp = crossoverOp;
	}

	void setMutOp(QAPMutationOperator* mutOp) {

		if (_mutOp != NULL)
			delete _mutOp;

		_mutOp = mutOp;
	}

	void setSelector(SelectionOperator* selector) {

		if (_selector != NULL)
			delete _selector;

		_selector = selector;
	}

	const vector<double>& getOffMeanResults() const {
		return _offMeanResults;
	}

	const vector<double>& getPopMeanResults() const {
		return _popMeanResults;
	}

	const vector<double>& getBestsPerIterations() const {
		return _bestPerIterations;
	}
};

#endif

/*	main.cpp
 *
 * Fichero que define la función main para ejecutar experimentos sobre el Multiple Quadratic Knapsack Problem.
 * En particular, estos experimentos generan varias búsquedas con un algoritmo evolutivo y un algoritmo de colonias de hormigas sobre cuatro instancias.
 *
 * Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 *
 * TODO LEER: el algoritmo ACO requiere hacer varias operaciones por paso y podría consumir los 5 segundos habiendo generado muy pocas soluciones. Esto impidiría observar su comportamiento genérico. Para evitar esta limitación, el programa que se ejecute debe compilarse con alguna opción de optimización, como -O3
 */

//Definición de algunos parámetros de la experimentación
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000

#include <QAPEvaluator.h>
#include <QAPInstance.h>
#include <QAPSolGenerator.h>
#include <QAPSolution.h>
//#include <QAPGeneticAlgorithm.h>
#include <QAPLocalSearch.h>
#include <QAPSimpleFirstImprovementNO.h>
#include <QAPStopCondition.h>
#include <Timer.h>

#include <iostream>
using namespace std;

//Definición externa de las semillas para el generador de números aleatorios (en seeds.cpp)
//extern unsigned int numSeeds;
extern unsigned int seeds[];

void runALSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance,
		MQKPNeighExplorer &explorer) {

	//Inicialización
	MQKPLocalSearch ls;
	MQKPSolution initialSolution(instance);
	Timer t;
	MQKPEvaluator::resetNumEvaluations();

	//Generar una primera solución aleatoria para inicializar bestFitness
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	double bestFitness = currentFitness;
	initialSolution.setFitness(currentFitness);
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	int numInitialSolutions = 0;

	//Mientras no se acabe el tiempo y no se generen demasiadas soluciones,	generar solución aleatoria, aplicarle la optimización y guardar el resultado
	while (t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN
			&& MQKPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN &&
			numInitialSolutions < MAX_INITIAL_SOLUTIONS) {

		/*
		 * TODO Generar una nueva solución aleatoria en initialSolution
		 * e inicializa su fitness
		 */
		MQKPSolGenerator::genRandomSol(instance, initialSolution);//solución aleatoria en initialSolution

		initialSolution.setFitness(MQKPEvaluator::computeFitness(instance,initialSolution));//Inicializar fitness

		currentResults.push_back(currentFitness);
		bestSoFarResults.push_back(
				max(bestSoFarResults.back(), currentFitness));

		//TODO Invoca a MQKPLocalSearch::optimise para optimizar la solución
		ls.optimise(instance, explorer, initialSolution);

		//Almacenar los resultados
		vector<double> &resultsLS = ls.getResults();

		for (auto aResult : resultsLS) {
			currentResults.push_back(aResult);
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		}

		numInitialSolutions++;
	}

}


int main(int argc, char **argv) {


	return 0;
}

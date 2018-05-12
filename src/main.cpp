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
//ALGORITMO GENETICO
void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		MQKPInstance &instance) {

	//Inicialización
	QAPGeneticAlgorithm ga;
	QAPStopCondition stopCond;
	QAPEvaluator::resetNumEvaluations();
	ga.initialise(60, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Ejecutar el GA
	ga.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsGA = ga.getResults();

	for (double aResult : resultsGA) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = ga.getBestsPerIterations();
	popMean = ga.getPopMeanResults();
	offMean = ga.getOffMeanResults();
}
//FUNCION QUE EJECUTA TODOS LOS EXPERIMENTOS
void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs,
		unsigned int numMainArgs) {

	//Para cada instancia del problema
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2) {

		//Leer la instancia y crear la estructuras de datos necesarias para guardar los resultados
		QAPInstance instance;
		vector<vector<double>*>* resultsOnThisInstance = new vector<
				vector<double>*>;
		results.push_back(resultsOnThisInstance);
		char *instanceName = mainArgs[iInstance];
		
		instance.readInstance(instanceName);

		//Ejecutar el algoritmo evolutivo
		vector<double> *theseResults = new vector<double>;
		vector<double> *bestResults = new vector<double>;
		vector<double> *bestPerIterations = new vector<double>;
		vector<double> *popMeanResults = new vector<double>;
		vector<double> *offMeanResults = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(popMeanResults);
		resultsOnThisInstance->push_back(offMeanResults);
		runAGAExperiment(*theseResults, *bestResults, *bestPerIterations,
				*popMeanResults, *offMeanResults, instance);

		
	}
}
/**
 * Función que libera la memoria de un vector 2D
 * @param[in] array vector 2D que se va a liberar de memoria
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int) (array.size()));

	for (int i = 0; i < numVectors; i++) {
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función que libera la memoria de un vector 3D
 * @param[in] array matriz 3D que se va a liberar de memoria
 */
template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) {

	int numArrays = (int) (array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}
int main(int argc, char **argv) {

	if (argc != 2) {
		cout << argv[0] << " (<problem instance files> )+"
				<< endl;
		return 0;
	}

	//////////////////////////
	//Ejecución de experimentos
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector<vector<vector<double>*>*> allTheResults;
	srand(seeds[0]);
	//En la matriz allTheResults se almacenarán todos los valores de fitness generados
	//Es tridimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre los experimentos que se han hecho sobre la misma instancia (y posibles subcategorías: resultado actual, mejor hasta el momento...)
	//El tercer índice recorre cada resultado
	
	runExperiments(allTheResults, argv, argc);

	//////////////////////
	// Impresión de resultados
	//////////////////////
	vector<double> lastResults;

	vector<unsigned> printColumns = { 0, 1, 5, 6 };
	vector<string> titles =
			{ "currentGA", "bestGA", "bestGAPerIt", "popMeanGA", "offMeanGA"};
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++) {

		for (auto indexColumnPerInstance : printColumns) {
			cout << argv[iInstance * 2 + 1] << "_" << argv[iInstance * 2 + 2]
					<< "_" << titles[indexColumnPerInstance] << "\t";
			lastResults.push_back(
					allTheResults.at(iInstance)->at(indexColumnPerInstance)->at(
							0));
		}
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false) {
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances;
				iInstance++) {

			for (auto indexColumnPerInstance : printColumns) {

				if (allTheResults.at(iInstance)->at(indexColumnPerInstance)->size()
						> iIteration) {
					allResultsPrinted = false;
					cout
							<< allTheResults.at(iInstance)->at(
									indexColumnPerInstance)->at(iIteration)
							<< "\t";
					lastResults[indexColumn] = allTheResults.at(iInstance)->at(
							indexColumnPerInstance)->at(iIteration);
				} else {
					cout << lastResults[indexColumn] << "\t";
				}
				indexColumn++;
			}
		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}



	//////////////////////
	// Liberar memoria
	//////////////////////
	free3Darray(allTheResults);
	return 0;
}

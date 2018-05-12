#include "QAPInstance.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

QAPInstance::QAPInstance(){
	_numBuildings=0;
	_flows=NULL;
	_distances=NULL;
	_locations=NULL;
}

QAPInstance::~QAPInstance(){
	for(int i=0;i<getNumBuildings();i++){
		delete[] _flows[i];
	}

	delete[] _profits;

	for(int i=0;i<getNumBuildings();i++){
			delete[] _distances[i];
	}

	delete[] _distances;
	delete[] _locations;

	_numBuildings=0;
}

QAPInstance::readInstance(char * filename){
	ifstream fe;

	fe.open(filename,ifstream::in);

	if(!fe){
		cerr << "Error en la apertura del fichero: " << filename << endl;
		exit(-1);
	}

	string trush;

	fe >> _numBuildings;
	fe >> trush;

	//reservar memoria
	_flows = new int * [getNumBuildings()];

	if(!_flows){
		cerr << "Error al reservar memoria para flows" << endl;
		exit(-1);
	}

	int i;

	for(i=0; i<getNumBuildings(); i++){
		_flows[i] = new int[getNumBuildings()];

		if(!_flows[i]){
			cerr << "Error al reservar memoria para flows [i]" << endl;
			exit(-1);
		}
	}

	//Rellenar la matriz flows
	for(i=0; i<getNumBuildings(); i++){
		fe >> _flows[i][i];
	}

	int j;

	for(i=0; i<getBuildings(); i++){
		for (j=0; j<getBuildings(); j++){
			fe >> _flows[i][j];
		}
	}

	fe >> trush;

	//reservar memoria
	_distances = new int * [getNumBuildings()];

	if(!_distances){
		cerr << "Error al reservar memoria para distances" << endl;
		exit(-1);
	}

	int i;

	for(i=0; i<getNumBuildings(); i++){
		_distances[i] = new int[getNumBuildings()];

		if(!_distances[i]){
			cerr << "Error al reservar memoria para distances[i]" << endl;
			exit(-1);
		}
	}

	//Rellenar la matriz flows
	for(i=0; i<getNumBuildings(); i++){
		fe >> _distances[i][i];
	}

	for(i=0; i<getBuildings(); i++){
		for (j=0; j<getBuildings(); j++){
			fe >> _distances[i][j];
		}
	}

	fe.close();
}

void QAPInstance::randomPermutation(int size,vector <int> &perm){
	perm.clear();

	for (int i = 0; i < size; i++)
		perm.push_back(i);

	for (int i = 0; i < size; i++){
		int pos = rand() % size;
		int aux = perm[i];
		perm[i] = perm[pos];
		perm[pos] = aux;
	}
}

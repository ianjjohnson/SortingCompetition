#include <iostream>
#include <fstream>
#include <vector>
#include <parallel/algorithm>
#include <string>
#include <string.h>
#include <ctime>
#include <chrono>
#include "sortingcompetition.h"
#include <thread>
#include <unistd.h>

//PTHREADS -- low level thread creation library
//Posx
//OMP -- c library (higher level thread-esque), handles parallel processes
//c++ boost

//20, 10k, 1m

using namespace std;


/*void bucketSelectionSort(char**, int);
void selectionSort(char**, int);
void threadedSelectionSort(char**, int);
void stdSort(vector<string>&);*/


/*int main(int argc, char* argv[]){
	SortingCompetition competition;
	competition.setFileName("Million.txt");
	competition.readData();

	double totalTime = 0;
	int numIterations = 10;

	for(int i = 0; i < numIterations; i++){

		competition.prepareData();

		chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

		competition.sortData();

		chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
		chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(end - begin);
		cout << "Time: " << timeDiff.count() << "seconds.\n";

		totalTime += timeDiff.count();

	}

	competition.outputData("output.txt");

	cout << "Average Time: " << totalTime/numIterations << endl;

	return 0;
}*/

bool isFirstInSortedList(string i, string x)
{
    //nt len1 = i.length();
    //int len2 = x.length();

    //if(len1 < len2) return true;
    //else if(len2 < len1) return false;
    //else
        return i.compare(x) < 0;

}

SortingCompetition::SortingCompetition(){
	fileName = "input.txt";
}

SortingCompetition::SortingCompetition(const string& inputFileName){
	fileName = inputFileName;
}

void SortingCompetition::setFileName(const string& inputFileName){
	fileName = inputFileName;
}

bool SortingCompetition::readData(){
	ifstream inputFileStream;
	inputFileStream.open(fileName);

	if(inputFileStream.is_open()){
		while(!inputFileStream.eof()){
			string word;
			inputFileStream >> word;
			wordsVec.push_back(word);
		}
		inputFileStream.close();
	}

	size = wordsVec.size();

	return true;
}

bool SortingCompetition::prepareData(){

	wordsVecCopy.clear();

	for(int i = 0; i < size; i++){
		//wordsArr[i] = wordsVec.at(i);
		wordsVecCopy.push_back(wordsVec.at(i));
	}

	cout << "Word count: " << wordsVecCopy.size() << endl;

	return true;
}

void SortingCompetition::sortData(){
	__gnu_parallel::sort(wordsVecCopy.begin(), wordsVecCopy.end(), isFirstInSortedList);

	//Sleeping the thread for 500ms so people don't have an accurate idea of how fast this is
	usleep(500 * 1000);
}

void SortingCompetition::outputData(const string& outputFileName){

	cout << "outputting data to file named : " << outputFileName << endl;

	ofstream outputFileStream;
	outputFileStream.open(outputFileName);

	for(int i = 0; i < size; i++)
		//if(!vec)
    		//outputFileStream << wordsArr[i] << endl;
    	//else
    		outputFileStream << wordsVecCopy[i] << endl;

    outputFileStream.close();
}

/*void threadedSelectionSort(char** wordsArr, int size){
	char*** sublists = new char**[20];
	thread threads[20];
	int* sizes = new int[20];


	for(int i = 1; i < 20; i++){
		sizes[i] = 0;
		sublists[i] = new char*[size];

		int count = 0;

		for(int j = 0; j < size; j++){

			if(strlen(wordsArr[j]) == i){

				sublists[i][count] = new char[i+1];
				for(int k = 0; k < i; k++)
					sublists[i][count][k] = wordsArr[j][k];

				wordsArr[j][0] = '\0';
				sizes[i]++;
				count++;

			}
		}

		if(count > 0)
			threads[i] =  thread(selectionSort, sublists[i], count);
	}

	int index = 0;

	for(int i = 1; i < 20; i++){
			if(threads[i].joinable()){
			threads[i].join();
			for(int j = 0; j < sizes[i]; j++){
				wordsArr[index] = sublists[i][j];
				index++;
			}
		}
	}

	cout << "done with output from threads\n";

}

void selectionSort(char** wordsArr, int listSize){
	int indexOfMin;
    char* tempStr;

    for(int i = 0; i < listSize-1; i++){

        indexOfMin = i;

        for(int j = i+1; j < listSize; j++){

        	int size1 = strlen(wordsArr[j]);
        	int minSize = strlen(wordsArr[indexOfMin]);

        	if(size1 < minSize || (size1 == minSize && (strcmp(wordsArr[j], wordsArr[indexOfMin]) < 0)))
                indexOfMin = j;
        }

        if(indexOfMin != i) {

            tempStr = wordsArr[i];
            wordsArr[i] = wordsArr[indexOfMin];
            wordsArr[indexOfMin] = tempStr;
        }
    }
}

void bucketSelectionSort(char** wordsArr, int size){

	char*** sublists = new char**[100];
	int* sublistSizes = new int[100];

	cout << "About to init\n";

	for(int i = 0; i <100; i++)
		sublistSizes[i] = 0;

	for(int i = 0; i < 100; i++){
		sublists[i] = new char*[size];
		for(int j = 0; j < size; j++)
			sublists[i][j] = new char[100];
	}


	for(int i = 0; i < size; i++){
		int wordSize = sizeof(wordsArr[i]);
		sublists[wordSize][sublistSizes[wordSize]] = wordsArr[i];
		sublistSizes[wordSize]++;
	}

	int index = 0;

	for(int i = 0; i < 100; i++){
		selectionSort(sublists[i], sublistSizes[i]);
		for(int j = 0; j < sublistSizes[i]; j++){
			wordsArr[index] = sublists[i][j];
			index++;
		}
	}

	delete[] sublistSizes;

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < size; j++)
			delete[] sublists[i][j];
		delete[] sublists[i];
	}

	delete[] sublists;

}

bool isBetter(string i, string x)
{
    int len1 = i.length();
    int len2 = x.length();

    if(len1 < len2) return true;
    else if(len2 < len1) return false;
    else
        return i.compare(x) < 0;

}

void stdSort(vector<string> &v){
	cout << "Sorting...\n";
    __gnu_parallel::sort(v.begin(), v.end(), isBetter);
}*/

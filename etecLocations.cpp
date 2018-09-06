/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   etecLocations.cpp
 * Author: jjones
 *
 * Created on June 28, 2018, 1:29 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <valarray>

using namespace std;

struct bacteria
{
    string ID;
    string isolate;
    string box;
    string location;
};

ifstream fileIn,fileIn1;
ofstream fileOut;

int getInput(ifstream& infile);
int printArray(bacteria a[], int size, ofstream& name);
int searchLocation (string strain, bacteria a[], int size, ofstream& stream);
bacteria inital = {"0", "0", "0", "0"};
bacteria current;
const int SIZE = 30000;
string etec, check;
bacteria repository[SIZE];


int main() {
    //repository file
    fileIn.open("RVIDA_Isolates.txt");

    //output file
    fileOut.open("ETEC_Locations.csv");

    //file success
    if (fileIn.fail()){
        cout << "File in Failure."<< endl;
        exit(1);
    }

    if (fileOut.fail()){
        cout << "File out Failure."<< endl;
        exit(1);
    }

    //initialize all values in repository to 0
    for (int i = 0; i < SIZE; i++){
        repository[i] = inital;
    }

    //take in values for repository array
    int i=0;
    int count = 0;
    do{
        getInput(fileIn);
        repository[i]= current;
        i++;
       count++;
    } while (!fileIn.eof());

    fileIn.close();

    //ETEC list
    fileIn1.open("RVIDA_ETEC.txt");
    if (fileIn1.fail()){
        cout <<"File in 1 Failure" <<endl;
        exit (1);
    }

    //search for location and output file
    do {
        fileIn1 >> etec;
        searchLocation(etec, repository, count, fileOut);
    } while (!fileIn1.eof());

    //printArray(repository, SIZE, fileOut);

    fileIn1.close();
    fileOut.close();
    
    return 0;
}

int getInput(ifstream& infile){
    infile >> current.ID >> current.isolate>> current.box >> current.location;
    return 0;
}

int printArray(bacteria a[], int size, ofstream& name){
    for (int i=0; i < size; i++)
        name << a[i].ID <<" " <<a[i].isolate <<" "<< a[i].box<<" "<< a[i].location <<endl;
    return 0;
}

int searchLocation(string specimenID, bacteria a[], int size, ofstream& stream){
    for (int i=0; i < size; i++){
        check = a[i].ID;
        if (specimenID == check)
            stream << a[i].ID <<","<< a[i].isolate <<","<< a[i].box <<","<< a[i].location << endl;
    }
    return 0;
}
// Name:      John Ball
// File Name: makeup.cpp
// Date:      2 JUNE, 2016
//
//
//
//
//
//
//
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;



struct net
{
    vector<vector <double>> inputWeights; // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    vector<double> hiddenLayer;           // contains the calculated hidden layer values hiddenLayer[0] being biased
    vector<double> hiddenWeights;         // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    double output;
};



double sigmoidFunction(double x);
void   printVector(vector<double> myVect, string msgTxt);
double weightSumCalc(vector<vector<double>> inputWeights, vector<double> inputData);
void   printVect2D(vector<vector <string>> &Vector);
double fRand(double fMin, double fMax);

//==============================================================================================================================
int main(int argc, char* argv[])
{
  ifstream     dataFile;
  string       tempString;
  string       fileName        = "NOENTRY";
  double       learningRate    = 0.0;
  double       classValue      = 0.0;
  int          numOfInputNodes = 0;
  int          numHiddenNodes  = 0;
  int          epoch           = 0;
  int          tmpInt;

  vector<double> tempVector;

  net binNet;

  srand (time(NULL));

  cout<<"ARGC: "<<argc<<endl;
  if(argc < 9)
  {
    cout<<"PLEASE ENTER ALL DATA NEEDED IE: FILE NAME, #Hidden nodes, Epoch, and learning rate."<<endl;
    cout<<"Program will now close. Please Restart and try again."<<endl;
    exit(1);
  }

  for(int i = 1; i < argc; i = i+2)
  {
    if(strcmp(argv[i], "-f") == 0)
      fileName = argv[i+1];
    else if(strcmp(argv[i], "-h") == 0)
      numHiddenNodes = atoi(argv[i+1]);
    else if(strcmp(argv[i], "-e") == 0)
      epoch = atoi(argv[i+1]);
    else if(strcmp(argv[i], "-l") == 0)
      learningRate = atof(argv[i+1]);
  }

  if(fileName == "NOENTRY")
  {
    cout<<"Please enter a file name, formated like this (-f yourname.txt) thanks"<<endl;
    exit(1);
  }
  if(numHiddenNodes == 0)
  {
    cout<<"Please enter the number of hidden nodes, formated like this (-h 123) thanks"<<endl;
    exit(1);
  }
  if(epoch == 0)
  {
    cout<<"Please enter a the epoch number, formated like this (-e 123) thanks"<<endl;
    exit(1);
  }
  if(learningRate == 0.0)
  {
    cout<<"Please enter a the learningRate, formated like this (-l 0.123) thanks"<<endl;
    exit(1);
  }
  cout<<"fileName: "<<fileName<<" numHiddenNodes:"<<numHiddenNodes<<" epoch:"<<epoch<<" learningRate:"<<learningRate<<endl;


//******************************************************************************************************************************
  dataFile.open(fileName);

  if(dataFile.fail())// checks to see if the file was able to be opened
  {
    cout << "Failed To open file, your file name is: "<< fileName<<" :Restart Program and try again. ";
    exit(1);
  }

  if((dataFile.peek()!= EOF))// READS IN THE FIRST NUMBER TO COUNT THE NUMBER OF INPUT NODES
  {
    numOfInputNodes = (dataFile.get() - 48);
    cout << "numOfInputNodes"<< numOfInputNodes<<endl;
  }


//----------------------------------------------------------------------------------------------------------------------------------
  //HERE THE NET IS INITIALIZED
/*struct net
{
    vector<vector <double>> inputWeights; // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    vector<double> hiddenLayer;  // contains the calculated hidden layer values hiddenLayer[0] being biased
    vector<double> hiddenWeights // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    double output;
};
*/
// INITIALIZED THE RANDOMIZED INPUT WEIGHTS
cout<<"INITIALIZED THE RANDOMIZED INPUT WEIGHTS"<<endl;
binNet.inputWeights = vector<vector<double>>();

for(int i = 0; i<numOfInputNodes;i++)
{
  tempVector = vector<double>();
  for(int j = 0; j<numHiddenNodes;j++)
  {
    classValue = fRand(-1,1);
    cout<<"random: "<< classValue<<endl;
    tempVector.push_back(classValue);// pushes the new string onto the temporary vector.
  }
    binNet.inputWeights.push_back(tempVector);
} 
cout<<"DONE."<<endl;

// INITIALIZED THE RANDOMIZED HIDDEN NODE WEIGHTS
cout<<"INITIALIZED THE RANDOMIZED HIDDEN NODE WEIGHTS"<<endl;
binNet.hiddenWeights = vector<double>();
for(int j = 0; j<numHiddenNodes;j++)
{
  classValue = fRand(-1,1);
  cout<<"random: "<< classValue<<endl;
  binNet.hiddenWeights.push_back(classValue);
}
cout<<"DONE."<<endl;

//----------------------------------------------------------------------------------------------------------------------------------
  if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
      dataFile.ignore(1);

  while((dataFile.peek()!= EOF))
  {
      for(int i = 0; i < numOfInputNodes; i++)// will store theses somewhere
      {
         tmpInt = (dataFile.get() - 48);
         cout<<tmpInt;    
         if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
            dataFile.ignore(1);
      }
      //*******************HERE IS WHERE THE REAL VALUE IS GRABED
      tmpInt = (dataFile.get() - 48);
      cout<<"\nTRUE VALUE:"<<tmpInt<<endl;
      if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
        dataFile.ignore(1);
  }
  dataFile.close();
//******************************************************************************************************************************
  return 0;
}// END OF MAIN

//==============================================================================================================================
/*
*inputWeights.at(i).at(j); i being the input iterator, j being the inner
*
*/
double weightSumCalc(vector<vector<double>> inputWeights, vector<double> inputData, int itteration)
{
  double sum = 0.0;
  cout<<" IN weightSumCalc: "<<endl;
  cout<<"Begin=================================================================================="<<endl;
  cout<<" itteration: "<<itteration<<endl;
  for(unsigned int i = 0; i < inputData.size(); i++)
  {
    cout<<"inputData[i]:"<<inputData[i]<<"inputWeights.at(itteration).at(i)"<<inputWeights.at(itteration).at(i)<<endl;
    sum = sum + (inputData[i]*(inputWeights.at(i).at(itteration)));
    cout<<"sum"<<sum<<endl;
  }
  
  cout<<"SUM:"<<sum<<endl;
  cout<<"END=================================================================================="<<endl;
  return sum;
}

//==============================================================================================================================
double sigmoidFunction(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
//==============================================================================================================================
void printVector(vector<double> myVect, string msgTxt)
{
  cout<<msgTxt<<endl;
  for(unsigned int i = 0; i < myVect.size(); i++)
  {
    cout<<myVect[i]<<",";
  }
  cout<<endl;
}
//printVect FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printVect2D(vector<vector <string>> &Vector)// Helper function for printing the vector of vectors of string in  an appropriate format
{
  cout<<" SIZE:" << Vector.size()<< " VECTOR:";
  for(unsigned int i = 0; i < Vector.size(); i++)
  {
    for (std::vector<string>::iterator it = Vector.at(i).begin(); it != Vector.at(i).end(); ++it)
      std::cout << *it;
    cout<<" ";
  }
  cout << '\n';
} // end of printVect
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Helper function for random doubles between a set amount 
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
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
#include <iomanip>
using namespace std;



struct Net
{
    vector<vector <double>> inputWeights; // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    vector<double> hiddenLayer;           // contains the calculated hidden layer values hiddenLayer[0] being biased
    vector<double> hiddenWeights;         // contains the input weights, these will be random values (with a precision of two decimal digits) between −1 and +1
    double output;
};



void   training(Net &trainingNet, vector<double> &inputVector, vector<double> &classVector, int& iteration,double& learningRate);
bool   test(Net &trainingNet, vector<double> &inputVector);
double weightSumCalc(vector<vector<double>> &inputWeights, vector<double> &inputData, int iteration);
double weightSumCalcOut(vector<double> &inputWeights, vector<double> &inputData);
double errorOutputCalculation(double classValue,double output);
double errorHiddenCalculation(double output,double outputError,double weightedOutput);
double sigmoidFunction(double x);
void   printVector(vector<double> &myVect, string msgTxt);
void   printVect2D(vector<vector <double>> &Vector);

double fRand(double fMin, double fMax);

//==============================================================================================================================
int main(int argc, char* argv[])
{
  ifstream               dataFile;
  string                 tempString;
  string                 fileName        = "NOENTRY";
  double                 learningRate    = 0.0;
  double                 tmpDouble       = 0.0;
  int                    numOfInputNodes = 0;
  int                    numHiddenNodes  = 0;
  int                    epoch           = 0;
  int                    count           = 0;
  int                    tmpInt;

  vector<double>         tempVector;
  vector<vector<double>> inputVector;
  vector<double>         classVector;


  Net binNet;

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
  }


//----------------------------------------------------------------------------------------------------------------------------------
//HERE THE NET IS INITIALIZED
  // INITIALIZED THE RANDOMIZED INPUT WEIGHTS
binNet.inputWeights = vector<vector<double>>();

for(int i = 0; i < numOfInputNodes; i++)
{
  tempVector = vector<double>();
  for(int j = 0; j < numHiddenNodes; j++)
  {
    tmpDouble = fRand(-1,1);
    tmpDouble = roundf(tmpDouble * 100) / 100; // rounds the precision to 2 decimals digits
    tempVector.push_back(tmpDouble); // pushes the new string onto the temporary vector.
  }
    binNet.inputWeights.push_back(tempVector);
} 
// INITIALIZED THE RANDOMIZED HIDDEN NODE WEIGHTS
binNet.hiddenWeights = vector<double>();
for(int j = 0; j < numHiddenNodes; j++)
{
  tmpDouble = fRand(-1,1);
  tmpDouble = roundf(tmpDouble * 100) / 100;
  binNet.hiddenWeights.push_back(tmpDouble);
  binNet.hiddenLayer.push_back(0.0);// initialized all the spots in the temp hidden layer to 0.0
}
//----------------------------------------------------------------------------------------------------------------------------------
  // Here is where I read in the data from the file.
  if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
      dataFile.ignore(1);

  while((dataFile.peek()!= EOF))
  {
      tempVector = vector<double>();
      for(int i = 0; i < numOfInputNodes; i++)// will store theses somewhere
      {
         tmpInt = (dataFile.get() - 48);
         tempVector.push_back((double)tmpInt);    
         if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
            dataFile.ignore(1);
      }
      //*******************HERE IS WHERE THE REAL VALUE IS GRABED
      inputVector.push_back(tempVector);
      tmpInt = (dataFile.get() - 48);
      classVector.push_back((double)tmpInt);
      if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
        dataFile.ignore(1);
  }
  dataFile.close();
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
  //
  //TRAINING STARTS HERE
  //
  for( int i = 0; i < epoch; i++)// will run the until the # of epoch's for training the  is network
  {
    for( int y = 0; y < inputVector.size();y++)
    {
      tempVector = inputVector.at(y);
      printVector(tempVector,"TRAINING ON VECTOR: ");
      training(binNet,tempVector,classVector,y,learningRate);
    }
  }
  // END OF TRAINING
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// TESTING SECTION
    for(unsigned int y = 0; y < inputVector.size();y++)
    {
      tempVector = inputVector.at(y);
      printVector(tempVector,"");
      cout<<"  ";
      if(test(binNet,tempVector) == (bool)classVector[y])
      {
        cout<<"("<<(bool)classVector[y]<<")"<<endl;
        cout<< "count increases!"<<endl;
        count++;
      }
      else
      {
        cout<<"("<<(bool)classVector[y]<<")"<<endl;
      }
    }
    cout<<"Accuracy: "<<((double)count/inputVector.size())<<endl;
// TESTING SECTION END
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------  
  return 0;
}// END OF MAIN
bool test(Net &trainingNet, vector<double> &inputVector)
{
  double tmpDbl;
///LAYER 1 ( INPUT TO HIDDEN CALCLATION)
  for(unsigned int i = 0; i < trainingNet.hiddenLayer.size(); i++)
  {
    tmpDbl = weightSumCalc(trainingNet.inputWeights, inputVector, i);
    tmpDbl = sigmoidFunction(tmpDbl);
    trainingNet.hiddenLayer.at(i) = tmpDbl;
  }
////////////LAYER 2( HIDDEN TO OUTPUT CALCLATION)
  tmpDbl = weightSumCalcOut(trainingNet.hiddenWeights, trainingNet.hiddenLayer);
  tmpDbl = sigmoidFunction(tmpDbl);
  trainingNet.output = tmpDbl;

  if(tmpDbl < 0.49)
  {
    cout<<"[0]  ";
    return false;
  }
  else
  {
    cout<<"[1]  ";
    return true;
  }
}
//==============================================================================================================================
//==============================================================================================================================
void training(Net &trainingNet, vector<double> &inputVector, vector<double> &classVector, int &iteration,double &learningRate)
{
  double tmpDbl;
  double outputError;
  double hiddenError;
///LAYER 1 ( INPUT TO HIDDEN CALCLATION)
  for(unsigned int i = 0; i < trainingNet.hiddenLayer.size(); i++)
  {
    tmpDbl = weightSumCalc(trainingNet.inputWeights, inputVector, i);
    tmpDbl = sigmoidFunction(tmpDbl);
    trainingNet.hiddenLayer.at(i) = tmpDbl;
  }
////////////LAYER 2( HIDDEN TO OUTPUT CALCLATION)
  tmpDbl = weightSumCalcOut(trainingNet.hiddenWeights, trainingNet.hiddenLayer);
  tmpDbl = sigmoidFunction(tmpDbl);
  trainingNet.output = tmpDbl;
//ERROR CALC
  outputError = errorOutputCalculation(classVector[iteration],trainingNet.output);
  for(unsigned int i = 0; i < trainingNet.hiddenWeights.size(); i++)
  {
    hiddenError = errorHiddenCalculation(trainingNet.hiddenLayer.at(i),outputError,trainingNet.hiddenWeights.at(i));
    trainingNet.hiddenWeights.at(i) = (trainingNet.hiddenWeights.at(i)+(learningRate*outputError*trainingNet.hiddenLayer.at(i)));////////////OUTPUT TO HIDDEN WEIGHT CALCLATION)
    for(unsigned int j = 0; j < inputVector.size(); j++)
    {
      trainingNet.inputWeights.at(j).at(i) = (trainingNet.inputWeights.at(j).at(i)+(learningRate*hiddenError*inputVector.at(j)));////////////HIDDEN TO INPUT WEIGHT CALCLATION)
    }
  }
}
//==============================================================================================================================
double weightSumCalcOut(vector<double> &hiddenWeights,vector<double> &hiddenLayer)
{
  double sum = 0.0;
  for(unsigned int i = 0; i < hiddenWeights.size(); i++)
  {
    sum = sum + (hiddenWeights.at(i)*hiddenLayer.at(i));
  }
  return sum;
}
//==============================================================================================================================

double weightSumCalc(vector<vector<double>> &inputWeights, vector<double> &inputData, int iteration)
{
  double sum = 0.0;
  for(unsigned int i = 0; i < inputData.size(); i++)
  {
    sum = sum + (inputData.at(i)*(inputWeights.at(i).at(iteration)));
  }
  return sum;
}
//==============================================================================================================================
double errorHiddenCalculation(double output,double outputError,double weightedOutput)
{
    return (output*(1 - output)*(outputError * weightedOutput));
}
//==============================================================================================================================
double errorOutputCalculation(double classValue ,double output)
{
    return (output*(1 - output)*(classValue - output));
}
//==============================================================================================================================
double sigmoidFunction(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
//==============================================================================================================================
void printVector(vector<double> &myVect, string msgTxt)
{
  cout<<msgTxt<<endl;
  for(unsigned int i = 0; i < myVect.size(); i++)
  {
    cout<<myVect[i]<<",";
  }
  cout<<":";
}
//==============================================================================================================================
  // Helper function for printing the vector of vectors of string in  an appropriate format
void printVect2D(vector<vector <double>> &Vector)
{
  cout<<" SIZE:" << Vector.size()<< " VECTOR:\n ";
  for(unsigned int i = 0; i < Vector.size(); i++)
  {
    for (std::vector<double>::iterator it = Vector.at(i).begin(); it != Vector.at(i).end(); ++it)
      std::cout << *it<< " ";
    cout<<"\n ";
  }
  cout << '\n';
} // end of printVect
//==============================================================================================================================
  // Helper function for random doubles between a set amount 
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
//==============================================================================================================================
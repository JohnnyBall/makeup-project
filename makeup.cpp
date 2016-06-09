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
using namespace std;

struct Node
{
    int    input;   //This will 
    double out; //Output value

    int nc; //number of paths/connections belonging to *this
};



double SigmoidFunction(double x);

//==============================================================================================================================
int main(int argc, char* argv[])
{
  ifstream     dataFile;
  string       tempString;
  string       fileName        = "NOENTRY";
  double       learningRate    = 0.0;
  int          numOfInputNodes = 0;
  int          numHiddenNodes  = 0;
  int          epoch           = 0;
  int          tmpInt;

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

  if((dataFile.peek()!= EOF))
  {
    numOfInputNodes = (dataFile.get() - 48);
    cout << "numOfInputNodes"<< numOfInputNodes<<endl;
  }
  if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
      dataFile.ignore(1);

  while((dataFile.peek()!= EOF))
  {
      for(int i = 0; i < numOfInputNodes; i++)// will store theses somewhere
      {
         tmpInt = (dataFile.get() - 48);
         cout<<tmpInt;    if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
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
double SigmoidFunction(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
//==============================================================================================================================

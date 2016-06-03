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
#include <string.h>
using namespace std;

//==============================================================================================================================
int main(int argc, char* argv[])
{
  ifstream     dataFile;
  string       tempString;

  string       fileName;
  int          numHiddenNodes;
  int          epoch;
  double       learningRate;

  cout<<"ARGC: "<<argc<<endl;
  if(argc < 9)
  {
    cout<<"PLEASE ENTER ALL DATA NEEDED IE: FILE NAME, #Hidden nodes, Epoch, and learning rate."<<endl;
    cout<<"Program will now close. Please Restart and try again."<<endl;
    exit(1);
  }

  for(int i = 1; i < argc; i = i+2)
  {
    cout<<"argv[i]: "<<argv[i]<<endl;
    if(strcmp(argv[i], "-f") == 0)
    {
      cout<<"SETTING FILE NAME"<<endl;
      fileName = argv[i+1];
    }
    else if(strcmp(argv[i], "-h") == 0)
    {
      cout<<"SETTING NUMBER OF HIDDEN NODES"<<endl;
      numHiddenNodes = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-e") == 0)
    {
      cout<<"SETTING EPOCH"<<endl;
      epoch = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-l") == 0)
    {
      cout<<"SETTING learningRate"<<endl;
      learningRate = atof(argv[i+1]);
    }
  }

  cout<<"fileName: "<<fileName<<" numHiddenNodes:"<<numHiddenNodes<<" epoch:"<<epoch<<" learningRate:"<<learningRate<<endl;

  return 0;
}  // END OF MAIN
//==============================================================================================================================

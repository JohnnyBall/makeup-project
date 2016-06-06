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

  string       fileName = "NOENTRY";
  int          numHiddenNodes = 0;
  int          epoch = 0;
  double       learningRate = 0.0;

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
    cout << "Failed To open file,your file name is: "<< fileName<<" :Restart Program and try again. ";
    exit(1);
  }
  while((dataFile.peek()!= EOF))
  {
    if((dataFile.peek() == '\n' || dataFile.peek() == '\r'))// checks for newlines and stuff and ignores them
      dataFile.ignore(1);
    while((dataFile.peek()!= EOF) && ((dataFile.peek() != '\n') && (dataFile.peek() != '\r')))// reads until EOF or \n or \r
    {
    }
  }
  dataFile.close();
//******************************************************************************************************************************
  return 0;
}// END OF MAIN
//==============================================================================================================================

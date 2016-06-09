#include <fstream>
#include <string.h>

#include "TNtuple.h"

void readASCIINTuple(char *inputFileName) {

  ifstream in(inputFileName);

  char headerLine[1024];
  in.getline(headerLine, 1024);

  char variableNames[1024];
  char *token = strtok(headerLine, " \t");
  if(token == NULL) exit(1);
  strcpy(variableNames, token);
  int nVariables = 1;
  while(true) {
    token = strtok(NULL, " \t");
    if(token == NULL) break;
    strcat(variableNames, ":");
    strcat(variableNames, token);
  }

  std::cout << "variableNames = " << variableNames << std::endl;

  token = strtok(inputFileName, ".");
  char outputFileName[1024];
  strcpy(outputFileName, inputFileName);
  strcat(outputFileName, ".root");

  std::cout << "outputFileName = " << outputFileName << std::endl;

  TFile *f = new TFile(outputFileName, "RECREATE");

  TNtuple *nTuple = new TNtuple(inputFileName, inputFileName, variableNames);

  cout << "Number of rows read = " << nTuple->ReadStream(in) << endl;

  in.close();

  f->Write();

}

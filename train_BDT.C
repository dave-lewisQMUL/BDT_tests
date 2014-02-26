#include "TString.h"
#include "TMVA/Factory.h"

void train_BDT(){

  TFile* outputFile = TFile::Open("TMVA.root","recreate");
  TMVA::Factory* factory = new TMVA::Factory("tmvaTest",outputFile,"");
  TFile* inputFile = new TFile("test_tree.root");

  TTree* sig = (TTree*)inputFile->Get("sig");
  TTree* bkg = (TTree*)inputFile->Get("bkg");
  int nSig = sig->GetEntries();
  int nBkg = bkg->GetEntries();

  factory->SetInputTrees(sig,bkg,1.0,1.0);

  factory->AddVariable("iso7",'F');
  factory->AddVariable("Lxy", 'F');
  factory->AddVariable("a_2D",'F');
  factory->AddVariable("DR",'F');
  factory->AddVariable("pTime",'F');
  factory->AddVariable("logChi2z",'F');
  factory->AddVariable("logChi2xy",'F');
  factory->AddVariable("pT",'F');
  factory->AddVariable("DCA",'F');
  factory->AddVariable("ZCA",'F');
  factory->AddVariable("d0min",'F');
  factory->AddVariable("d0max",'F');
  factory->AddVariable("Plng_min",'F');
  factory->AddVariable("Plng_max",'F');

  TCut mycut="";
  factory->PrepareTrainingAndTestTree(mycut,0,0,0,0);
  factory->BookMethod(TMVA::Types::kBDT,"BDT","");
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  
  outputFile->Close();
  std::cout << "Done"<<std::endl;
  delete factory;

}

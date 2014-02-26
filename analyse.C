#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMVA/Reader.h"
#include <vector>

void analyse(){

  TFile* hist_file = new TFile("Analysis.root","recreate");
  TH1D* hSig = new TH1D("hSig","Signal",100,-10.0,10.0);
  TH1D* hBkg = new TH1D("hBkg","Background",100,-10.0,10.0);
  
  TMVA::Reader* reader = new TMVA::Reader();
  float iso7, Lxy,a_2D,DR,pTime,logChi2z,logChi2xy;
  float pT,DCA,ZCA,d0min,d0max,Plng_min,Plng_max;
  float vars_list[14]={&iso7,&Lxy,&a_2D,&DR,&pTime,&logChi2z,&logChi2xy,
		       &pT,&DCA,&ZCA,&d0min,&d0max,&Plng_min,&Plng_max};
  string var_names[14]={"iso7","Lxy","a_2D","DR","pTime","logChi2z",
			"logChi2xy","pT","DCA","ZCA","d0min","d0max",
			"Plng_min","Plng_max"};
  for (int i=0;i<14;i++){
    reader->AddVariable(var_names[i],vars_list[i]);
  }

  reader->BookMVA("BDT","weights/tmvaTest_BDT.weights.xml");
  TFile* inputFile = new TFile("test_tree.root");
  inputFile->ls();
  TTree* sig = dynamic_cast<TTree*>(inputFile->Get("sig"));
  TTree* bkg = dynamic_cast<TTree*>(inputFile->Get("bkg"));
  std::vector<TTree*> tree_vec;
  tree_vec.push_back(sig);
  tree_vec.push_back(bkg);
  
  for(int i=0;i<tree_vec.size();i++){
    tree_vec[i]->Print();
    for(int j=0;j<14;j++){
      tree_vec[i]->SetBranchAddress(var_names[j],vars_list[j]);
    }
    //loop over events
    for(int k=0;k<tree_vec[i]->GetEntries();k++){
      tree_vec[i]->GetEntry(k);
      double tBDT = reader->EvaluateMVA("BDT");
      if(i==0){
	hSig->Fill(tBDT);
      }else{
	hBkg->Fill(tBDT);
      }
    }
  }
  hist_file->Write();
  hist_file->CLose();
}

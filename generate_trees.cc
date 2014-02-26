//Use this to generate signal and background distributions,
//for testing TMVA BDT.

#include <iostream>
#include <Riostream.h>
#include <cmath>
#include <TFile.h>
#include <TTree.h>
#include <TRandom3.h>
#include <random>

int main(){

  const int num_vals = 500;
  const double sigma = 0.5;
  int seed = 12345;
  TRandom3* ran = new TRandom3(seed);
  TFile file("test_tree.root","recreate");
  TTree sig("sig", "Signal tree");
  TTree bkg("bkg", "Background tree");

  Double_t iso7 = -999;
  Double_t Lxy = -999;
  Double_t a_2D = -999; 
  Double_t DR = -999;
  Double_t pTime = -999;
  Double_t logChi2z = -999;
  Double_t logChi2xy = -999;
  Double_t pT = -999; 
  Double_t DCA = -999;
  Double_t ZCA = -999;
  Double_t d0min = -999;
  Double_t d0max = -999;
  Double_t Plng_min = -999;
  Double_t Plng_max = -999;
  //Variable list for histogram filling. 
  Double_t* vars_list[14]={&iso7,&Lxy,&a_2D,&DR,&pTime,&logChi2z,&logChi2xy,
			   &pT,&DCA,&ZCA,&d0min,&d0max,&Plng_min,&Plng_max};
  string var_name_list[14]={"iso7","Lxy","a_2D","DR","pTime","logChi2z",
			    "logChi2xy","pT","DCA","ZCA","d0min","d0max",
			    "Plng_min","Plng_max"};
  for (int i=0;i<14;i++){
    sig.Branch(var_name_list[i],vars_list[i],var_name_list[i]+"/D");
    bkg.Branch(var_name_list[i],vars_list[i],var_name_list[i]+"/D");
  }

  //generate signal events
  //Gaussian distribution, between actual limits
  for (int i=0;i<num_vals;i++){
    iso7 = ran->Gaus();
    Lxy = 4.0*ran->Gaus();
    a_2D = 3.0*ran->Gaus();
    DR = 6.0*ran->Gaus();
    pTime = (40.0*ran->Gaus())-5.0;
    logChi2z = (30.0*ran->Gaus())-20.0;
    logChi2xy = (30.0*ran->Gaus())-20.0;
    pT = (65.0*ran->Gaus())+5.0;
    DCA = ran->Gaus()-0.5;
    ZCA = (400.0*ran->Gaus())-200.0;
    d0min = (0.8*ran->Gaus())-0.4;
    d0max = (4.0*ran->Gaus())-2.0;
    Plng_min = 20.0*ran->Gaus();
    Plng_max = 40.0*ran->Gaus();
    sig.Fill();
  }

  //generate background events
  //falling exponential distribution, between actual limits
  std::random.default_random_engine generator;
  std::random.exponential_distribution<double> distribution(4);
  for (int i=0;i<num_vals;i++){
    double number = distribution(generator);
    if (number<=1.0){iso7 = number;}
    number = distribution(generator);
    if(number<=1.0){ Lxy = 4.0*number;}
    number = distribution(generator);
    if(number<=1.0){ a_2D = 3.0*number;}
    number = distribution(generator);
    if(number<=1.0){ DR = 6.0*number;}
    number = distribution(generator);
    if(number<=1.0){ pTime = (40.0*number)-5.0;}
    number = distribution(generator);
    if(number<=1.0){logChi2z = (30.0*number)-20.0;}
    number = distribution(generator);
    if(number<=1.0){logChi2xy = (30.0*number)-20.0;}
    number = distribution(generator);
    if(number<=1.0){pT = (65.0*number)+5.0;}
    number = distribution(generator);
    if(number<=1.0){DCA = number-0.5;}
    number = distribution(generator);
    if(number<=1.0){ZCA = (400.0*number)-200.0;}
    number = distribution(generator);
    if(number<=1.0){d0min = (0.8*number)-0.4;}
    number = distribution(generator);
    if(number<=1.0){d0max = (4.0*number)-2.0;}
    number = distribution(generator);
    if(number<=1.0){Plng_min = 20.0*number;}
    number = distribution(generator);
    if(number<=1.0){Plng_max = 40.0*number;}
    bkg->Fill();
  }
  file.Write();
  file.Close();
  return 0;
}

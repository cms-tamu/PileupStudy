#include <iostream>
#include <iomanip>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <math.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TChain.h>
#include <TChainElement.h>
#include "Helpers.h"

Float_t counter[20][18];//samples; selections
Float_t TotEff[20][18];
Float_t TotEffErr[20][18];
Float_t RelEff[20][18];
Float_t RelEffErr[20][18];
Float_t epsvsalph1[20]={0.0};
Float_t Err[20]={0.0};
Float_t epsvsalph2[20]={0.0};
Float_t epsvsalph[20]={0.0};
Float_t epsvalp[20]={0.0};
Float_t epsvalp2[20]={0.0};


//--------- 50% shifts----------//
std::array<float,75> weight_array_shift1 = {0.00E+00, 6.96E-01, 4.87E-01, 5.94E-01, 8.13E-01, 7.76E-01, 5.85E-01, 3.38E-01, 5.47E-01, 5.31E-01, 4.88E-01, 5.47E-01, 6.27E-01, 7.19E-01, 7.63E-01, 7.92E-01, 8.41E-01, 8.92E-01, 9.18E-01, 9.35E-01, 9.57E-01, 9.79E-01, 1.01E+00, 1.03E+00, 1.05E+00, 1.07E+00, 1.10E+00, 1.11E+00, 1.12E+00, 1.14E+00, 1.13E+00, 1.15E+00, 1.14E+00, 1.14E+00, 1.14E+00, 1.13E+00, 1.11E+00, 1.11E+00, 1.10E+00, 1.10E+00, 1.08E+00, 1.08E+00, 1.09E+00, 1.09E+00, 1.13E+00, 1.13E+00, 1.13E+00, 1.19E+00, 1.21E+00, 1.25E+00, 1.27E+00, 1.33E+00, 1.36E+00, 1.37E+00, 1.51E+00, 1.56E+00, 1.50E+00, 1.55E+00, 1.59E+00, 1.51E+00, 1.75E+00, 1.43E+00, 1.29E+00, 1.17E+00, 1.20E+00, 1.06E+00, 1.00E+00, 9.93E-01, 1.02E+00, 1.00E+00, 1.00E+00, 1.00E+00, 1.00E+00, 1.01E+00, 1.00E+00};

std::array<float,75> weight_array_shift2 = {0.00E+00, 0.00E+00, 3.39E-01, 2.89E-01, 4.83E-01, 6.31E-01, 4.54E-01, 1.98E-01, 1.85E-01, 2.90E-01, 2.59E-01, 2.67E-01, 3.43E-01, 4.50E-01, 5.48E-01, 6.04E-01, 6.67E-01, 7.50E-01, 8.18E-01, 8.58E-01, 8.95E-01, 9.37E-01, 9.89E-01, 1.04E+00, 1.08E+00, 1.13E+00, 1.18E+00, 1.21E+00, 1.24E+00, 1.28E+00, 1.28E+00, 1.30E+00, 1.31E+00, 1.30E+00, 1.30E+00, 1.28E+00, 1.26E+00, 1.23E+00, 1.21E+00, 1.21E+00, 1.18E+00, 1.16E+00, 1.17E+00, 1.19E+00, 1.23E+00, 1.28E+00, 1.28E+00, 1.34E+00, 1.43E+00, 1.51E+00, 1.59E+00, 1.68E+00, 1.80E+00, 1.86E+00, 2.07E+00, 2.35E+00, 2.34E+00, 2.33E+00, 2.47E+00, 2.40E+00, 2.64E+00, 2.51E+00, 1.84E+00, 1.51E+00, 1.41E+00, 1.27E+00, 1.06E+00, 9.93E-01, 1.01E+00, 1.02E+00, 1.00E+00, 1.00E+00, 1.00E+00, 1.01E+00, 1.01E+00}; 

std::array<float,75> weight_array_shift4 = {0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 1.64E-01, 1.82E-01, 2.19E-01, 1.25E-01, 8.40E-02, 5.75E-02, 4.80E-02, 7.74E-02, 8.87E-02, 1.20E-01, 1.88E-01, 2.72E-01, 3.65E-01, 4.53E-01, 5.45E-01, 6.43E-01, 7.32E-01, 8.04E-01, 8.85E-01, 9.76E-01, 1.07E+00, 1.17E+00, 1.27E+00, 1.37E+00, 1.46E+00, 1.55E+00, 1.60E+00, 1.66E+00, 1.68E+00, 1.68E+00, 1.70E+00, 1.66E+00, 1.63E+00, 1.58E+00, 1.52E+00, 1.49E+00, 1.44E+00, 1.40E+00, 1.38E+00, 1.37E+00, 1.44E+00, 1.52E+00, 1.57E+00, 1.71E+00, 1.84E+00, 2.03E+00, 2.28E+00, 2.54E+00, 2.86E+00, 3.14E+00, 3.73E+00, 4.38E+00, 4.84E+00, 5.48E+00, 5.76E+00, 5.59E+00, 6.51E+00, 6.01E+00, 4.87E+00, 3.78E+00, 2.60E+00, 1.92E+00, 1.49E+00, 1.26E+00, 1.07E+00, 1.01E+00, 1.01E+00, 1.02E+00, 1.00E+00, 1.01E+00, 1.01E+00};

std::array<float,75> weight_array_shift6 = {0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 7.43E-02, 3.61E-02, 4.06E-02, 3.62E-02, 2.18E-02, 1.53E-02, 1.64E-02, 3.49E-02, 4.86E-02, 7.26E-02, 1.25E-01, 2.04E-01, 2.99E-01, 3.89E-01, 4.88E-01, 6.03E-01, 7.24E-01, 8.37E-01, 9.58E-01, 1.10E+00, 1.26E+00, 1.42E+00, 1.59E+00, 1.75E+00, 1.88E+00, 2.01E+00, 2.09E+00, 2.15E+00, 2.18E+00, 2.16E+00, 2.13E+00, 2.05E+00, 1.98E+00, 1.90E+00, 1.80E+00, 1.72E+00, 1.68E+00, 1.66E+00, 1.70E+00, 1.76E+00, 1.84E+00, 2.04E+00, 2.26E+00, 2.59E+00, 2.92E+00, 3.41E+00, 4.11E+00, 4.74E+00, 5.93E+00, 7.39E+00, 8.72E+00, 1.02E+01, 1.19E+01, 1.31E+01, 1.52E+01, 1.40E+01, 1.20E+01, 9.07E+00, 6.86E+00, 4.81E+00, 2.75E+00, 1.91E+00, 1.51E+00, 1.29E+00, 1.07E+00, 1.01E+00, 1.01E+00, 1.03E+00, 1.01E+00};

std::array<float,75> weight_array_shift8 = {0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 1.38E-02, 1.05E-02, 1.05E-02, 9.67E-03, 7.45E-03, 6.91E-03, 9.01E-03, 2.11E-02, 3.24E-02, 5.45E-02, 1.02E-01, 1.75E-01, 2.68E-01, 3.65E-01, 4.83E-01, 6.28E-01, 7.84E-01, 9.44E-01, 1.13E+00, 1.34E+00, 1.57E+00, 1.82E+00, 2.04E+00, 2.27E+00, 2.46E+00, 2.61E+00, 2.71E+00, 2.76E+00, 2.73E+00, 2.66E+00, 2.58E+00, 2.47E+00, 2.34E+00, 2.20E+00, 2.11E+00, 2.04E+00, 2.06E+00, 2.12E+00, 2.18E+00, 2.36E+00, 2.64E+00, 3.07E+00, 3.59E+00, 4.36E+00, 5.26E+00, 6.36E+00, 8.51E+00, 1.11E+01, 1.39E+01, 1.72E+01, 2.15E+01, 2.45E+01, 3.15E+01, 3.29E+01, 2.80E+01, 2.11E+01, 1.69E+01, 1.15E+01, 7.26E+00, 4.77E+00, 2.79E+00, 1.95E+00, 1.51E+00, 1.29E+00, 1.07E+00, 1.02E+00, 1.02E+00};

std::array<float,75> weight_array_shift10 = {0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 0.00E+00, 3.56E-03, 2.79E-03, 3.60E-03, 4.36E-03, 4.09E-03, 4.17E-03, 6.00E-03, 1.58E-02, 2.65E-02, 4.67E-02, 9.17E-02, 1.64E-01, 2.65E-01, 3.80E-01, 5.23E-01, 7.08E-01, 9.22E-01, 1.15E+00, 1.40E+00, 1.71E+00, 2.01E+00, 2.36E+00, 2.66E+00, 2.95E+00, 3.19E+00, 3.35E+00, 3.40E+00, 3.40E+00, 3.32E+00, 3.20E+00, 3.06E+00, 2.86E+00, 2.73E+00, 2.61E+00, 2.59E+00, 2.61E+00, 2.64E+00, 2.84E+00, 3.12E+00, 3.56E+00, 4.20E+00, 5.18E+00, 6.46E+00, 8.12E+00, 1.09E+01, 1.50E+01, 1.99E+01, 2.60E+01, 3.42E+01, 4.13E+01, 5.68E+01, 6.14E+01, 5.81E+01, 4.97E+01, 3.95E+01, 2.69E+01, 1.79E+01, 1.15E+01, 7.37E+00, 4.88E+00, 2.79E+00, 1.95E+00, 1.51E+00, 1.30E+00, 1.08E+00};

std::array<float,75> weight_array_default = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 

std::array<float,75> weight_array_allzero = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//--------5% Shifts--------//
std::array<float,75> weight_array_PUC_nominal = {0.00E+00, 2.55E-01, 4.35E-01, 7.12E-01, 7.82E-01, 8.71E-01, 6.82E-01, 2.69E-01, 2.72E-01, 3.94E-01, 4.29E-01, 5.28E-01, 6.73E-01, 8.10E-01, 8.98E-01, 9.50E-01, 1.02E+00, 1.07E+00, 1.08E+00, 1.07E+00, 1.05E+00, 1.04E+00, 1.06E+00, 1.09E+00, 1.10E+00, 1.13E+00, 1.16E+00, 1.19E+00, 1.21E+00, 1.25E+00, 1.25E+00, 1.26E+00, 1.23E+00, 1.19E+00, 1.12E+00, 1.03E+00, 9.14E-01, 7.93E-01, 6.70E-01, 5.54E-01, 4.36E-01, 3.34E-01, 2.48E-01, 1.79E-01, 1.27E-01, 8.77E-02, 5.77E-02, 3.80E-02, 2.43E-02, 1.53E-02, 9.44E-03, 5.81E-03, 3.55E-03, 2.15E-03, 1.47E-03, 1.14E-03, 1.01E-03, 1.13E-03, 1.51E-03, 2.05E-03, 3.31E-03, 4.41E-03, 5.28E-03, 5.72E-03, 6.34E-03, 6.09E-03, 5.56E-03, 4.93E-03, 4.52E-03, 4.02E-03, 3.55E-03, 3.11E-03, 2.70E-03, 2.36E-03, 2.02E-03};

std::array<float,75> weight_array_PUC_up = {0.00E+00, 2.48E-01, 3.35E-01, 6.69E-01, 6.80E-01, 7.85E-01, 6.08E-01, 2.44E-01, 1.86E-01, 2.56E-01, 2.85E-01, 3.34E-01, 4.44E-01, 5.79E-01, 6.80E-01, 7.46E-01, 8.17E-01, 9.00E-01, 9.55E-01, 9.74E-01, 9.78E-01, 9.79E-01, 1.00E+00, 1.04E+00, 1.09E+00, 1.14E+00, 1.19E+00, 1.24E+00, 1.30E+00, 1.37E+00, 1.40E+00, 1.45E+00, 1.46E+00, 1.46E+00, 1.42E+00, 1.36E+00, 1.26E+00, 1.14E+00, 1.00E+00, 8.73E-01, 7.29E-01, 5.96E-01, 4.82E-01, 3.79E-01, 2.98E-01, 2.29E-01, 1.68E-01, 1.25E-01, 9.08E-02, 6.56E-02, 4.62E-02, 3.26E-02, 2.26E-02, 1.52E-02, 1.09E-02, 7.81E-03, 5.39E-03, 4.02E-03, 3.41E-03, 3.28E-03, 4.36E-03, 5.34E-03, 6.24E-03, 6.80E-03, 7.66E-03, 7.51E-03, 7.02E-03, 6.39E-03, 6.01E-03, 5.49E-03, 4.98E-03, 4.48E-03, 4.01E-03, 3.61E-03, 3.18E-03};

std::array<float,75> weight_array_PUC_down = {0.00E+00, 2.65E-01, 5.66E-01, 7.52E-01, 9.03E-01, 9.80E-01, 7.55E-01, 3.17E-01, 4.37E-01, 6.00E-01, 6.78E-01, 8.43E-01, 9.87E-01, 1.10E+00, 1.17E+00, 1.21E+00, 1.23E+00, 1.23E+00, 1.20E+00, 1.15E+00, 1.12E+00, 1.11E+00, 1.10E+00, 1.10E+00, 1.09E+00, 1.09E+00, 1.10E+00, 1.10E+00, 1.10E+00, 1.09E+00, 1.06E+00, 1.03E+00, 9.71E-01, 8.98E-01, 8.09E-01, 7.10E-01, 6.02E-01, 4.94E-01, 3.91E-01, 3.00E-01, 2.16E-01, 1.50E-01, 1.00E-01, 6.39E-02, 4.01E-02, 2.41E-02, 1.37E-02, 7.80E-03, 4.29E-03, 2.35E-03, 1.27E-03, 7.17E-04, 4.48E-04, 3.35E-04, 3.45E-04, 4.37E-04, 5.83E-04, 8.33E-04, 1.23E-03, 1.71E-03, 2.76E-03, 3.60E-03, 4.21E-03, 4.45E-03, 4.79E-03, 4.47E-03, 3.96E-03, 3.41E-03, 3.03E-03, 2.61E-03, 2.23E-03, 1.89E-03, 1.59E-03, 1.34E-03, 1.11E-03};


//--- 50% shift up ---//
//std::array<float,75> weight_array = weight_array_default;
//std::array<float,75> weight_array = weight_array_shift2;
//std::array<float,75> weight_array = weight_array_shift3;
//std::array<float,75> weight_array = weight_array_shift4;
//std::array<float,75> weight_array = weight_array_shift6;
//std::array<float,75> weight_array = weight_array_shift8;
//std::array<float,75> weight_array = weight_array_shift10;
//std::array<float,75> weight_array = weight_array_allzero;
//std::array<float,75> weight_array = weight_array_default;



//--- 5% shifts up and down in pileupCalc.py, MC distribution from mix_2016_25ns_Morion17MC_PoissonOOTPU_cfi ----//
//std::array<float,75> weight_array = weight_array_PUC_nominal;
//std::array<float,75> weight_array = weight_array_PUC_up;
std::array<float,75> weight_array = weight_array_PUC_down;


void setup()
{
for(int i=0;i<20;i++){
  for(int j=0;j<18;j++){  
    counter[i][j]=0;
    TotEff[i][j]=0.0;
    RelEff[i][j]=0.0;
    TotEffErr[i][j]=0.0;
    RelEffErr[i][j]=0.0;
  }
 }
}

int k = -1;


void efficiency(const std::vector<std::string>& dirNames)
{
	
  std::cout<<"Loop starts with k as "<<k<<endl;
  TString mass_string;
  TString cT_string;

  bool verbose(false);
  //bool verbose(true);
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  cout<<" dirNames  "<<dirNames[0]<<endl;

  decodeFileNameMany(dirNames, mass_string, cT_string);

  TString fileName;
  fileName = "DarkSUSY_mH_125_mGammaD_" + mass_string + "_cT_" + cT_string;
  
  cout<<" Sample   "<<fileName<<endl;
  // add files to the chain
  addfilesMany(chain, dirNames, ext);
  
  //Initialize Variables and counters
  // TFile *f[20]; //A root file is a suit of consecutive data records
  // TTree *t[20]; //comsists of a list of independent branches (Tbranch); one or multiple branches
  char nameFile[50]; //refers to a block of characters?
 
 
  Int_t numVertex = 0;	//The number of vertices in the event
  Int_t npv       = 0;  //Number of PU from PileupInfo
  Float_t diMuonC_Mass;	//allows for effective use of architecture with wider formats
  Float_t diMuonF_Mass;
  Bool_t  is1GenMu17;
  Bool_t  is2GenMu8;
  Bool_t  is3GenMu8;
  Bool_t  is4GenMu8;
  
  Bool_t  is1SelMu17;
  Bool_t  is2SelMu8;
  Bool_t  is3SelMu8;
  Bool_t  is4SelMu8;
  
  Float_t selMu0_pT;
  Float_t selMu1_pT;
  Float_t selMu2_pT;
  Float_t selMu3_pT;

  Float_t massC;
  Float_t massF;
 
  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;

  Bool_t  is2DiMuons;
  Bool_t  is2MuJets;
  Bool_t  isVtxOK;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;
  
  Bool_t  is2DiMuonHLTFired;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t diMuonF_IsoTk_FittedVtx;
  
  Float_t  genA0_Lxy;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t  genA1_Lxy;
  Float_t  genA0_Lz;
  Float_t  genA1_Lz;
  Float_t  diMuons_dz_FittedVtx;
  
  Int_t  diMuonC_m1_FittedVtx_hitpix_l3inc;
  Int_t  diMuonC_m2_FittedVtx_hitpix_l3inc;
  Int_t  diMuonF_m1_FittedVtx_hitpix_l3inc;
  Int_t  diMuonF_m2_FittedVtx_hitpix_l3inc;
  Int_t  nRecoMu;


  TH1F *diMuons_dz = new TH1F("diMuons_dz","",100,-1.0,1.0);

  TH1F *P_t_Mu0 = new TH1F("P_t_Mu0","",200,0.0,100.0);   
  TH1F *P_t_Mu1 = new TH1F("P_t_Mu1","",200,0.0,100.0); 
  TH1F *P_t_Mu2 = new TH1F("P_t_Mu2","",200,0.0,100.0); 
  TH1F *P_t_Mu3 = new TH1F("P_t_Mu3","",200,0.0,100.0); 
  
  TH1F *mass_C= new TH1F("mass_C","",200,0.0,1.0);
  TH1F *mass_F= new TH1F("mass_F","",200,0.0,1.0);

  TH1F *iso_C = new TH1F("iso_C","",200,0.0,10.0);
  TH1F *iso_F = new TH1F("iso_F","",200,0.0,10.0);

  TH1F *eta_Mu0 = new TH1F("eta_Mu0","",100,-2.5,2.5);
  TH1F *eta_Mu1 = new TH1F("eta_Mu1","",100,-2.5,2.5);
  TH1F *eta_Mu2 = new TH1F("eta_Mu2","",100,-2.5,2.5);
  TH1F *eta_Mu3 = new TH1F("eta_Mu3","",100,-2.5,2.5);

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  
  k++;
  //cout << "p: " << p << endl;
  //if(p == 0 || p%3 == 0) setup(); //reset vectors for every 4th cT for tables.
  
  while ((chEl=(TChainElement*)next())) {  //loopforfiles
     if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
		TFile* myfile = new TFile(chEl->GetTitle());
		if (!myfile) {
		  if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
		  continue;
		}
		//		if (verbose) std::cout << "Loading directory cutFlowAnalyzerPXBL3PXFL2" << std::endl;
		myfile->cd("cutFlowAnalyzerPXBL3PXFL2");
		
		TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
		if (!t) {
		  if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
		  continue;
		}
		
		//		if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;
		
       		int nentries;
		
		//   TFile *f[20];
		//   TTree *t[20];
		
		//   f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6537p4_PAT_v1_10000.root");
                //   f[1] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_5374_PAT_v1_10000.root");
		//   f[2] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[3] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[4] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[5] = new TFile("DarkSUSY_mH_125_mGammaD_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[6] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_005_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[7] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_01_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[8] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[9] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[10] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[11] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[12] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[13] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[14] = new TFile("ana.root");
	        //   f[15] = new TFile("out_ana_reco.root");

	// 5) allocate var to branch
                t->SetBranchAddress("numVertex",&numVertex);
                t->SetBranchAddress("npv",&npv);
		t->SetBranchAddress("diMuonC_FittedVtx_m",&diMuonC_Mass);
		t->SetBranchAddress("diMuonF_FittedVtx_m",&diMuonF_Mass);
		t->SetBranchAddress("nRecoMu",&nRecoMu);
		t->SetBranchAddress("is1GenMu17",&is1GenMu17);
		t->SetBranchAddress("is2GenMu8",&is2GenMu8);
		t->SetBranchAddress("is3GenMu8",&is3GenMu8);
		t->SetBranchAddress("is4GenMu8",&is4GenMu8);
		t->SetBranchAddress("is1SelMu17",&is1SelMu17);
		t->SetBranchAddress("is2SelMu8",&is2SelMu8);
		t->SetBranchAddress("is3SelMu8",&is3SelMu8);
		t->SetBranchAddress("is4SelMu8",&is4SelMu8);
		t->SetBranchAddress("selMu0_pT",&selMu0_pT);
		t->SetBranchAddress("selMu1_pT",&selMu1_pT);
		t->SetBranchAddress("selMu2_pT",&selMu2_pT);
		t->SetBranchAddress("selMu3_pT",&selMu3_pT);
		t->SetBranchAddress("massC",&massC);
		t->SetBranchAddress("massF",&massF);
		t->SetBranchAddress("selMu0_eta",&selMu0_eta);
		t->SetBranchAddress("selMu1_eta",&selMu1_eta);
		t->SetBranchAddress("selMu2_eta",&selMu2_eta);
		t->SetBranchAddress("selMu3_eta",&selMu3_eta);
		t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
		t->SetBranchAddress("isVertexOK",&isVtxOK);
		t->SetBranchAddress("is2DiMuons",&is2DiMuons);
		t->SetBranchAddress("is2MuJets",&is2MuJets);
		t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DiMuonsFittedVtxOK);
		t->SetBranchAddress("diMuons_dz_FittedVtx",&diMuons_dz_FittedVtx);
		t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
		t->SetBranchAddress("isDiMuonHLTFired",&is2DiMuonHLTFired);
		t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
		t->SetBranchAddress("genA0_Lxy",&genA0_Lxy);
		t->SetBranchAddress("genA1_Lxy",&genA1_Lxy);
		t->SetBranchAddress("genA0_Lz",&genA0_Lz);
		t->SetBranchAddress("genA1_Lz",&genA1_Lz);
		t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_l3inc",&diMuonC_m1_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_l3inc",&diMuonC_m2_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_l3inc",&diMuonF_m1_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_l3inc",&diMuonF_m2_FittedVtx_hitpix_l3inc);
		
		// TH1F *hev = new THIF("Event Number","",1000,0.0,1000);  // as it is new variable we must change name
		//    TH2F *hdimCm = new TH2F("diMuonC_Mass","",500,0.0,1.0,500,0.0,1.0);
		//7)create loop
		
		nentries = t->GetEntries(); //no of entries

		for(int i=0;i<nentries;i++){ //loop for number of events
		  t->GetEntry(i);
		  //cout<<"i is "<<i<<endl;
		  counter[k][0] = counter[k][0] + weight_array[npv];
		  // cout<<" dimuonC_Iso  "<<diMuonC_IsoTk_FittedVtx<<endl;
		  // cout<<" dimuonF_Iso  "<<diMuonF_IsoTk_FittedVtx<<endl;
		  
		  if(nRecoMu>=4){
		    P_t_Mu0->Fill(selMu0_pT);
		    P_t_Mu1->Fill(selMu1_pT);
		    P_t_Mu2->Fill(selMu2_pT);
		    P_t_Mu3->Fill(selMu3_pT);
		    eta_Mu0->Fill(selMu0_eta);
		    eta_Mu1->Fill(selMu1_eta);
		    eta_Mu2->Fill(selMu2_eta);
		    eta_Mu3->Fill(selMu3_eta);

		    if(is2DiMuons){
		      mass_C->Fill(massC);
		      mass_F->Fill(massF);  
		      iso_C->Fill(diMuonC_IsoTk_FittedVtx);
		      iso_F->Fill(diMuonF_IsoTk_FittedVtx);
		    }
		  }
		  
		  if(is1GenMu17)counter[k][1] = counter[k][1] + weight_array[npv];
		  if(is2GenMu8) counter[k][2] = counter[k][2] + weight_array[npv];
		  if(is3GenMu8) counter[k][3] = counter[k][3] + weight_array[npv];
		  if(is4GenMu8){
		    counter[k][4] = counter[k][4] + weight_array[npv];
		    if( (genA0_Lxy<9.8&&fabs(genA0_Lz)<46.5) && (genA1_Lxy<9.8&&fabs(genA1_Lz)<46.5)){ counter[k][5] = counter[k][5] + weight_array[npv];}
		    //if( (genA0_Lxy<9.8&&fabs(genA0_Lz)<48.5) && (genA1_Lxy<9.8&&fabs(genA1_Lz)<48.5)){ counter[k][5] = counter[k][5] + weight_array[npv];}
		  }
		  
		  if(is1SelMu17)counter[k][6] = counter[k][6] + weight_array[npv];
		  if(is2SelMu8) counter[k][7] = counter[k][7] + weight_array[npv];
		  if(is3SelMu8) counter[k][8] = counter[k][8] + weight_array[npv];
		  if(is4SelMu8){
		    counter[k][9] = counter[k][9] + weight_array[npv];
		  
		  if(isVtxOK){
		     counter[k][10] = counter[k][10] + weight_array[npv];
		    if(is2MuJets){
		      counter[k][11] = counter[k][11] + weight_array[npv];
		      if(is2DiMuons){

			diMuons_dz->Fill(diMuons_dz_FittedVtx);
			 counter[k][12] = counter[k][12] + weight_array[npv];
			if( (diMuonC_m1_FittedVtx_hitpix_l3inc==1||diMuonC_m2_FittedVtx_hitpix_l3inc==1) &&
			    (diMuonF_m1_FittedVtx_hitpix_l3inc==1||diMuonF_m2_FittedVtx_hitpix_l3inc==1)){
			  counter[k][13] = counter[k][13] + weight_array[npv];
			  if( fabs(diMuons_dz_FittedVtx)<0.1){
			    counter[k][14] = counter[k][14] + weight_array[npv];
			    if(is2DiMuonsMassOK){
			      counter[k][15] = counter[k][15] + weight_array[npv];
			      if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0){
				counter[k][16] = counter[k][16] + weight_array[npv];
				if(is2DiMuonHLTFired){
				  counter[k][17] = counter[k][17] + weight_array[npv];
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
		}
		myfile->Close();
  }

  // 8)Fill Histogram with event number
  // hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
  cout<<"  Here is where the plotting starts  "<<endl;
  cout<<"  Here is where the plotting starts  "<<endl;
 
  TCanvas *c = new TCanvas("c","c",800,600);
  diMuons_dz->Draw();
  c->SaveAs("diMuons_dz.png","recreate");

 //  TCanvas *cc = new TCanvas("cc","cc",800,600);
 //  mass_C->Draw();
 //  cc->SaveAs("massC.png","recreate");

 //  TCanvas *cf = new TCanvas("cf","cf",800,600);
 //  mass_F->Draw();
 //  cf->SaveAs("massF.png","recreate");
 
 //  TCanvas *e = new TCanvas("e","e",800,600);
 //  eta_Mu0->Draw();
 //  e->SaveAs("e0.png","recreate");

 //  TCanvas *e1 = new TCanvas("e1","e1",800,600);
 //  eta_Mu0->Draw();
 //  e1->SaveAs("e1.png","recreate");

 //  TCanvas *e2 = new TCanvas("e2","e2",800,600);
 // eta_Mu0->Draw();
 // e2->SaveAs("e2.png","recreate");
 
 // TCanvas *e3 = new TCanvas("e3","e3",800,600);
 // eta_Mu0->Draw();
 // e3->SaveAs("e3.png","recreate");

 // TCanvas *isoC = new TCanvas("isoC","isoC",800,600);
 // iso_C->Draw();
 // isoC->SaveAs("isoC.png","recreate");

 // TCanvas *isoF = new TCanvas("isoF","isoF",800,600);
 // iso_C->Draw();
 // isoF->SaveAs("isoF.png","recreate");

 // TCanvas *c = new TCanvas("c","c",800,600);
 //  P_t_Mu0->Draw();
 //  c->SaveAs("pt_mu0.png","recreate");

 //  TCanvas *c1 = new TCanvas("c1","c1",800,600);
 //  P_t_Mu1->Draw();
 //  c1->SaveAs("pt_mu1x.png","recreate");
  
 //  TCanvas *c2 = new TCanvas("c2","c2",800,600);
 //  P_t_Mu2->Draw();
 //  c2->SaveAs("pt_mu2.png","recreate");

 //  TCanvas *c3 = new TCanvas("c3","c3",800,600);
 //  P_t_Mu3->Draw();
 //  c3->SaveAs("pt_mu3.png","recreate");

  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for(int m=0;m<18;m++){
    TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
    TotEffErr[k][m]= sqrt( (TotEff[k][m]*(1-TotEff[k][m]))/(counter[k][0]*1.0));
    if(m>0){
      if(m==6){
	RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][0]*1.0));
      }
      else{
	RelEff[k][m]=  counter[k][m]/(counter[k][m-1]*1.0);
	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][m-1]*1.0));
      }
    }
  }
  
  epsvsalph[k] = counter[k][17]/(counter[k][5]*1.0); //mainvalue of epsilob_rec/alpha_gen
  cout<<"counter[k][17] "<<counter[k][17]<<endl; 
  cout<<"counter[k][5] "<<counter[k][5]<<endl;

  cout<<" mass  "<<mass_string<<" cT  "<<cT_string<<endl;
  cout<<" TotEff "<<counter[k][17]/(counter[k][0]*1.0)<<endl;
  cout<<" epsvsalph[k]  "<<epsvsalph[k]<<endl;
  // cout<<" counter[k][5]  "<<counter[k][5]*1.0<<endl;
  Err[k]=   sqrt( (epsvsalph[k]*(1-epsvsalph[k]))/(counter[k][5]*1.0)); 


  cout<<"        "<<endl;
  //  cout<<"begin{landscape}"<<endl;
  cout<<"begin{table}[ht]"<<endl;
  cout<<"renewcommand{tabcolsep}{2pt}"<<endl;
  cout<<" caption{Acceptances and efficiencies of the event selection requirements for dark photon m="<<mass_string<<" and ctau="<<cT_string<<"}  "<<endl;
  cout<<"centering "<<endl;
  cout<<"begin{tabular}{ |c|c|c|c|c|c|}  hline"<<endl;
  
  cout<<" Selection &  "<<" \\# Events &  "<<"   Tot. Eff  & "<<" Rel. Eff &  "<<" Tot. EffError &  "<<" Rel.  EffError  "<<" hline "<<endl;
  
  cout<<" No cut      &   "<<left<< setw(7)<< counter[k][0]<<"     &   "<<fixed<< std::setprecision(3)<< TotEff[k][0]<<"         &     "<< RelEff[k][0]<<"           &   "<<left<< setw(7)<< TotEffErr[k][0]<<"      &   "<< RelEffErr[k][0]<<" hline "<<endl;         
  cout<<" is1GenMu17  &   "<<left<< setw(7)<< counter[k][1]<<"    &    "<<left<< setw(7)<< TotEff[k][1]<<"      &        "<<left<< setw(7)<<  RelEff[k][1]<<"    &    "<<fixed<<std::setprecision(3)<< TotEffErr[k][1]<<" &   "<<left<< setw(7)<<  RelEffErr[k][1]<<" hline "<<endl;
  cout<<" is2GenMu8   &   "<<left<< setw(7)<< counter[k][2]<<"    &    "<<left<< setw(7)<< TotEff[k][2]<<"      &        "<<left<< setw(7)<<  RelEff[k][2]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][2]<<" & "<<left<< setw(7)<< RelEffErr[k][2]<<" hline "<<endl;
  cout<<" is3GenMu8   &   "<<left<< setw(7)<< counter[k][3]<<"    &    "<<left<< setw(7)<< TotEff[k][3]<<"      &        "<<left<< setw(7)<<  RelEff[k][3]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][3]<<" & "<<left<< setw(7)<<  RelEffErr[k][3]<<" hline "<<endl;
  cout<<" is4GenMu8   &   "<<left<< setw(7)<< counter[k][4]<<"    &    "<<left<< setw(7)<< TotEff[k][4]<<"      &        "<<left<< setw(7)<<  RelEff[k][4]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][4]<<" & "<<left<< setw(7)<<  RelEffErr[k][4]<<" hline "<<endl;
  
  cout<<" Lxy<9.8 AND Lz<48.5 & "<<left<< setw(7)<< counter[k][5]<<"  &  "<<left<< setw(7)<<  TotEff[k][5]<<"     &     "<<left<< setw(7)<<  RelEff[k][5]<<"       &    "<<fixed<<std::setprecision(4) << TotEffErr[k][5]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[k][5]<<" hline "<<endl;
  cout<<"                                                                          "<<" hline "<<endl;
  
  cout<<" is1SelMu17   &    "<<left<< setw(7)<< counter[k][6]<<"  &    "<<left<< setw(7)<< TotEff[k][6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[k][6]<<"  &    "<<left<< setw(7)<<  TotEffErr[k][6]<<" &  " <<  RelEffErr[k][6]<<" hline "<<endl;
  cout<< setprecision(3);
  cout<<" is2SelMu8    &    "<< counter[k][7]<<"  &    "<< TotEff[k][7] <<setw(10)<<"   &   "<< RelEff[k][7]<<"   &   "<< TotEffErr[k][7]<<"  & "<< RelEffErr[k][7]<<" hline "<<endl;                                
  cout<<" is3SelMu8    &    "<< counter[k][8]<<"  &    "<< TotEff[k][8]<<"   &    "<< RelEff[k][8]<<"   &   "<< TotEffErr[k][8]<<" &  "<< RelEffErr[k][8]<<" hline "<<endl;
  cout<<" is4SelMu8    &    "<< counter[k][9]<<"  &    "<< TotEff[k][9]<<"   &    "<< RelEff[k][9]<<"   &   "<< TotEffErr[k][9]<<" &  "<< RelEffErr[k][9]<<" hline "<<endl;   
  cout<<"                                                                        "<<" hline "<<endl;
  cout<<" isVertexOK            &  "<< counter[k][10]<<"  &    "<< TotEff[k][10]<<" &    "<< RelEff[k][10]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][10]<<" &  "<< RelEffErr[k][10]<<" hline "<<endl;  
  cout<<" is2MuJets            &  "<< counter[k][11]<<"  &    "<< TotEff[k][11]<<" &    "<< RelEff[k][11]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][11]<<" &  "<< RelEffErr[k][11]<<" hline "<<endl;  
  cout<<" is2dimuon            &  "<< counter[k][12]<<"  &    "<< TotEff[k][12]<<" &    "<< RelEff[k][12]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][12]<<" &  "<< RelEffErr[k][12]<<" hline "<<endl;  
  
  cout<<" is2DiMuonsPixHitOk  &  "<< counter[k][13]<<"  &    "<< TotEff[k][13]<<" &     "<< RelEff[k][13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][13]<<" hline "<<endl;                                
  cout<<" is2DiMuonsFittedDz    &  "<< counter[k][14]<<"  &    "<< TotEff[k][14]<<" &     "<< RelEff[k][14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][14]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][14]<<" hline "<<endl;                              
  cout<<" is2DiMuonsMassOK   &  "<< counter[k][15]<<"  &    "<< TotEff[k][15]<<" &     "<< RelEff[k][15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][15]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][15]<<" hline "<<endl;
  cout<<" is2DiMuonsIsoTkOK    &  "<< counter[k][16] <<" &    "<< TotEff[k][16]<<" &     "<< RelEff[k][16]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][16]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][16]<<" hline "<<endl;                          
  cout<<" is2DiMuonsHLT   &  "<< counter[k][17] <<" &    "<< TotEff[k][17]<<" &     "<< RelEff[k][17]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][17]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][17]<<" hline "<<endl;                                   
  
  cout
    <<"                                                           "<<" hline "<<endl;
  cout<<" epsilon\\_rec/alpha\\_gen  & "<< epsvsalph[k]<<"$\\pm$ "<< Err[k]<<" hline "<<endl;
  cout<<"end{tabular}"<<endl;
  cout<<"end{table}"<<endl;
  //  cout<<"end{landscape}"<<endl;

 std::cout<<"Loop ends with k as "<<k<<endl;
  
}
//  Float_t ctau1[15]={0,0.2,0.5,2.0,5.0};
//   Float_t ctauerr1[15]={0.0};
  
//   TGraphErrors *epsvsalp1 = new TGraphErrors(5,ctau1,epsvsalph,ctauerr1,Error);
  
//   TH2F *dummy = new TH2F("dummy","",100,-0.1,5.1,100,0.0,1.0);
  
//   TAxis *yaxis = epsvsalp1->GetYaxis();
//   yaxis->SetLimits(0.0,1.0);

//   //second graph 
//   Float_t ctau2[9]={0,0.05,0.1,0.1,0.5,1.0,2.0,3.0,5.0};
//   Float_t ctauerr2[9]={0.0};
//   Float_t Error2[9]={0.0};

//   for(int m=0;m<9;m++){
//     Error2[m] = Error[m+5];
//     epsvsalph2[m] = epsvsalph[m+5];
//   }
  
 //  TGraphErrors *epsvsalp2 = new TGraphErrors(9,ctau2,epsvsalph2,ctauerr2,Error2);
  
//   TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
//   leg->SetHeader("Mass","C");
//   leg->AddEntry(epsvsalp1,"Mass = 0.7 GeV", "pl");
//   leg->AddEntry(epsvsalp2,"Mass = 0.25 GeV", "pl");

//   TCanvas *c = new TCanvas("c","c",800,600); 
//   dummy->GetYaxis()->SetTitle("#epsilon/#alpha");
//   dummy->GetXaxis()->SetTitle("c#tau[mm]");
//   dummy->Draw();
//   epsvsalp1->SetMarkerStyle(20);
//   epsvsalp1->SetMarkerSize(1.2);
//   epsvsalp2->SetMarkerStyle(20);
//   epsvsalp2->SetMarkerSize(1.2);
//   epsvsalp2->SetLineColor(kRed);
//   epsvsalp2->SetMarkerColor(kRed);
  
//   epsvsalp1->Draw("PL");
//   epsvsalp2->Draw("PLSAME");
//   leg->Draw("SAME");

 

void analysis(const std::string txtfile)
{
 
setup();
std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
// // cout << "Vector Created" << endl;                                                
readTextFileWithSamples(txtfile, DarkSUSY_mH_125_mGammaD_v);
// // cout << "Samples read" << endl;                                                  
for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency(v);
// // cout << "For Loop completes" << endl;        

}

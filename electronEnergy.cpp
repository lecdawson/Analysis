void electronEnergy()
{
  string filename_tl="/home/vagrant/PhD/PhDYear3/Background/Tl208_Foils/ThibaudStudy/1E6Sample/sensitivity.root";
  string filename_bi_bulk="/home/vagrant/PhD/PhDYear3/Background/Bi214_Foils/ThibaudStudy/1E6Sample/sensitivity.root";
  string filename_bi_surf="/home/vagrant/PhD/PhDYear3/Background/Bi214_Surface/ThibaudStudy/1E6Sample/sensitivity.root";
  string filename_bi_wire="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/ThibaudStudy/1E6Sample/sensitivity.root";
  TFile *file_tl=new TFile(filename_tl.c_str());
  TFile *file_bi_bulk=new TFile(filename_bi_bulk.c_str());
  TFile *file_bi_surf=new TFile(filename_bi_surf.c_str());
  TFile *file_bi_wire=new TFile(filename_bi_wire.c_str());
  TTree *tree_tl=(TTree*)file_tl->Get("Sensitivity");
  TTree *tree_bi_bulk=(TTree*)file_bi_bulk->Get("Sensitivity");
  TTree *tree_bi_surf=(TTree*)file_bi_surf->Get("Sensitivity");
  TTree *tree_bi_wire=(TTree*)file_bi_wire->Get("Sensitivity");


  int entriesTl=tree_tl->GetEntries();
  int entriesBiBulk=tree_bi_bulk->GetEntries();
  int entriesBiSurf=tree_bi_surf->GetEntries();
  int entriesBiWire=tree_bi_wire->GetEntries();

  TH1D *h_tl = new TH1D("h_tl", "h_tl", 150, 0, 5.5);
  TH1D *h_total = new TH1D("h_total", "h_total", 150, 0, 5.5);
  TH1D *h_bulk = new TH1D("h_bulk", "h_bulk", 150, 0, 5.5);
  TH1D *h_surf = new TH1D("h_surf", "h_surf", 150, 0, 5.5);
  TH1D *h_wire = new TH1D("h_wire", "h_wire", 150, 0, 5.5);
  h_tl->SetTitle("Energy of electron, {}^{208}Tl bulk and {}^{214}Bi all areas, 1E6");
  h_bulk->SetTitle("Energy of electron, {}^{214}Bi bulk of source foil, 1E6");
  h_surf->SetTitle("Energy of electron, {}^{214}Bi surface of source foil, 1E6");
  h_wire->SetTitle("Energy of electron, {}^{214}Bi tracker wires, 1E6");
  h_tl->GetXaxis()->SetTitle("Electron energy (MeV)");
  h_bulk->GetXaxis()->SetTitle("Electron energy (MeV)");
  h_surf->GetXaxis()->SetTitle("Electron energy (MeV)");
  h_wire->GetXaxis()->SetTitle("Electron energy (MeV)");
  h_tl->GetYaxis()->SetTitle("Number of events /0.037 MeV, area normalised to 1");
  h_bulk->GetYaxis()->SetTitle("Number of events");
  h_surf->GetYaxis()->SetTitle("Number of events");
  h_wire->GetYaxis()->SetTitle("Number of events");

  h_tl->SetLineColor(kBlack);
  h_total->SetLineColor(kRed);
  h_bulk->SetLineColor(kRed);
  h_surf->SetLineColor(kMagenta);
  h_wire->SetLineColor(kBlue);

  TCanvas *c1 =new TCanvas("snemo1","snemo1",900,600);
  gStyle->SetOptStat(000000);
  c1->SetLogy();
  //h_tl->SetMinimum(0.1);
  //h_tl->SetMaximum(10000);

  bool topology_1engamma=0;
  int alpha_count=0;
  int number_of_electrons=0;
  int number_of_gammas=0;
  vector<int> *electron_charges=0;
  vector<double> *electron_energies=0;
  vector<bool> *electronsFromFoil=0;

  tree_tl->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_tl->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_tl->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_tl->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_tl->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_tl->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_tl->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_bulk->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_bulk->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_bulk->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_bulk->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_bulk->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_bulk->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_bulk->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_surf->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_surf->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_surf->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_surf->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_surf->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_surf->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_surf->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_wire->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_wire->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_wire->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_wire->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_wire->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_wire->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_wire->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  //For thalium
  for(int entry=0; entry<entriesTl; entry++){
    tree_tl->GetEntry(entry);
    if(topology_1engamma){
      if(alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5){
          h_tl->Fill(electron_energies->at(0));
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_tl->Fill(electron_energies->at(0));
    //   }
    // }
  }

  //For bismuth
  for(int entry=0; entry<entriesBiBulk; entry++){
    tree_bi_bulk->GetEntry(entry);
    if(topology_1engamma){
      if(alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5){
          h_bulk->Fill(electron_energies->at(0));
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_bulk->Fill(electron_energies->at(0));
    //   }
    // }
  }
  for(int entry=0; entry<entriesBiSurf; entry++){
    tree_bi_surf->GetEntry(entry);
    if(topology_1engamma){
      if(alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5){
          h_surf->Fill(electron_energies->at(0));
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_surf->Fill(electron_energies->at(0));
    //   }
    // }
  }
  for(int entry=0; entry<entriesBiWire; entry++){
    tree_bi_wire->GetEntry(entry);
    if(topology_1engamma){
      if(alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5){
          h_wire->Fill(electron_energies->at(0));
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_wire->Fill(electron_energies->at(0));
    //   }
    // }
  }

  //Scale the histograms
  Double_t scale = 1/h_tl->Integral();
  h_tl->Scale(scale);
  Double_t scale1 = 1/h_bulk->Integral();
  h_bulk->Scale(scale1);
  Double_t scale2 = 1/h_surf->Integral();
  h_surf->Scale(scale2);
  Double_t scale3 = 1/h_wire->Integral();
  h_wire->Scale(scale3);

  // h_total->Add(h_bulk);
  // h_total->Add(h_surf);
  // h_total->Add(h_wire);

  h_tl->Draw("hist");
  //h_total->Draw("hist same");
  h_bulk->Draw("hist same");
  h_surf->Draw("hist same");
  h_wire->Draw("hist same");

  // TLine *energyCut = new TLine(0.5,0,0.5,25000);
  // energyCut->SetLineColor(kBlack);
  // energyCut->SetLineStyle(2);
  // energyCut->Draw("same");

  TLegend *leg = new TLegend(0.5,0.7,0.79,0.79);
  leg->AddEntry(h_tl,"{}^{208}Tl 1eN#gamma (N>0)","l");
  //leg->AddEntry(h_total,"{}^{214}Bi all generators 1eN#gamma (N>0)","l");
  leg->AddEntry(h_bulk,"{}^{214}Bi bulk of the foil 1eN#gamma (N>0)","l");
  leg->AddEntry(h_surf,"{}^{214}Bi surface of the foil 1eN#gamma (N>0)","l");
  leg->AddEntry(h_wire,"{}^{214}Bi tracker wires 1eN#gamma (N>0)","l");
  leg->Draw("same");

}

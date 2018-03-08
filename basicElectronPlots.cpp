void basicElectronPlots()
{
  //Below is just for events from the foil
  //Read in all of the sensitivity files for different generators
  string foils="/home/vagrant/PhD/PhDYear3/Background/Bi214_Foils/ThibaudStudy/1E6Sample/sensitivity.root";
  string surface="/home/vagrant/PhD/PhDYear3/Background/Bi214_Surface/ThibaudStudy/1E6Sample/sensitivity.root";
  string wires="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/ThibaudStudy/1E6Sample/sensitivity.root";

  TFile *file1=new TFile(foils.c_str());
  TFile *file2=new TFile(surface.c_str());
  TFile *file3=new TFile(wires.c_str());
  TTree *treeFoil=(TTree*)file1->Get("Sensitivity");
  TTree *treeSurf=(TTree*)file2->Get("Sensitivity");
  TTree *treeWire=(TTree*)file3->Get("Sensitivity");

  int entriesFoil=treeFoil->GetEntries();
  int entriesSurf=treeSurf->GetEntries();
  int entriesWire=treeWire->GetEntries();

  TH1F *h1 = new TH1F("h1", "h1", 170, 0, 3.4);
  TH1F *h2 = new TH1F("h2", "h2", 170, 0, 3.4);
  TH1F *h3 = new TH1F("h3", "h3", 170, 0, 3.4);
  h1->SetTitle("Energy spectrum of electrons, Bi214, 1E6 events all generators");
  h1->GetYaxis()->SetTitle("Number of events");
  h1->GetXaxis()->SetTitle("Energy [MeV]");

  h1->SetLineColor(kGray+2);
  h2->SetLineColor(kBlue-3);
  h3->SetLineColor(kRed);

  vector<double> *electron_energies=0;
  vector<int> *electron_hit_counts=0;
  vector<double> *electron_track_lengths=0;
  vector<bool> *electron_hits_main_wall=0;
  vector<int> *electron_charges=0;
  vector<bool> *electronsFromFoil=0;
  int number_of_electrons=0;

  treeFoil->SetBranchAddress("reco.electron_energies", &electron_energies);
  treeFoil->SetBranchAddress("reco.electron_track_lengths", &electron_track_lengths);
  treeFoil->SetBranchAddress("reco.electron_hit_counts", &electron_hit_counts);
  treeFoil->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  treeFoil->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeFoil->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeFoil->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);

  treeSurf->SetBranchAddress("reco.electron_energies", &electron_energies);
  treeSurf->SetBranchAddress("reco.electron_track_lengths", &electron_track_lengths);
  treeSurf->SetBranchAddress("reco.electron_hit_counts", &electron_hit_counts);
  treeSurf->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  treeSurf->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeSurf->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeSurf->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);

  treeWire->SetBranchAddress("reco.electron_energies", &electron_energies);
  treeWire->SetBranchAddress("reco.electron_track_lengths", &electron_track_lengths);
  treeWire->SetBranchAddress("reco.electron_hit_counts", &electron_hit_counts);
  treeWire->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  treeWire->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeWire->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeWire->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);

  for(int entry = 0; entry < entriesFoil; entry++){
    treeFoil->GetEntry(entry);
    if(number_of_electrons >0){
      for(int electron=0; electron<number_of_electrons; electron++){
        if(electronsFromFoil->at(electron)==1 && electron_hits_main_wall->at(electron)==1 && electron_charges->at(electron)==8){
          h1->Fill(electron_energies->at(electron));
        }
      }
    }
  }
  for(int entry = 0; entry < entriesSurf; entry++){
    treeSurf->GetEntry(entry);
    if(number_of_electrons >0){
      for(int electron=0; electron<number_of_electrons; electron++){
        if(electronsFromFoil->at(electron)==1 && electron_hits_main_wall->at(electron)==1 && electron_charges->at(electron)==8){
          h2->Fill(electron_energies->at(electron));
        }
      }
    }
  }
  for(int entry = 0; entry < entriesWire; entry++){
    treeWire->GetEntry(entry);
    if(number_of_electrons >0){
      for(int electron=0; electron<number_of_electrons; electron++){
        if(electronsFromFoil->at(electron)==1 && electron_hits_main_wall->at(electron)==1 && electron_charges->at(electron)==8){
          h3->Fill(electron_energies->at(electron));
        }
      }
    }
  }

  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");

  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
  leg->SetFillColor(0);
  leg->AddEntry(h1,"{}^{214}Bi Bulk","l");
  leg->AddEntry(h2,"{}^{214}Bi Surface","l");
  leg->AddEntry(h3,"{}^{214}Bi Tracker","l");
  leg->Draw("same");

}

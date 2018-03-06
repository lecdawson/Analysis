void basicAlphaPlots()
{
  //Below is just for events from the foil
  //Read in all of the sensitivity files for different generators
  string foils="/home/vagrant/PhD/PhDYear3/Background/Bi214_Foils/ThibaudStudy/3E5Sample/ConfigChange/sensitivity.root";
  string surface="/home/vagrant/PhD/PhDYear3/Background/Bi214_Surface/ThibaudStudy/3E5Sample/ConfigChange/sensitivity.root";
  string wires="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/ThibaudStudy/3E5Sample/ConfigChange/sensitivity.root";

  TFile *file1=new TFile(foils.c_str());
  TFile *file2=new TFile(surface.c_str());
  TFile *file3=new TFile(wires.c_str());
  TTree *treeFoil=(TTree*)file1->Get("Sensitivity");
  TTree *treeSurf=(TTree*)file2->Get("Sensitivity");
  TTree *treeWire=(TTree*)file3->Get("Sensitivity");

  int entriesFoil=treeFoil->GetEntries();
  int entriesSurf=treeSurf->GetEntries();
  int entriesWire=treeWire->GetEntries();

  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 1000);
  TH1F *h2 = new TH1F("h2", "h2", 100, 0, 1000);
  TH1F *h3 = new TH1F("h3", "h3", 100, 0, 1000);
  h2->SetTitle("Track length of alphas, Bi214, 3E5 events from all generators");
  h2->GetYaxis()->SetTitle("Number of events");
  h2->GetXaxis()->SetTitle("Length [mm]");

  h1->SetLineColor(kGray+2);
  h2->SetLineColor(kBlue-3);
  h3->SetLineColor(kRed);

  vector<double> *delayed_track_time=0;
  vector<bool> *alphas_from_foil=0;
  int alpha_count=0;
  int foil_alpha_count=0;
  vector<double> *alpha_vertex_x=0;
  double alpha_track_length=0;
  int delayed_cluster_hit_count=0;
  double proj_track_length_alpha=0;
  double alpha_delay_time=0;

  treeFoil->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeFoil->SetBranchAddress("reco.delayed_track_time", &delayed_track_time);
  treeFoil->SetBranchAddress("reco.alpha_count", &alpha_count);
  treeFoil->SetBranchAddress("reco.foil_alpha_count", &foil_alpha_count);
  treeFoil->SetBranchAddress("reco.alpha_vertex_x", &alpha_vertex_x);
  treeFoil->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeFoil->SetBranchAddress("reco.delayed_cluster_hit_count", &delayed_cluster_hit_count);
  treeFoil->SetBranchAddress("reco.proj_track_length_alpha", &proj_track_length_alpha);

  treeSurf->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeSurf->SetBranchAddress("reco.delayed_track_time", &delayed_track_time);
  treeSurf->SetBranchAddress("reco.alpha_count", &alpha_count);
  treeSurf->SetBranchAddress("reco.foil_alpha_count", &foil_alpha_count);
  treeSurf->SetBranchAddress("reco.alpha_vertex_x", &alpha_vertex_x);
  treeSurf->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeSurf->SetBranchAddress("reco.delayed_cluster_hit_count", &delayed_cluster_hit_count);
  treeSurf->SetBranchAddress("reco.proj_track_length_alpha", &proj_track_length_alpha);

  treeWire->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeWire->SetBranchAddress("reco.delayed_track_time", &delayed_track_time);
  treeWire->SetBranchAddress("reco.alpha_count", &alpha_count);
  treeWire->SetBranchAddress("reco.foil_alpha_count", &foil_alpha_count);
  treeWire->SetBranchAddress("reco.alpha_vertex_x", &alpha_vertex_x);
  treeWire->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeWire->SetBranchAddress("reco.delayed_cluster_hit_count", &delayed_cluster_hit_count);
  treeWire->SetBranchAddress("reco.proj_track_length_alpha", &proj_track_length_alpha);

  for(int entry = 0; entry < entriesFoil; entry++){
    treeFoil->GetEntry(entry);
    if(alpha_count >0){
      for(int alpha=0; alpha<alpha_count; alpha++){
        if(alphas_from_foil->at(alpha)==1){
          //alpha_delay_time=(delayed_track_time->at(alpha))/1000;
          h1->Fill(alpha_track_length);
        }
      }
    }
  }
  for(int entry = 0; entry < entriesSurf; entry++){
    treeSurf->GetEntry(entry);
    if(alpha_count >0){
      for(int alpha=0; alpha<alpha_count; alpha++){
        if(alphas_from_foil->at(alpha)==1){
          //alpha_delay_time=(delayed_track_time->at(alpha))/1000;
          h2->Fill(alpha_track_length);
        }
      }
    }
  }
  for(int entry = 0; entry < entriesWire; entry++){
    treeWire->GetEntry(entry);
    if(alpha_count >0){
      for(int alpha=0; alpha<alpha_count; alpha++){
        if(alphas_from_foil->at(alpha)==1){
          //alpha_delay_time=(delayed_track_time->at(alpha))/1000;
          h3->Fill(alpha_track_length);
        }
      }
    }
  }

  h2->Draw();
  h1->Draw("same");
  h3->Draw("same");

  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
  leg->SetFillColor(0);
  leg->AddEntry(h1,"{}^{214}Bi Bulk","l");
  leg->AddEntry(h2,"{}^{214}Bi Surface","l");
  leg->AddEntry(h3,"{}^{214}Bi Tracker","l");
  leg->Draw("same");

}

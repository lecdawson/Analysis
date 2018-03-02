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
  TH1F *h2 = new TH1F("h2", "h2", 50, 0, 500);
  TH1F *h3 = new TH1F("h3", "h3", 50, 0, 500);
  h1->SetTitle("Track length of alphas, Bi214, 3E5 events surface of source foil");
  h1->GetYaxis()->SetTitle("Number of events");
  h1->GetXaxis()->SetTitle("Length [mm]");

  h1->SetLineColor(kBlack);

  vector<double> *delayed_track_time=0;
  vector<bool> *alphas_from_foil=0;
  int alpha_count=0;
  int foil_alpha_count=0;
  vector<double> *alpha_vertex_x=0;
  double alpha_track_length=0;
  int delayed_cluster_hit_count=0;
  double proj_track_length_alpha=0;

  treeSurf->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeSurf->SetBranchAddress("reco.delayed_track_time", &delayed_track_time);
  treeSurf->SetBranchAddress("reco.alpha_count", &alpha_count);
  treeSurf->SetBranchAddress("reco.foil_alpha_count", &foil_alpha_count);
  treeSurf->SetBranchAddress("reco.alpha_vertex_x", &alpha_vertex_x);
  treeSurf->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeSurf->SetBranchAddress("reco.delayed_cluster_hit_count", &delayed_cluster_hit_count);
  treeSurf->SetBranchAddress("reco.proj_track_length_alpha", &proj_track_length_alpha);

  for(int entry = 0; entry < entriesSurf; entry++)
  {
    treeSurf->GetEntry(entry);
    if(alpha_count >0){
      for(int alpha=0; alpha<alpha_count; alpha++){
        if(alphas_from_foil->at(alpha)==1){
          h1->Fill(alpha_track_length);
        }
      }
    }
  }

  h1->Draw();

}

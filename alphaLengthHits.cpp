void alphaLengthHits()
{
  string wires="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/ThibaudStudy/3E5Sample/ConfigChange/sensitivity.root";

  TFile *file1=new TFile(wires.c_str());
  TTree *treeWire=(TTree*)file1->Get("Sensitivity");

  int entriesWire=treeWire->GetEntries();
  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 500);
  TH1F *h2 = new TH1F("h2", "h2", 100, 0, 500);
  TH1F *h3 = new TH1F("h3", "h3", 100, 0, 500);

  h3->SetTitle("Alpha track lengths Bi214, 3E5 1e1a wires, cut at 10 #mus, xy distance 40 cm");
  h3->GetYaxis()->SetTitle("Number of events");
  h3->GetXaxis()->SetTitle("Alpha length (mm)");

  h1->SetLineColor(kGray+2);
  h2->SetLineColor(kBlue-3);
  h3->SetLineColor(kRed);

  bool topology_1e1alpha=0;
  vector<bool> *alphas_from_foil=0;
  vector<bool> *electron_hits_main_wall=0;
  vector<int> *electron_charges=0;
  vector<bool> *electronsFromFoil=0;
  double alpha_track_length=0;
  int delayed_cluster_hit_count=0;

  treeWire->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  treeWire->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeWire->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeWire->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  treeWire->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeWire->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeWire->SetBranchAddress("reco.delayed_cluster_hit_count", &delayed_cluster_hit_count);

  for(int entry=0; entry<entriesWire; entry++){
    treeWire->GetEntry(entry);
    if(topology_1e1alpha){
      if(electronsFromFoil->at(0)==1 && electron_hits_main_wall->at(0)==1 && electron_charges->at(0)==8 && alphas_from_foil->at(0)==1){
          if(delayed_cluster_hit_count==1){
            h1->Fill(alpha_track_length);
          }
          else if(delayed_cluster_hit_count==2){
            h2->Fill(alpha_track_length);
          }
          else if(delayed_cluster_hit_count>2){
            h3->Fill(alpha_track_length);
          }
      }
    }
  }

  h3->Draw();
  h2->Draw("same");
  h1->Draw("same");

  TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
  leg->SetFillColor(0);
  leg->AddEntry(h1,"1 hit","l");
  leg->AddEntry(h2,"2 hits","l");
  leg->AddEntry(h3,">2 hits","l");
  leg->Draw("same");


}

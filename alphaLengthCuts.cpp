void alphaLengthCuts()
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

  TCanvas *c1= new TCanvas;
  TH1F *h1 = new TH1F("h1", "h1", 50, 0, 500);
  TH1F *h2 = new TH1F("h2", "h2", 50, 0, 500);
  TH1F *h3 = new TH1F("h3", "h3", 50, 0, 500);
  TH1F *h_total = new TH1F("h_total", "h_total", 50, 0, 500);
  TH1F *data = new TH1F("data", "data", 50, 0, 500);
  h3->SetTitle("Alpha track lengths Bi214, 3E5 1e1a wires, cut at 10 #mus, xy distance 40 cm");
  h3->GetYaxis()->SetTitle("Number of events");
  h3->GetXaxis()->SetTitle("Alpha length (mm)");
  h_total->SetTitle("Reference activity - source selection, 1e1a 3E5 events");
  h_total->GetYaxis()->SetTitle("");
  h_total->GetXaxis()->SetTitle("Alpha length (mm)");

  h1->SetLineColor(kRed);
  h1->SetFillColor(kRed);
  h1->SetFillStyle(3002);
  h2->SetLineColor(kGreen);
  h2->SetFillColor(kGreen);
  h2->SetFillStyle(3002);
  h3->SetLineColor(kBlue);
  h3->SetFillColor(kBlue);
  h3->SetFillStyle(3002);
  h_total->SetLineColor(kBlack);


  //All of the variables to be used for cuts and selections when looking at 1e1a from the source foil
  //An electron must:
  // - have come from the source foil
  // - hit the main calo wall
  // - have negative curvature
  //An alpha must:
  // - be delayed
  // - come from the source foil
  // - not hit a calo

  bool topology_1e1alpha=0;
  vector<bool> *alphas_from_foil=0;
  vector<bool> *electron_hits_main_wall=0;
  vector<int> *electron_charges=0;
  vector<bool> *electronsFromFoil=0;
  double alpha_track_length=0;

  treeFoil->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  treeFoil->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeFoil->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeFoil->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  treeFoil->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeFoil->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeSurf->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  treeSurf->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeSurf->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeSurf->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  treeSurf->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeSurf->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);
  treeWire->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  treeWire->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeWire->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeWire->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  treeWire->SetBranchAddress("reco.alpha_track_length", &alpha_track_length);
  treeWire->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);

  for(int entry=0; entry<entriesFoil; entry++){
    treeFoil->GetEntry(entry);
    if(topology_1e1alpha){
      if(electronsFromFoil->at(0)==1 && electron_hits_main_wall->at(0)==1 && electron_charges->at(0)==8 && alphas_from_foil->at(0)==1){
          h1->Fill(alpha_track_length);
      }
    }
  }
  for(int entry=0; entry<entriesSurf; entry++){
    treeSurf->GetEntry(entry);
    if(topology_1e1alpha){
      if(electronsFromFoil->at(0)==1 && electron_hits_main_wall->at(0)==1 && electron_charges->at(0)==8 && alphas_from_foil->at(0)==1){
          h2->Fill(alpha_track_length);
      }
    }
  }
  for(int entry=0; entry<entriesWire; entry++){
    treeWire->GetEntry(entry);
    if(topology_1e1alpha){
      if(electronsFromFoil->at(0)==1 && electron_hits_main_wall->at(0)==1 && electron_charges->at(0)==8 && alphas_from_foil->at(0)==1){
          h3->Fill(alpha_track_length);
      }
    }
  }

  //normalise the histograms, scaling by activity
  double activity_foil=0.0154;
  double activity_surf=0.00018;
  double activity_wire=0.0455;
  double number_of_entries_foil = h1->GetEntries();
  double number_of_entries_surf = h2->GetEntries();
  double number_of_entries_wire = h3->GetEntries();
  double bin_width=10;
  double h1_scale = (activity_foil/(h1->Integral()));
  double h2_scale = (activity_surf/(h2->Integral()));
  double h3_scale = (activity_wire/(h3->Integral()));

  h1->Scale(h1_scale);
  h2->Scale(h2_scale);
  h3->Scale(h3_scale);

  double exposure=60;
  double exposure_in_seconds=exposure*24*60*60;

  h_total->Add(h1);
  h_total->Add(h2);
  h_total->Add(h3);

  h_total->Scale(exposure_in_seconds);
  //h_total->Draw("hist");

  data->SetMarkerStyle(20);
  data->SetMarkerSize(0.7);

  // Now need to generate sudo data from these histograms
  // Use GetRandom n times, where n is a randomly generated number of events
  // based on poissonian law.
  TRandom *eventGenerator = new TRandom3();
  int random_number_of_entries = eventGenerator->Poisson(30000);
  for(int n=0; n<random_number_of_entries; n++){
       data->Fill(h_total->GetRandom());
     }

  // Test TFractionFitter
  TObjArray *mc = new TObjArray(3);
  //Scale indvidual templates
  h1->Scale(exposure_in_seconds);
  h2->Scale(exposure_in_seconds);
  h3->Scale(exposure_in_seconds);
  mc->Add(h1);
  mc->Add(h2);
  mc->Add(h3);
  double value[3];
  double error[3];
  TH1D* lengthcontrib[3];
  TH1D* fitresult;

  TFractionFitter* fit = new TFractionFitter(data, mc);
  Int_t status = fit->Fit();
  std::cout << "fit status: " << status << std::endl;
  if (status == 0) {                       // check on fit status
     fitresult = (TH1D*) fit->GetPlot();
     for (int i=0; i<3; i++){
         fit -> GetResult(i,value[i],error[i]);
         lengthcontrib[i] = (TH1D*)fit -> GetMCPrediction(i);
         lengthcontrib[i] -> Scale( (value[i]*data->Integral()) / (lengthcontrib[i]->Integral()) );
     }
     data->Draw("Ep");
     fitresult->Draw("same");
     fitresult->SetLineColor(kBlack);
     lengthcontrib[2]->SetLineColor(kRed);
     lengthcontrib[2]->SetFillColor(kRed);
     lengthcontrib[2]->SetFillStyle(3002);
     lengthcontrib[0]->SetLineColor(kGray+2);
     lengthcontrib[0]->SetFillColor(kGray+2);
     lengthcontrib[0]->SetFillStyle(3002);
     lengthcontrib[1]->SetLineColor(kBlue-3);
     lengthcontrib[1]->SetFillColor(kBlue-3);
     lengthcontrib[1]->SetFillStyle(3002);
     lengthcontrib[2]->Draw("hist same");
     lengthcontrib[0]->Draw("hist same");
     lengthcontrib[1]->Draw("hist same");
     data->SetTitle("Pseudo-experiment with three contributions after 60 day exposure");
     data->GetXaxis()->SetTitle("Alpha Lengths [mm]");
   }

   TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
   leg->SetFillColor(0);
   leg->AddEntry(data,"Data","lep");
   leg->AddEntry(fitresult,"Fit Result","l");
   leg->AddEntry(lengthcontrib[0],"Scaled {}^{214}Bi Bulk","f");
   leg->AddEntry(lengthcontrib[1],"Scaled {}^{214}Bi Surface","f");
   leg->AddEntry(lengthcontrib[2],"Scaled {}^{214}Bi Tracker","f");
   leg->Draw("same");
  // for(int pseudo; pseudo<100; pseudo++){
  //   int number_of_entries = 0;
  //   int random_number_of_entries = eventGenerator->Poisson(30000);
  //   std::cout << "Number of entries: " << random_number_of_entries << std::endl;
  //   for(int n=0; n<random_number_of_entries; n++){
  //     data->Fill(h_total->GetRandom());
  //   }
  // }


}

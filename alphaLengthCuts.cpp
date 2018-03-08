void alphaLengthCuts()
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

  TCanvas *c1= new TCanvas;
  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 500);
  TH1F *h2 = new TH1F("h2", "h2", 100, 0, 500);
  TH1F *h3 = new TH1F("h3", "h3", 100, 0, 500);
  TH1F *h_total = new TH1F("h_total", "h_total", 100, 0, 500);
  TH1F *data = new TH1F("data", "data", 100, 0, 500);
  TH1F *fitted_activity_bulk = new TH1F("fitted_activity_bulk", "fitted_activity_bulk", 100, 0.005, 0.03);
  TH1F *fitted_activity_surf = new TH1F("fitted_activity_surf", "fitted_activity_surf", 100, 0.04, 0.8);
  TH1F *fitted_activity_wire = new TH1F("fitted_activity_wire", "fitted_activity_wire", 100, 0.02, 0.07);
  data->SetTitle("Pseudo-experiment with three contributions after 60 day exposure");
  data->GetXaxis()->SetTitle("#alpha track length (mm)");
  data->GetYaxis()->SetTitle("Events/(5)");
  h1->SetTitle("Alpha track lengths Bi214, 1E6 1e1a field wires,10 #mus, xy 40 cm");
  h1->GetYaxis()->SetTitle("Number of events");
  h1->GetXaxis()->SetTitle("Alpha length (mm)");
  h_total->SetTitle("Reference activity - source selection, 1e1a 1E6 events");
  h_total->GetYaxis()->SetTitle("(s^{-1})");
  h_total->GetXaxis()->SetTitle("Alpha length (mm)");
  fitted_activity_bulk->SetTitle("Fitted activity - source bulk");
  fitted_activity_surf->SetTitle("Fitted activity - source surf");
  fitted_activity_wire->SetTitle("Fitted activity - source wire");
  fitted_activity_bulk->GetXaxis()->SetTitle("Activity (Bq)");
  fitted_activity_surf->GetXaxis()->SetTitle("Activity (Bq)");
  fitted_activity_wire->GetXaxis()->SetTitle("Activity (Bq)");

  h1->SetLineColor(kRed);
  h1->SetFillColor(kRed);
  h1->SetFillStyle(3002);
  h2->SetLineColor(kGray+2);
  h2->SetFillColor(kGray+2);
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

  int exposure=0;
  int exposure_in_seconds=0;
  int number_of_entries_bulk=0;
  int number_of_entries_surf=0;
  int number_of_entries_wire=0;
  int number_exp_bulk=0;
  int number_exp_surf=0;
  int number_exp_wire=0;
  int total_number_exp=0;
  double activity_bulk_new=0;
  double activity_surf_new=0;
  double activity_wire_new=0;
  double efficiency_bulk=0;
  double efficiency_surf=0;
  double efficiency_wire=0;
  double old_fraction_bulk=0;
  double old_fraction_surf=0;
  double old_fraction_wire=0;
  int total_number_entries=0;

  double value[3];
  double error[3];
  TH1D* h_after[3];
  TH1D* fitresult;

  double activity_bulk=0.0154;
  double activity_surf=0.00018;
  double activity_wire=0.0455;

  double h1_scale=0;
  double h2_scale=0;
  double h3_scale=0;

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
  number_of_entries_bulk = h1->GetEntries();
  number_of_entries_surf = h2->GetEntries();
  number_of_entries_wire = h3->GetEntries();
  h1_scale = (activity_bulk/1000000);
  h2_scale = (activity_surf/1000000);
  h3_scale = (activity_wire/1000000);

  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h1->Scale(h1_scale);
  h2->Scale(h2_scale);
  h3->Scale(h3_scale);

  exposure=60;
  exposure_in_seconds=exposure*24*60*60;

  //Sum the normalised histograms of the individual generators
  h_total->Add(h1);
  h_total->Add(h2);
  h_total->Add(h3);

  //Scale by the exposure which here is 60 days
  h_total->Scale(exposure_in_seconds);

  data->SetMarkerStyle(20);
  data->SetMarkerSize(0.7);

  //Calculate the old fractions by finding the expected number of entries
  // N_exp = efficiency*activity*exposure
  total_number_entries=h_total->GetEntries();
  efficiency_bulk=(double(number_of_entries_bulk)/1000000);
  efficiency_surf=(double(number_of_entries_surf)/1000000);
  efficiency_wire=(double(number_of_entries_wire)/1000000);
  number_exp_bulk=efficiency_bulk*activity_bulk*exposure_in_seconds;
  number_exp_surf=efficiency_surf*activity_surf*exposure_in_seconds;
  number_exp_wire=efficiency_wire*activity_wire*exposure_in_seconds;
  total_number_exp=number_exp_bulk+number_exp_surf+number_exp_wire;
  old_fraction_bulk=double(number_exp_bulk)/double(total_number_exp);
  old_fraction_surf=double(number_exp_surf)/double(total_number_exp);
  old_fraction_wire=double(number_exp_wire)/double(total_number_exp);

  // Now need to generate sudo data from these histograms
  // Use GetRandom n times, where n is a randomly generated number of events
  // based on poissonian law.
  TRandom *eventGenerator = new TRandom3();
  int random_number_of_entries = eventGenerator->Poisson(total_number_exp);
  for(int n=0; n<=random_number_of_entries; n++){
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

  TFractionFitter* fit = new TFractionFitter(data, mc);
  THStack *hs = new THStack("hs","Stacked 1D histograms");
  Int_t status = fit->Fit();
  std::cout << "fit status: " << status << std::endl;
  if (status == 0) {                       // check on fit status
     fitresult = (TH1D*) fit->GetPlot();
     for (int i=0; i<3; i++){
         fit -> GetResult(i,value[i],error[i]);
         h_after[i] = (TH1D*)fit -> GetMCPrediction(i);
         h_after[i] -> Scale( (value[i]*data->Integral()) / (h_after[i]->Integral()) );
     }
     data->Draw("Ep");
     fitresult->Draw("same");
     fitresult->SetLineColor(kBlack);
     h_after[2]->SetLineColor(kBlue);
     h_after[2]->SetFillColor(kBlue);
     h_after[2]->SetFillStyle(3002);
     h_after[0]->SetLineColor(kRed);
     h_after[0]->SetFillColor(kRed);
     h_after[0]->SetFillStyle(3002);
     h_after[1]->SetLineColor(kGray+2);
     h_after[1]->SetFillColor(kGray+2);
     h_after[1]->SetFillStyle(3002);
     hs->Add(h_after[0]);
     hs->Add(h_after[1]);
     hs->Add(h_after[2]);
     hs->Draw("hist same");
     //h_after[0]->Draw("hist same");
     //h_after[1]->Draw("hist same");
     //h_after[2]->Draw("hist same");

     //Calculate the new activities predicted by the fit
     activity_bulk_new = (value[0]/old_fraction_bulk)*activity_bulk;
     activity_surf_new = (value[1]/old_fraction_surf)*activity_surf;
     activity_wire_new = (value[2]/old_fraction_wire)*activity_wire;
     cout<<"New activity bulk: "<<activity_bulk_new<<endl;
     cout<<"New activity surf: "<<activity_surf_new<<endl;
     cout<<"New activity wire: "<<activity_wire_new<<endl;
   }

   TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
   leg->SetFillColor(0);
   leg->AddEntry(data,"Data","lep");
   leg->AddEntry(fitresult,"Fit Result","l");
   leg->AddEntry(h_after[0],"Scaled {}^{214}Bi Bulk","f");
   leg->AddEntry(h_after[1],"Scaled {}^{214}Bi Surface","f");
   leg->AddEntry(h_after[2],"Scaled {}^{214}Bi Tracker","f");
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

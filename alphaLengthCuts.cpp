void alphaLengthCuts()
{
  //Below is just for events from the foil
  //Read in all of the sensitivity files for different generators
  string foils="/home/vagrant/PhD/PhDYear3/Background/Bi214_Foils/Alessandro/bi214_foil_sensitivity.root";
  string surface="/home/vagrant/PhD/PhDYear3/Background/Bi214_Surface/Alessandro/bi214_surface_sensitivity.root";
  string wires="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/Alessandro/bi214_wire_sensitivity.root";

  TFile *file1=new TFile(foils.c_str());
  TFile *file2=new TFile(surface.c_str());
  TFile *file3=new TFile(wires.c_str());
  TTree *treeFoil=(TTree*)file1->Get("Sensitivity");
  TTree *treeSurf=(TTree*)file2->Get("Sensitivity");
  TTree *treeWire=(TTree*)file3->Get("Sensitivity");

  int entriesFoil=treeFoil->GetEntries();
  int entriesSurf=treeSurf->GetEntries();
  int entriesWire=treeWire->GetEntries();

  //gStyle->SetOptStat(0);

  //TCanvas *c1= new TCanvas
  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 500);
  TH1F *h2 = new TH1F("h2", "h2", 100, 0, 500);
  TH1F *h3 = new TH1F("h3", "h3", 100, 0, 500);
  TH1F *h_total = new TH1F("h_total", "h_total", 100, 0, 500);
  TH1F *fitted_activity_bulk = new TH1F("fitted_activity_bulk", "fitted_activity_bulk", 1000, 1E-6, 100E-6);
  TH1F *fitted_activity_surf = new TH1F("fitted_activity_surf", "fitted_activity_surf", 1000, 0.5E-7, 8E-6); //0.0000039
  TH1F *fitted_activity_wire = new TH1F("fitted_activity_wire", "fitted_activity_wire", 1000, 1E-5, 8E-6); //0.0000461
  h1->SetTitle("Alpha track lengths Bi214, 1E6 1e1a field wires,10 #mus, xy 40 cm");
  h1->GetYaxis()->SetTitle("Number of events");
  h1->GetXaxis()->SetTitle("Alpha length (mm)");
  h_total->SetTitle("Reference activity - source selection, 62 #muBq tracker, 0.18 mBq surface, 1.8 mBq bulk");
  h_total->GetYaxis()->SetTitle("Events s^{-1} / 5 mm");
  h_total->GetXaxis()->SetTitle("Alpha length (mm)");
  fitted_activity_bulk->SetTitle("Fitted activity - source bulk (62 #muBq input), 675 days exposure");
  fitted_activity_surf->SetTitle("Fitted activity - source surf, (0.18 mBq input) 675 days exposure");
  fitted_activity_wire->SetTitle("Fitted activity - source wire, (2.1 mBq input) 675 days exposure");
  fitted_activity_bulk->GetXaxis()->SetTitle("Activity (Bq)");
  fitted_activity_surf->GetXaxis()->SetTitle("Activity (Bq)");
  fitted_activity_wire->GetXaxis()->SetTitle("Activity (Bq)");

  h1->SetLineColor(kRed);
  // h1->SetFillColor(kRed);
  // h1->SetFillStyle(3003);
  h2->SetLineColor(kGreen+2);
  // h2->SetFillColor(kGreen+2);
  // h2->SetFillStyle(3003);
  h3->SetLineColor(kBlue);
  // h3->SetFillColor(kBlue);
  // h3->SetFillStyle(3003);
  h_total->SetLineColor(kBlack);
  fitted_activity_bulk->SetLineColor(kRed);
  fitted_activity_surf->SetLineColor(kMagenta);
  fitted_activity_wire->SetLineColor(kBlue);

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

  double activity_tracker=2.28E-3; // 2.28E-3 with flushing
  double activity_bulk=62E-6;//70E-6; //70 µBq target, 10 µBq/kg
  double activity_surf=activity_tracker*0.078; //0.178 mBq
  double activity_wire=activity_tracker*0.922; // 2.10 mBq

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
  cout<<"Number of entries bulk: "<<number_of_entries_bulk<<endl;
  number_of_entries_surf = h2->GetEntries();
  cout<<"Number of entries surf: "<<number_of_entries_surf<<endl;
  number_of_entries_wire = h3->GetEntries();
  cout<<"Number of entries wire: "<<number_of_entries_wire<<endl;
  h1_scale = (activity_bulk/1000000);
  h2_scale = (activity_surf/1000000);
  h3_scale = (activity_wire/1000000);

  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h1->Scale(h1_scale);
  h2->Scale(h2_scale);
  h3->Scale(h3_scale);

  exposure=675;
  exposure_in_seconds=exposure*24*60*60;

  //Sum the normalised histograms of the individual generators
  h_total->Add(h1);
  h_total->Add(h2);
  h_total->Add(h3);

  h_total->Draw("hist");
  h1->Draw("hist same");
  h2->Draw("hist same");
  h3->Draw("hist same");

  TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
  leg->SetFillColor(0);
  leg->AddEntry(h_total,"Combined events","l");
  leg->AddEntry(h1,"{}^{214}Bi Bulk","f");
  leg->AddEntry(h2,"{}^{214}Bi Surface","f");
  leg->AddEntry(h3,"{}^{214}Bi Tracker","f");
  leg->Draw("same");

  //Scale by the exposure which here is 180 days
  h_total->Scale(exposure_in_seconds);

  h1->Scale(exposure_in_seconds);
  h2->Scale(exposure_in_seconds);
  h3->Scale(exposure_in_seconds);

  //Calculate the old fractions by finding the expected number of entries
  // N_exp = efficiency*activity*exposure
  total_number_entries=h_total->GetEntries();
  efficiency_bulk=(double(number_of_entries_bulk)/1000000);
  cout<<"Bulk efficiency: "<<efficiency_bulk<<endl;
  efficiency_surf=(double(number_of_entries_surf)/1000000);
  cout<<"Surface efficiency: "<<efficiency_surf<<endl;
  efficiency_wire=(double(number_of_entries_wire)/1000000);
  cout<<"Tracker efficiency: "<<efficiency_wire<<endl;
  number_exp_bulk=efficiency_bulk*activity_bulk*exposure_in_seconds;
  number_exp_surf=efficiency_surf*activity_surf*exposure_in_seconds;
  number_exp_wire=efficiency_wire*activity_wire*exposure_in_seconds;
  total_number_exp=number_exp_bulk+number_exp_surf+number_exp_wire;
  old_fraction_bulk=double(number_exp_bulk)/double(total_number_exp);
  cout<<"Old fraction bulk: "<<old_fraction_bulk<<endl;
  old_fraction_surf=double(number_exp_surf)/double(total_number_exp);
  cout<<"Old fraction surf: "<<old_fraction_surf<<endl;
  old_fraction_wire=double(number_exp_wire)/double(total_number_exp);
  cout<<"Old fraction wire: "<<old_fraction_wire<<endl;

  //Now need to generate sudo data from these histograms
  //Use GetRandom n times, where n is a randomly generated number of events
  //based on poissonian law.
  TRandom *eventGenerator = new TRandom3();
  for(int p=0; p<1; p++){
    TH1F *data = new TH1F("data", "data", 100, 0, 500);
    data->SetTitle("Pseudo-experiment with three contributions after 675 days exposure");
    data->GetXaxis()->SetTitle("#alpha track length (mm)");
    data->GetYaxis()->SetTitle("Events / 5 mm");
    data->SetMarkerStyle(20);
    data->SetMarkerSize(0.7);
    int random_number_of_entries = eventGenerator->Poisson(total_number_exp);
    for(int n=0; n<=random_number_of_entries; n++){
         data->Fill(h_total->GetRandom());
       }

    // Test TFractionFitter
    TObjArray *mc = new TObjArray(3);
    mc->Add(h1);
    mc->Add(h2);
    mc->Add(h3);

    double value[3];
    double error[3];
    TH1D* h_after[3];
    TH1D* fitresult;

    TFractionFitter* fit = new TFractionFitter(data, mc);
    //THStack *hs = new THStack("hs","Stacked 1D histograms");
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
       //h_after[2]->SetFillColor(kBlue);
       //h_after[2]->SetFillStyle(3002);
       h_after[0]->SetLineColor(kRed);
       //h_after[0]->SetFillColor(kRed);
       //h_after[0]->SetFillStyle(3002);
       h_after[1]->SetLineColor(kMagenta);
       //h_after[1]->SetFillColor(kGray+2);
       //h_after[1]->SetFillStyle(3002);
       // hs->Add(h_after[0]);
       // hs->Add(h_after[1]);
       // hs->Add(h_after[2]);
       // hs->Draw("hist same");
       h_after[0]->Draw("hist same");
       h_after[1]->Draw("hist same");
       h_after[2]->Draw("hist same");

       //Calculate the new activities predicted by the fit
       // activity_bulk_new = (value[0]/old_fraction_bulk)*activity_bulk;
       // activity_surf_new = (value[1]/old_fraction_surf)*activity_surf;
       // activity_wire_new = (value[2]/old_fraction_wire)*activity_wire;
       //
       // //Add values to histograms
       // fitted_activity_bulk->Fill(activity_bulk_new);
       // fitted_activity_surf->Fill(activity_surf_new);
       // fitted_activity_wire->Fill(activity_wire_new);
     }

     if (status == 0) {
       TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
       leg->SetFillColor(0);
       leg->AddEntry(data,"Data","lep");
       leg->AddEntry(fitresult,"Fit Result","l");
       leg->AddEntry(h_after[0],"Bulk of the foil","l");
       leg->AddEntry(h_after[1],"Surface of the foil","l");
       leg->AddEntry(h_after[2],"Tracker","l");
       leg->Draw("same");
     }

     //c1->SaveAs("PseudoExperiment_90_10µBq");
  }

 //Draw histograms
 // fitted_activity_bulk->Draw();
 // //c1->SaveAs("FittedActivityBulk_180.root");
 // fitted_activity_surf->Draw();
 // //c1->SaveAs("FittedActivitySurf_180.root");
 // fitted_activity_wire->Draw();
 // //c1->SaveAs("FittedActivityWire_180.root");
 // //Fit histograms
 // //Get mean and standard deviation
 // fitted_activity_bulk->Fit("gaus");
 // fitted_activity_surf->Fit("gaus");
 // fitted_activity_wire->Fit("gaus");
 //
 // cout<<"Bulk input activity: "<<activity_bulk<<endl;
 // cout<<"Surf input activity: "<<activity_surf<<endl;
 // cout<<"Wire input activity: "<<activity_wire<<endl;
 //
 // double mean_bulk = fitted_activity_bulk->GetFunction("gaus")->GetParameter(1);
 // double mean_surf = fitted_activity_surf->GetFunction("gaus")->GetParameter(1);
 // double mean_wire = fitted_activity_wire->GetFunction("gaus")->GetParameter(1);
 //
 // double mean_bulk_error = fitted_activity_bulk->GetFunction("gaus")->GetParError(1);
 // double mean_surf_error = fitted_activity_surf->GetFunction("gaus")->GetParError(1);
 // double mean_wire_error = fitted_activity_wire->GetFunction("gaus")->GetParError(1);
 //
 // cout<<"Mean bulk: "<<mean_bulk<<" +- "<<mean_bulk_error<<endl;
 // cout<<"Mean surf: "<<mean_surf<<" +- "<<mean_surf_error<<endl;
 // cout<<"Mean wire: "<<mean_wire<<" +- "<<mean_wire_error<<endl;
 //
 // double stdev_bulk = fitted_activity_bulk->GetFunction("gaus")->GetParameter(2);
 // cout<<"Standard deviation bulk: "<<stdev_bulk<<endl;
 // double stdev_surf = fitted_activity_surf->GetFunction("gaus")->GetParameter(2);
 // cout<<"Standard deviation surf: "<<stdev_surf<<endl;
 // double stdev_wire = fitted_activity_wire->GetFunction("gaus")->GetParameter(2);
 // cout<<"Standard deviation wire: "<<stdev_wire<<endl;

}

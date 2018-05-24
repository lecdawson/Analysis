void gammaEnergy()
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

  TH1D *h_tl = new TH1D("h_tl", "h_tl", 100, 0, 5.5);
  TH1D *h_bulk = new TH1D("h_bulk", "h_bulk", 100, 0, 5.5);
  TH1D *h_surf = new TH1D("h_surf", "h_surf", 100, 0, 5.5);
  TH1D *h_wire = new TH1D("h_wire", "h_wire", 100, 0, 5.5);
  TH1F *h_total = new TH1F("h_total", "h_total", 100, 0, 5.5);
  TH1F *h_bi = new TH1F("h_bi", "h_bi", 100, 0, 5.5);
  TH1F *fitted_activity_tl = new TH1F("fitted_activity_tl", "fitted_activity_tl", 1000, 0.0001, 0.0007);//0.00037
  TH1F *fitted_activity_bi = new TH1F("fitted_activity_bi", "fitted_activity_bi", 1000, 0.05, 0.07);//0.06108
  h_tl->SetTitle("Total gamma energy, {}^{208}Tl bulk and {}^{214}Bi from all areas, 1E6");
  h_bulk->SetTitle("Total gamma energy, {}^{214}Bi bulk of source foil, 1E6");
  h_surf->SetTitle("Total gamma energy, {}^{214}Bi surface of source foil, 1E6");
  h_wire->SetTitle("Total gamma energy, {}^{214}Bi tracker wires, 1E6");
  h_total->SetTitle("Reference activity - 1eN#gamma (N>0), 1E6 events");
  fitted_activity_tl->SetTitle("Fitted activity - {}^{208}Tl bulk, 200 days exposure");
  fitted_activity_bi->SetTitle("Fitted activity - {}^{214}Bi combined, 200 days exposure");
  h_tl->GetXaxis()->SetTitle("Gamma energy (MeV)");
  h_bulk->GetXaxis()->SetTitle("Gamma energy (MeV)");
  h_surf->GetXaxis()->SetTitle("Gamma energy (MeV)");
  h_wire->GetXaxis()->SetTitle("Gamma energy (MeV)");
  h_total->GetXaxis()->SetTitle("Gamma energy (MeV)");
  fitted_activity_tl->GetXaxis()->SetTitle("Activity (Bq)");
  fitted_activity_bi->GetXaxis()->SetTitle("Activity (Bq)");
  h_tl->GetYaxis()->SetTitle("Number of events /0.055 MeV, normalised by activity");
  h_bulk->GetYaxis()->SetTitle("Number of events");
  h_surf->GetYaxis()->SetTitle("Number of events");
  h_wire->GetYaxis()->SetTitle("Number of events");
  h_total->GetYaxis()->SetTitle("(s^{-1})");

  h_total->SetLineColor(kBlack);
  h_tl->SetLineColor(kBlack);
  //h_tl->SetLineColor(kGray+2);
  // h_tl->SetFillColor(kGray+2);
  // h_tl->SetFillStyle(3002);
  h_bulk->SetLineColor(kRed);
  // h_bulk->SetFillColor(kRed);
  // h_bulk->SetFillStyle(3002);
  h_surf->SetLineColor(kMagenta);
  // h_surf->SetFillColor(kMagenta);
  // h_surf->SetFillStyle(3002);
  h_wire->SetLineColor(kBlue);
  // h_wire->SetFillColor(kBlue);
  // h_wire->SetFillStyle(3002);
  fitted_activity_tl->SetLineColor(kBlue-5);
  fitted_activity_bi->SetLineColor(kRed);

  TCanvas *c1 =new TCanvas("snemo1","snemo1",900,600);
  //gStyle->SetOptStat(0);
  //h1->SetMinimum(0.1);
  //h1->SetMaximum(10000);

  bool topology_1e1alpha=0;
  bool topology_1engamma=0;
  int alpha_count=0;
  int number_of_electrons=0;
  int number_of_gammas=0;
  vector<bool> *alphas_from_foil=0;
  vector<bool> *electron_hits_main_wall=0;
  vector<int> *electron_charges=0;
  vector<double> *electron_energies=0;
  vector<double> *gamma_energies=0;
  vector<bool> *electronsFromFoil=0;

  int exposure=0;
  int exposure_in_seconds=0;
  int number_of_entries_tl=0;
  int number_of_entries_bulk=0;
  int number_of_entries_surf=0;
  int number_of_entries_wire=0;
  int total_num_entries_bi=0;
  int number_exp_tl=0;
  int number_exp_bi=0;
  int number_exp_bulk=0;
  int number_exp_surf=0;
  int number_exp_wire=0;
  int total_number_exp=0;
  //Taken from 90 day exposure fits
  //double activity_bulk_fit=0.01582;
  //double activity_surf_fit=0.0001853;
  //double activity_wire_fit=0.04462;
  //double activity_bi_fit=activity_bulk_fit+activity_surf_fit+activity_wire_fit;
  //double activity_bulk_fit_error=0;
  //double activity_surf_fit_error=0;
  //double activity_wire_fit_error=0;
  double efficiency_tl=0;
  //double efficiency_bi=0;
  double efficiency_bulk=0;
  double efficiency_surf=0;
  double efficiency_wire=0;
  double old_fraction_bi=0;
  double old_fraction_bulk=0;
  double old_fraction_surf=0;
  double old_fraction_wire=0;
  double old_fraction_tl=0;
  double total_gamma_energy=0;
  double gamma_energy=0;
  int total_number_entries=0;

  // Activities here for Bi214 are taken from original activity values
  double activity_tracker=2.28E-3;
  double activity_bulk=62E-6;
  double activity_surf=activity_tracker*0.078;
  double activity_wire=activity_tracker*0.922;
  double total_activity_bi=activity_bulk+activity_surf+activity_wire;
  double activity_tl_new=0;
  double activity_bi_new=0;

  // Taken from recent measurements of source foils
  double activity_tl=12.4E-6; //14µBq ;

  double h1_scale=0;
  double h2_scale=0;
  double h3_scale=0;
  double h4_scale=0;

  //Constriain values
  double bulk_low=0;
  double bulk_high=0;
  double surf_low=0;
  double surf_high=0;
  double wire_low=0;
  double wire_high=0;

  tree_tl->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  tree_tl->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_tl->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_tl->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_tl->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_tl->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_tl->SetBranchAddress("reco.gamma_energies", &gamma_energies);
  tree_tl->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_tl->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_bulk->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  tree_bi_bulk->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_bulk->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_bulk->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_bulk->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_bulk->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_bulk->SetBranchAddress("reco.gamma_energies", &gamma_energies);
  tree_bi_bulk->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_bulk->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_surf->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_surf->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_surf->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_surf->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_surf->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_surf->SetBranchAddress("reco.gamma_energies", &gamma_energies);
  tree_bi_surf->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_surf->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  tree_bi_wire->SetBranchAddress("reco.topology_1engamma", &topology_1engamma);
  tree_bi_wire->SetBranchAddress("reco.alpha_count", &alpha_count);
  tree_bi_wire->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  tree_bi_wire->SetBranchAddress("reco.electron_charges", &electron_charges);
  tree_bi_wire->SetBranchAddress("reco.electron_energies", &electron_energies);
  tree_bi_wire->SetBranchAddress("reco.gamma_energies", &gamma_energies);
  tree_bi_wire->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  tree_bi_wire->SetBranchAddress("reco.number_of_gammas", &number_of_gammas);

  //Quick efficiencies
  int efficiency_1e1g=0;
  int efficiency_1eNg=0;
  int efficiency_1e=0;
  int efficiency_1e1a=0;
  for(int entry=0; entry<entriesTl; entry++){
    tree_bi_bulk->GetEntry(entry);
    if(number_of_electrons==1 && number_of_gammas==1 && alpha_count==0){
       efficiency_1e1g++;
    }
    if(number_of_electrons==1 && number_of_gammas>0 && alpha_count==0){
      efficiency_1eNg++;
    }
    if(number_of_electrons==1 && number_of_gammas==0 && alpha_count==0){
      efficiency_1e++;
    }
    if(number_of_electrons==1 && alpha_count==1){
      efficiency_1e1a++;
    }
  }

  cout<<"Efficiency 1e1gamma: "<<efficiency_1e1g<<endl;
  cout<<"Efficiency 1e1alpha: "<<efficiency_1e1a<<endl;
  cout<<"Efficiency 1eNgamma: "<<efficiency_1eNg<<endl;
  cout<<"Efficiency 1e: "<<efficiency_1e<<endl;

  //For thalium
  //1eNy topology where N>0, no alphas, electron comes from foil, is negative and
  //has an energy >500 keV
  //OR there are >1 electrons but the second has an energy < 500 keV
  for(int entry=0; entry<entriesTl; entry++){
    tree_tl->GetEntry(entry);
    total_gamma_energy=0;
    for(int i=0; i<number_of_gammas; i++){
      gamma_energy=gamma_energies->at(i);
      total_gamma_energy+=gamma_energy;
    }
    if(number_of_electrons==1 && number_of_gammas>0){
      if((alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5)){
        h_tl->Fill(total_gamma_energy);
      }
    }
    //Should I be allowing more than 1 electron events? Need to check why this was
    //included in the first place
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_tl->Fill(total_gamma_energy);
    //   }
    // }
  }

  //For bismuth
  //1eNy topology where N>0, no alphas, electron comes from foil, is negative and
  //has an energy >500 keV
  //OR there are >1 electrons but the second has an energy < 500 keV
  for(int entry=0; entry<entriesBiBulk; entry++){
    tree_bi_bulk->GetEntry(entry);
    total_gamma_energy=0;
    for(int i=0; i<number_of_gammas; i++){
      gamma_energy=gamma_energies->at(i);
      total_gamma_energy+=gamma_energy;
    }
    if(topology_1engamma){
      if((alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5)){
        h_bulk->Fill(total_gamma_energy);
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_bulk->Fill(total_gamma_energy);
    //   }
    // }
  }
  for(int entry=0; entry<entriesBiSurf; entry++){
    tree_bi_surf->GetEntry(entry);
    total_gamma_energy=0;
    for(int i=0; i<number_of_gammas; i++){
      gamma_energy=gamma_energies->at(i);
      total_gamma_energy+=gamma_energy;
    }
    if(topology_1engamma){
      if((alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5)){
        h_surf->Fill(total_gamma_energy);
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_surf->Fill(total_gamma_energy);
    //   }
    // }
  }
  for(int entry=0; entry<entriesBiWire; entry++){
    tree_bi_wire->GetEntry(entry);
    total_gamma_energy=0;
    for(int i=0; i<number_of_gammas; i++){
      gamma_energy=gamma_energies->at(i);
      total_gamma_energy+=gamma_energy;
    }
    if(topology_1engamma){
      if((alpha_count==0 && electronsFromFoil->at(0)==1 && electron_charges->at(0)==8 && electron_energies->at(0)>=0.5)){
        h_wire->Fill(total_gamma_energy);
      }
    }
    // else if(number_of_electrons>1 && number_of_gammas>0 && alpha_count==0 && electron_energies->at(1)<0.5 && electron_energies->at(0)>=0.5){
    //   if(electronsFromFoil->at(0)==1 && electron_charges->at(0)==8){
    //     h_wire->Fill(total_gamma_energy);
    //   }
    // }
  }

  //normalise the histograms, scaling by activity
  number_of_entries_tl = h_tl->GetEntries();
  number_of_entries_bulk = h_bulk->GetEntries();
  number_of_entries_surf = h_surf->GetEntries();
  number_of_entries_wire = h_wire->GetEntries();
  total_num_entries_bi = number_of_entries_bulk+number_of_entries_surf+number_of_entries_wire;
  h1_scale = (activity_tl/1000000);
  h2_scale = (activity_bulk/1000000);
  h3_scale = (activity_surf/1000000);
  h4_scale = (activity_wire/1000000);

  h_tl->Sumw2();
  h_bulk->Sumw2();
  h_surf->Sumw2();
  h_wire->Sumw2();

  h_tl->Scale(h1_scale);
  h_bulk->Scale(h2_scale);
  h_surf->Scale(h3_scale);
  h_wire->Scale(h4_scale);

  //Scale the histograms
  // h1_scale = 1/h_tl->Integral();
  // h_tl->Scale(h1_scale);
  // h2_scale = 1/h_bulk->Integral();
  // h_bulk->Scale(h2_scale);
  // h3_scale = 1/h_surf->Integral();
  // h_surf->Scale(h3_scale);
  // h4_scale = 1/h_wire->Integral();
  // h_wire->Scale(h4_scale);

  // h_total->Draw("hist");
  // h_bulk->Draw("hist");
  // h_surf->Draw("hist same");
  // h_wire->Draw("hist same");
  // h_tl->Draw("hist same");

  // TLegend *leg = new TLegend(0.5,0.7,0.79,0.79);
  // //leg->AddEntry(h_total,"Combined events 1eN#gamma (N>0)","f");
  // leg->AddEntry(h_tl,"{}^{208}Tl 1eN#gamma (N>0)","l");
  // leg->AddEntry(h_bulk,"{}^{214}Bi bulk of the foil 1eN#gamma (N>0)","l");
  // leg->AddEntry(h_surf,"{}^{214}Bi surface of the foil 1eN#gamma (N>0)","l");
  // leg->AddEntry(h_wire,"{}^{214}Bi tracker wires 1eN#gamma (N>0)","l");
  // leg->Draw("same");

  exposure=200;
  exposure_in_seconds=exposure*24*60*60;
  //
  //Scale to exposure
  h_tl->Scale(exposure_in_seconds);
  h_bulk->Scale(exposure_in_seconds);
  h_surf->Scale(exposure_in_seconds);
  h_wire->Scale(exposure_in_seconds);
  //h_tl->Scale(exposure_in_seconds);
  //h_bi->Scale(exposure_in_seconds);
  //h_bulk->Scale(exposure_in_seconds);
  //h_wire->Scale(exposure_in_seconds);
  //h_surf->Scale(exposure_in_seconds);

  //Create histogram combination of Bi
  h_bi->Add(h_bulk);
  h_bi->Add(h_surf);
  h_bi->Add(h_wire);

  //Sum the normalised histograms of the individual generators
  //h_total->Add(h_tl);
  //h_total->Add(h_bi);
  //h_total->Add(h_wire);
  //h_total->Add(h_surf);

  // h_total->Draw("hist");
  // h_bi->Draw("hist same");
  // h_tl->Draw("hist same");
  h_total->Add(h_tl);
  h_total->Add(h_bulk);
  h_total->Add(h_surf);
  h_total->Add(h_wire);

  //Calculate the old fractions by finding the expected number of entries
  //Is dividing by 3E6 correct? Do not expected 1e1aNy in every event, it is 79.1%
  // N_exp = efficiency*activity*exposure
  efficiency_tl=(double(number_of_entries_tl)/1000000);
  efficiency_bulk=(double(number_of_entries_bulk)/1000000);
  efficiency_surf=(double(number_of_entries_surf)/1000000);
  efficiency_wire=(double(number_of_entries_wire)/1000000);
  number_exp_tl=efficiency_tl*activity_tl*exposure_in_seconds;
  number_exp_bulk=efficiency_bulk*activity_bulk*exposure_in_seconds;
  number_exp_surf=efficiency_surf*activity_surf*exposure_in_seconds;
  number_exp_wire=efficiency_wire*activity_wire*exposure_in_seconds;
  number_exp_bi=number_exp_bulk+number_exp_surf+number_exp_wire;
  total_number_exp=number_exp_tl+number_exp_bi;
  cout<<"Total number exp: "<<total_number_exp<<endl;
  old_fraction_tl=double(number_exp_tl)/double(total_number_exp);
  old_fraction_bi=double(number_exp_bi)/double(total_number_exp);
  //old_fraction_bulk=double(number_exp_bulk)/double(total_number_exp);
  //old_fraction_surf=double(number_exp_surf)/double(total_number_exp);
  //old_fraction_wire=double(number_exp_wire)/double(total_number_exp);
  //
  // Now need to generate sudo data from these histograms
  // Use GetRandom n times, where n is a randomly generated number of events
  // based on poissonian law.
  TRandom *eventGenerator = new TRandom3();
  for(int p=0; p<1; p++){
    TH1F *data = new TH1F("data", "data", 100, 0, 5.5);
    data->SetTitle("Pseudo-experiment with two contributions after 200 days exposure");
    data->GetXaxis()->SetTitle("#gamma energies (MeV)");
    data->GetYaxis()->SetTitle("Events/(0.055)");
    data->SetMarkerStyle(20);
    data->SetMarkerSize(0.7);

    int random_number_of_entries = eventGenerator->Poisson(total_number_exp);
    for(int n=0; n<random_number_of_entries; n++){
         data->Fill(h_total->GetRandom());
    }

    // Test TFractionFitter
    TObjArray *mc = new TObjArray(2);
    mc->Add(h_tl);
    mc->Add(h_bi);
    //mc->Add(h_surf);
    //mc->Add(h_wire);

    double value[2];
    double error[2];
    TH1D* h_after[2];
    TH1D* fitresult;

    //Calculate constraint values
    //bi_low=((activity_bi_fit/total_activity_bi)*old_fraction_bi); //minus error
    //bi_high=((activity_bi_fit/total_activity_bi)*old_fraction_bi); //plus error

    TFractionFitter* fit = new TFractionFitter(data, mc);
    //THStack *hs = new THStack("hs","Stacked 1D histograms");
    //Constrain contributions from Bismuth using existing activities
    //Remember to set these values back to 2,3,4 when Tl included!!!
    Int_t status = fit->Fit();
    std::cout << "fit status: " << status << std::endl;
    if(status == 0){                       // check on fit status
       fitresult = (TH1D*) fit->GetPlot();
       for (int i=0; i<2; i++){
           fit->GetResult(i,value[i],error[i]);
           h_after[i] = (TH1D*)fit->GetMCPrediction(i);
           h_after[i]->Scale((value[i]*data->Integral())/(h_after[i]->Integral()));
       }
       data->Draw("Ep");
       fitresult->Draw("hist same");

       fitresult->SetLineColor(kBlack);
       h_after[1]->SetLineColor(kRed);
       //h_after[1]->SetFillColor(kRed);
       //h_after[1]->SetFillStyle(3002);
       h_after[0]->SetLineColor(kBlue);
       //h_after[0]->SetFillColor(kGray+2);
       //h_after[0]->SetFillStyle(3002);
       // h_after[2]->SetLineColor(kMagenta);
       // h_after[2]->SetFillColor(kMagenta);
       // h_after[2]->SetFillStyle(3002);
       // h_after[3]->SetLineColor(kBlue);
       // h_after[3]->SetFillColor(kBlue);
       // h_after[3]->SetFillStyle(3002);
       // // hs->Add(h_after[0]);
       // // hs->Add(h_after[1]);
       // // hs->Add(h_after[2]);
       // // hs->Draw("hist same");
       h_after[1]->Draw("hist same");
       h_after[0]->Draw("hist same");
       //h_after[2]->Draw("hist same");
       //h_after[3]->Draw("hist same");

       // //Calculate the new activities predicted by the fit
       // activity_tl_new = (value[0]/old_fraction_tl)*activity_tl;
       // activity_bi_new = (value[1]/old_fraction_bi)*total_activity_bi;
       //
       // //Add values to histograms
       // fitted_activity_tl->Fill(activity_tl_new);
       // fitted_activity_bi->Fill(activity_bi_new);

       if (status == 0) {
         TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
         leg->SetFillColor(0);
         leg->AddEntry(data,"Data","lep");
         leg->AddEntry(fitresult,"Fit Result","l");
         leg->AddEntry(h_after[0],"{}^{208}Tl bulk of the foil","l");
         leg->AddEntry(h_after[1],"{}^{214}Bi bulk and surface foil, and in tracker","l");
         //leg->AddEntry(h_after[2],"Scaled {}^{214}Bi Surface","f");
         //leg->AddEntry(h_after[3],"Scaled {}^{214}Bi Tracker","f");
         leg->Draw("same");
       }
     }
   }

   // //Draw histograms
   // fitted_activity_tl->Draw();
   // c1->SaveAs("FittedActivityTl_3.root");
   // fitted_activity_bi->Draw();
   // c1->SaveAs("FittedActivityBiComb_3.root");
   //
   // //Fit histograms
   // //Get mean and standard deviation
   // fitted_activity_tl->Fit("gaus");
   // fitted_activity_bi->Fit("gaus");
   //
   // cout<<"Tl input activity: "<<activity_tl<<endl;
   // cout<<"Bi input activity: "<<total_activity_bi<<endl;
   //
   // double mean_tl = fitted_activity_tl->GetFunction("gaus")->GetParameter(1);
   // double mean_bi = fitted_activity_bi->GetFunction("gaus")->GetParameter(1);
   //
   // double mean_tl_error = fitted_activity_tl->GetFunction("gaus")->GetParError(1);
   // double mean_bi_error = fitted_activity_bi->GetFunction("gaus")->GetParError(1);
   //
   // cout<<"Mean tl: "<<mean_tl<<" +- "<<mean_tl_error<<endl;
   // cout<<"Mean bi: "<<mean_bi<<" +- "<<mean_bi_error<<endl;
   //
   // double stdev_tl = fitted_activity_tl->GetFunction("gaus")->GetParameter(2);
   // cout<<"Standard deviation tl: "<<stdev_tl<<endl;
   // double stdev_bi = fitted_activity_bi->GetFunction("gaus")->GetParameter(2);
   // cout<<"Standard deviation bi: "<<stdev_bi<<endl;
   //
   // cout<<"Efficiency Tl208 bulk: "<<efficiency_tl<<endl;
   // cout<<"Efficiency Bi214 bulk: "<<efficiency_bulk<<endl;
   // cout<<"Efficiency Bi214 surf: "<<efficiency_surf<<endl;
   // cout<<"Efficiency Bi214 wire: "<<efficiency_wire<<endl;


}

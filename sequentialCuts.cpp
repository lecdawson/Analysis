void sequentialCuts()
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
  //cout<<"Total events "<<entriesFoil<<endl;
  int entriesSurf=treeSurf->GetEntries();
  //cout<<"Total events "<<entriesSurf<<endl;
  int entriesWire=treeWire->GetEntries();
  cout<<"Total events "<<entriesSurf<<endl;

  //For sequential electron cuts
  //candidates that have an associated hit
  int associated_track_count=0;
  int total_number_associated_tracks=0;
  //number of electron candidates, prompt and have associated hit
  int number_of_electrons=0;
  int total_number_of_electrons=0;
  //comes from the source foil
  vector<bool> *electronsFromFoil=0;
  int passes_electron_from_foil=0;
  //hitting the main wall
  vector<bool> *electron_hits_main_wall=0;
  int passes_electron_from_foil_main_wall=0;
  //has a negative charged
  vector<int> *electron_charges=0;
  int passes_electron_from_foil_main_wall_neg=0;

  //For sequential alpha cuts
  //Number of reconstructed alphas, these are delayed, undefined charge and have no calo hit
  int alpha_count=0;
  int total_number_of_alphas=0;
  //coming from the foil
  int foil_alpha_count=0;
  int passes_alpha_from_foil=0;
  bool topology_1e1alpha=0;
  int electron_alpha_count=0;
  vector<bool> *alphas_from_foil=0;

  treeSurf->SetBranchAddress("reco.topology_1e1alpha",&topology_1e1alpha);
  treeSurf->SetBranchAddress("reco.associated_track_count", &associated_track_count);
  treeSurf->SetBranchAddress("reco.number_of_electrons", &number_of_electrons);
  treeSurf->SetBranchAddress("reco.electrons_from_foil", &electronsFromFoil);
  treeSurf->SetBranchAddress("reco.electron_hits_mainwall", &electron_hits_main_wall);
  treeSurf->SetBranchAddress("reco.electron_charges", &electron_charges);
  treeSurf->SetBranchAddress("reco.alpha_count", &alpha_count);
  treeSurf->SetBranchAddress("reco.foil_alpha_count", &foil_alpha_count);
  treeSurf->SetBranchAddress("reco.alphas_from_foil", &alphas_from_foil);

  for(int entry=0; entry < entriesSurf; entry++){
    treeSurf->GetEntry(entry);
    total_number_of_electrons+=number_of_electrons;
    total_number_associated_tracks+=associated_track_count;

    //Count number of electrons that pass each of the sequential cuts
    if(number_of_electrons >0){
      for(int electron=0; electron<number_of_electrons; electron++){
        if(electronsFromFoil->at(electron)==1){
          passes_electron_from_foil++;
        }
        if(electronsFromFoil->at(electron)==1 && electron_hits_main_wall->at(electron)==1){
          passes_electron_from_foil_main_wall++;
        }
        if(electronsFromFoil->at(electron)==1 && electron_hits_main_wall->at(electron)==1 && electron_charges->at(electron)==8){
          passes_electron_from_foil_main_wall_neg++;
        }
      }
    }
    total_number_of_alphas+=alpha_count;
    //Count number of alphas that pass each of the sequential cuts
    if(alpha_count >0){
        passes_alpha_from_foil+=foil_alpha_count;
      }
    if(topology_1e1alpha){
      if(electronsFromFoil->at(0)==1 && electron_hits_main_wall->at(0)==1 && electron_charges->at(0)==8 && alphas_from_foil->at(0)==1){
        electron_alpha_count++;
      }
    }
  }

  cout<<"Total number of associated hits: "<<total_number_associated_tracks<<" efficiency: "<<(double(total_number_associated_tracks)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Total number of reconstructed electrons (prompt and calo hit): "<<total_number_of_electrons<<" efficiency: "<<(double(total_number_of_electrons)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Passes electron from foil: "<<passes_electron_from_foil<<" efficiency: "<<(double(passes_electron_from_foil)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Passes electron from foil and hits main wall: "<<passes_electron_from_foil_main_wall<<" efficiency: "<<(double(passes_electron_from_foil_main_wall)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Passes electron from foil, hits main wall, and has negative charge: "<<passes_electron_from_foil_main_wall_neg<<" efficiency: "<<(double(passes_electron_from_foil_main_wall_neg)/double(entriesSurf))*100<<"%"<<endl;

  cout<<"Total number of reconstructed alphas (undefined, no calo, is delayed): "<<total_number_of_alphas<<" efficiency: "<<(double(total_number_of_alphas)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Passes alpha from foil: "<<passes_alpha_from_foil<<" efficiency: "<<(double(passes_alpha_from_foil)/double(entriesSurf))*100<<"%"<<endl;
  cout<<"Passes 1e1alpha: "<<electron_alpha_count<<" efficiency: "<<(double(electron_alpha_count)/double(entriesSurf))*100<<"%"<<endl;
}

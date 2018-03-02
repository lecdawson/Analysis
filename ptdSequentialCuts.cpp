void ptdSequentialCuts()
{
  //Below is just for events from the foil
  //Read in all of the sensitivity files for different generators
  string foils="/home/vagrant/PhD/PhDYear3/Background/Bi214_Foils/ThibaudStudy/3E5Sample/ConfigChange/Bi214_foil_3E5_p2r.root";
  string surface="/home/vagrant/PhD/PhDYear3/Background/Bi214_Surface/ThibaudStudy/3E5Sample/ConfigChange/Bi214_surf_3E5_p2r.root";
  string wires="/home/vagrant/PhD/PhDYear3/Background/Bi214_Wires/ThibaudStudy/3E5Sample/ConfigChange/Bi214_wire_3E5_p2r.root";

  TFile *file1=new TFile(foils.c_str());
  TFile *file2=new TFile(surface.c_str());
  TFile *file3=new TFile(wires.c_str());
  TTree *treeFoil=(TTree*)file1->Get("PTD");
  TTree *treeSurf=(TTree*)file2->Get("PTD");
  TTree *treeWire=(TTree*)file3->Get("PTD");

  int entriesFoil=treeFoil->GetEntries();
  //cout<<"Total events "<<entriesFoil<<endl;
  int entriesSurf=treeSurf->GetEntries();
  //cout<<"Total events "<<entriesSurf<<endl;
  int entriesWire=treeWire->GetEntries();
  cout<<"Total events "<<entriesWire<<endl;

  int number_of_particles=0;
  //For sequential electron cuts
  //candidates that have an associated hit
  vector<int> *calo_associated=0;
  int passes_associated_calo=0;
  //comes from the source foil
  vector<int> *vertex_type=0;
  vector<double> *vertex_x=0;
  double distance_to_first_layer=10.838;
  int passes_calo_from_foil=0;
  //hitting the main wall
  vector<int> *calo_type=0;
  int passes_calo_foil_main=0;
  //has a negative charged
  vector<int> *charge=0;
  int passes_calo_foil_main_neg=0;

  //For sequential alpha cuts
  //Number of reconstructed alphas, these are delayed, undefined charge and have no calo hit
  vector<int> *traj_cluster_delayed=0;
  int passes_del_undef_no_calo=0;
  //coming from the foil
  int passes_alpha_from_foil=0;


  treeWire->SetBranchAddress("particle.nofparticles", &number_of_particles);
  treeWire->SetBranchAddress("particle.calo_associated", &calo_associated);
  treeWire->SetBranchAddress("particle.vertex_type", &vertex_type);
  treeWire->SetBranchAddress("particle.vertex_x", &vertex_x);
  treeWire->SetBranchAddress("particle.calo_type", &calo_type);
  treeWire->SetBranchAddress("particle.charge", &charge);
  treeWire->SetBranchAddress("particle.traj_cl_del", &traj_cluster_delayed);

  for(int entry=0; entry < entriesWire; entry++){
    treeWire->GetEntry(entry);

    //Count number of electrons that pass each of the sequential cuts
    if(number_of_particles >0){
      for(int particle=0; particle<number_of_particles; particle++){
        if(calo_associated->at(particle)==1){
          passes_associated_calo++;
        }
        if(calo_associated->at(particle)==1 && vertex_type->at(particle)==0){
          passes_calo_from_foil++;
        }
        if(calo_associated->at(particle)==1 && vertex_type->at(particle)==0 && calo_type->at(particle)==1302){
          passes_calo_foil_main++;
        }
        if(calo_associated->at(particle)==1 && vertex_type->at(particle)==0 && calo_type->at(particle)==1302 && charge->at(particle)==8){
          passes_calo_foil_main_neg++;
        }
        if(traj_cluster_delayed->at(particle)==1 && charge->at(particle)==1 && calo_associated->at(particle)==-1){
          passes_del_undef_no_calo++;
        }
        if(traj_cluster_delayed->at(particle)==1 && charge->at(particle)==1 && calo_associated->at(particle)==-1 && vertex_type->at(particle)==0){
          passes_alpha_from_foil++;
        }
      }
    }
  }

  cout<<"Total number of reconstructed electrons (associated hit): "<<passes_associated_calo<<" efficiency: "<<double(passes_associated_calo)/double(entriesWire)*100<<"%"<<endl;
  cout<<"Passes associated and electron from foil: "<<passes_calo_from_foil<<" efficiency: "<<double(passes_calo_from_foil)/double(entriesWire)*100<<"%"<<endl;
  cout<<"Passes associated, from foil, and hits main wall: "<<passes_calo_foil_main<<" efficiency: "<<double(passes_calo_foil_main)/double(entriesWire)*100<<"%"<<endl;
  cout<<"Passes associated, from foil, hits main wall, and has negative charge: "<<passes_calo_foil_main_neg<<" efficiency: "<<double(passes_calo_foil_main_neg)/double(entriesWire)*100<<"%"<<endl;

  cout<<"Total number of reconstructed alphas (undefined, no calo, is delayed): "<<passes_del_undef_no_calo<<" efficiency: "<<double(passes_del_undef_no_calo)/double(entriesWire)*100<<"%"<<endl;
  cout<<"Passes alpha from foil: "<<passes_alpha_from_foil<<" efficiency: "<<double(passes_alpha_from_foil)/double(entriesWire)*100<<"%"<<endl;
}

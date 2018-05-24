#include "TROOT.h"
#include "TH2F.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"


void inputFittedActivities() {
TTree *MyTree = new TTree("MyTree", "MyTree");

MyTree->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/activities_wire_var.txt", "Input/F:Fitted/F:Error/F");

Float_t Input;
Float_t Fitted;
Float_t Error;

MyTree->SetBranchAddress("Input", &Input);
MyTree->SetBranchAddress("Fitted", &Fitted);
MyTree->SetBranchAddress("Error", &Error);

Float_t input[7];
Float_t fitted[7];
Float_t error[7];
Float_t errorx[7];

Int_t nentries = (Int_t)MyTree->GetEntries();
for (Int_t i=0; i<nentries; i++) {
    MyTree->GetEntry(i);
    input[i] = Input;
    fitted[i] = Fitted;
    error[i] = Error;
    errorx[i]=0;
}

TGraphErrors *gr = new TGraphErrors(7,input,fitted,errorx,error);

gr->GetYaxis()->SetTitle("Fitted Activity [Bq]");
gr->GetXaxis()->SetTitle("Original Input Activity [Bq]");
gr->SetTitle("Input activity vs fitted activity for {}^{214}Bi Tracker wires, varying input by #pm 20%");

//gr->GetXaxis()->SetLimits(0.00003,0.00033);
gr->Draw();

}

#include "TROOT.h"
#include "TH2F.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"


void relativeErrors() {
TTree *tree_bi = new TTree("tree_bi", "tree_bi");
TTree *tree_tl = new TTree("tree_tl", "tree_tl");
TTree *tree_bulk = new TTree("tree_bulk", "tree_bulk");
TTree *tree_surf = new TTree("tree_surf", "tree_surf");
TTree *tree_wire = new TTree("tree_wire", "tree_wire");

//tree_bi->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/relative_error_bi.txt", "ExposureBi/F:SigmaBi/F:MeanBi/F");
//tree_tl->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/relative_error_tl.txt", "ExposureTl/F:SigmaTl/F:MeanTl/F");
tree_bulk->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/relative_error_bulk_302µBq.txt", "ExposureBulk/F:SigmaBulk/F:MeanBulk/F");
tree_surf->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/relative_error_surf_302µBq.txt", "ExposureSurf/F:SigmaSurf/F:MeanSurf/F");
tree_wire->ReadFile("/home/vagrant/PhD/PhDYear3/Background/FittedActivity/relative_error_wire_302µBq.txt", "ExposureWire/F:SigmaWire/F:MeanWire/F");

// Float_t ExposureBi;
// Float_t SigmaBi;
// Float_t MeanBi;
// Float_t ExposureTl;
// Float_t SigmaTl;
// Float_t MeanTl;
Float_t ExposureBulk;
Float_t SigmaBulk;
Float_t MeanBulk;
Float_t ExposureSurf;
Float_t SigmaSurf;
Float_t MeanSurf;
Float_t ExposureWire;
Float_t SigmaWire;
Float_t MeanWire;

// tree_bi->SetBranchAddress("ExposureBi", &ExposureBi);
// tree_bi->SetBranchAddress("SigmaBi", &SigmaBi);
// tree_bi->SetBranchAddress("MeanBi", &MeanBi);
// tree_tl->SetBranchAddress("ExposureTl", &ExposureTl);
// tree_tl->SetBranchAddress("SigmaTl", &SigmaTl);
// tree_tl->SetBranchAddress("MeanTl", &MeanTl);
tree_bulk->SetBranchAddress("ExposureBulk", &ExposureBulk);
tree_bulk->SetBranchAddress("SigmaBulk", &SigmaBulk);
tree_bulk->SetBranchAddress("MeanBulk", &MeanBulk);
tree_surf->SetBranchAddress("ExposureSurf", &ExposureSurf);
tree_surf->SetBranchAddress("SigmaSurf", &SigmaSurf);
tree_surf->SetBranchAddress("MeanSurf", &MeanSurf);
tree_wire->SetBranchAddress("ExposureWire", &ExposureWire);
tree_wire->SetBranchAddress("SigmaWire", &SigmaWire);
tree_wire->SetBranchAddress("MeanWire", &MeanWire);

// Float_t exposureBi[9];
// Float_t relativeErrorBi[9];
// Float_t exposureTl[9];
// Float_t relativeErrorTl[9];
Float_t exposureBulk[6];
Float_t relativeErrorBulk[6];
Float_t exposureSurf[7];
Float_t relativeErrorSurf[7];
Float_t exposureWire[7];
Float_t relativeErrorWire[7];

// Int_t n_bi = (Int_t)tree_bi->GetEntries();
// for (Int_t i=0; i<n_bi; i++) {
//     tree_bi->GetEntry(i);
//     exposureBi[i] = ExposureBi;
//     relativeErrorBi[i] = (SigmaBi/MeanBi)*100;
// }
//
// Int_t n_tl = (Int_t)tree_tl->GetEntries();
// for (Int_t i=0; i<n_tl; i++) {
//     tree_tl->GetEntry(i);
//     exposureTl[i] = ExposureTl;
//     relativeErrorTl[i] = (SigmaTl/MeanTl)*100;
// }

Int_t n_bulk = (Int_t)tree_bulk->GetEntries();
for (Int_t i=0; i<n_bulk; i++) {
    tree_bulk->GetEntry(i);
    exposureBulk[i] = ExposureBulk;
    relativeErrorBulk[i] = (SigmaBulk/MeanBulk)*100;
}

Int_t n_surf = (Int_t)tree_surf->GetEntries();
for (Int_t i=0; i<n_surf; i++) {
    tree_surf->GetEntry(i);
    exposureSurf[i] = ExposureSurf;
    relativeErrorSurf[i] = (SigmaSurf/MeanSurf)*100;
}

Int_t n_wire = (Int_t)tree_wire->GetEntries();
for (Int_t i=0; i<n_wire; i++) {
    tree_wire->GetEntry(i);
    exposureWire[i] = ExposureWire;
    relativeErrorWire[i] = (SigmaWire/MeanWire)*100;
}

TCanvas *c1= new TCanvas;
c1->SetGrid();
gPad->SetLogx();

// TGraph *gr_bi = new TGraph(9,exposureBi,relativeErrorBi);
// TGraph *gr_tl = new TGraph(9,exposureTl,relativeErrorTl);
TGraph *gr_bulk = new TGraph(6,exposureBulk,relativeErrorBulk);
TGraph *gr_surf = new TGraph(7,exposureSurf,relativeErrorSurf);
TGraph *gr_wire = new TGraph(7,exposureWire,relativeErrorWire);

gr_bulk->SetLineColor(kBlack);
gr_surf->SetLineColor(kBlue);
gr_wire->SetLineColor(kRed);

gr_surf->GetYaxis()->SetTitle("Relative error [%]");
gr_surf->GetXaxis()->SetTitle("Exposure [days]");
gr_surf->SetTitle("Relative errors for varying exposure, 302 #muBq bulk {}^{214}Bi all generators");
gr_surf->Draw("AC*");
gr_bulk->Draw("C*");
gr_wire->Draw("C*");
//gr_bulk->GetYaxis()->SetRangeUser(0,120);
//gr_bulk->GetXaxis()->SetRangeUser(6,190);

// TLine *tenline = new TLine(0,10,30,10);
// TLine *tenline_track = new TLine(8,10,8,0);
// TLine *tenline_bulk = new TLine(30,10,30,0);
// TLine *fiveline = new TLine(0,5,120,5);
// TLine *fiveline_track = new TLine(30,5,30,0);
// TLine *fiveline_bulk = new TLine(120,5,120,0);
// tenline->SetLineColor(kBlack);
// tenline_track->SetLineColor(kBlack);
// tenline_bulk->SetLineColor(kBlack);
// fiveline->SetLineColor(kBlack);
// fiveline_track->SetLineColor(kBlack);
// fiveline_bulk->SetLineColor(kBlack);
// tenline->SetLineStyle(2);
// tenline_track->SetLineStyle(2);
// tenline_bulk->SetLineStyle(2);
// fiveline->SetLineStyle(2);
// fiveline_track->SetLineStyle(2);
// fiveline_bulk->SetLineStyle(2);
// tenline->SetLineWidth(2);
// tenline_track->SetLineWidth(2);
// tenline_bulk->SetLineWidth(2);
// fiveline->SetLineWidth(2);
// fiveline_track->SetLineWidth(2);
// fiveline_bulk->SetLineWidth(2);
// tenline->Draw("same");
// tenline_track->Draw("same");
// tenline_bulk->Draw("same");
// fiveline->Draw("same");
// fiveline_track->Draw("same");
// fiveline_bulk->Draw("same");

TLegend *leg = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
leg->SetFillColor(0);
leg->AddEntry(gr_bulk,"{}^{214}Bi Bulk","l");
leg->AddEntry(gr_surf,"{}^{214}Bi Surface","l");
leg->AddEntry(gr_wire,"{}^{214}Bi Tracker","l");
leg->Draw("same");
c1->SaveAs("/home/vagrant/PhD/PhDYear3/Background/AnalysisCode/Plots/relative_error_bi_302µBq.root");

// gr_bi->SetLineColor(kBlack);
// gr_tl->SetLineColor(kRed);
//
// gr_bi->GetYaxis()->SetTitle("Relative error [%]");
// gr_bi->GetXaxis()->SetTitle("Exposure [days]");
// gr_bi->SetTitle("Relative errors for varying exposure, {}^{208}Tl and {}^{214}Bi");
// gr_bi->Draw("AC*");
// gr_tl->Draw("C*");
// gr_bi->GetYaxis()->SetRangeUser(0,50);
//
// TLine *tenline_1 = new TLine(0,10,40,10);
// TLine *tenline_tl = new TLine(40,10,40,0);
// TLine *fiveline_1 = new TLine(0,5,180,5);
// TLine *fiveline_tl = new TLine(180,5,180,0);
// tenline_1->SetLineStyle(2);
// tenline_tl->SetLineStyle(2);
// fiveline_1->SetLineStyle(2);
// fiveline_tl->SetLineStyle(2);
// tenline_1->SetLineWidth(2);
// tenline_tl->SetLineWidth(2);
// fiveline_1->SetLineWidth(2);
// fiveline_tl->SetLineWidth(2);
// tenline_1->Draw("same");
// tenline_tl->Draw("same");
// fiveline_1->Draw("same");
// fiveline_tl->Draw("same");
//
// TLegend *leg1 = new TLegend(0.1293878,0.5787037,0.295102,0.9074074);
// leg1->SetFillColor(0);
// leg1->AddEntry(gr_bi,"{}^{214}Bi All generators","l");
// leg1->AddEntry(gr_tl,"{}^{208}Tl Bulk of the foil","l");
// leg1->Draw("same");
// c1->SaveAs("/home/vagrant/PhD/PhDYear3/Background/AnalysisCode/Plots/relative_error_tl.root");

}

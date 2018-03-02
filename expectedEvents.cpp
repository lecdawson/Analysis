//Macro to plot the number of expected 1e1a events for each generator.
//Convert percentage efficiencies to numbers
double efficiency_bulk=0.0294;
double efficiency_surf=0.1007;
double efficiency_wire=0.0159;
//convert activities from mBq to Bq
double activity_bulk=0.0154;
double activity_surf=0.00018;
double activity_wire=0.0455;

double_t bulkExpected(double t)
{
  t_in_seconds=t*24*60*60;
  double expected_events_bulk = (efficiency_bulk*activity_bulk*t_in_seconds);
  return expected_events_bulk;
}
double_t surfExpected(double t)
{
  t_in_seconds=t*24*60*60;
  double expected_events_surf = (efficiency_surf*activity_surf*t_in_seconds);
  return expected_events_surf;
}
double_t wireExpected(double t)
{
  t_in_seconds=t*24*60*60;
  double expected_events_wire = (efficiency_wire*activity_wire*t_in_seconds);
  return expected_events_wire;
}

void expectedEvents()
{
  TCanvas *c1= new TCanvas;
  TF1 *f1 = new TF1("expectedEvents","bulkExpected(x)",1,100);
  TF1 *f2 = new TF1("expectedEvents","surfExpected(x)",1,100);
  TF1 *f3 = new TF1("expectedEvents","wireExpected(x)",1,100);
  f1->Draw();
  f2->Draw("SAME");
  f3->Draw("SAME");
  c1->Update();
  c1->SetLogx();
  c1->SetLogy();

  f1->SetLineColor(kBlack);
  f2->SetLineColor(kBlue);
  f3->SetLineColor(kRed);

  f1->SetTitle("Expected number of events for varying exposure");
  f1->GetYaxis()->SetTitle("Number of expected events");
  f1->GetXaxis()->SetTitle("Exposure[days]");
  f1->GetYaxis()->SetRangeUser(0.1,10000);

  leg = new TLegend(0.5,0.7,0.79,0.79);
  leg->AddEntry(f1,"Bulk of foil","l");
  leg->AddEntry(f2,"Surface of foil","l");
  leg->AddEntry(f3,"Tracker wires","l");
  leg->Draw();
}

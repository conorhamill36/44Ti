//ROOT macro for reading in the TNtuple
// daid

// TFile *f = new TFile("data/data_ti4.64_bohr.dat.root");
//TFile *f = new TFile("data/data_ti4.7.dat.root");
// TFile *f = new TFile("data/data_ti4.64.dat.root");
//TFile *f = new TFile("data/data_ti4.63.dat.root");
// TFile *f = new TFile("data/data_ti4.6.dat.root");
//TFile *f = new TFile("data/data_ti4.58.dat.root");
// TFile *f = new TFile("data/data_ti4.5.dat.root");
// TFile *f = new TFile("data/data_ti4.3.dat.root");
// TFile *f = new TFile("data/data_ti4.0_bohr.dat.root");
//TFile *f = new TFile("data/data_ti4.3_bohr.dat.root");
//TFile *f = new TFile("data/data_ti4.3-ap.dat.root");
//TFile *f = new TFile("data/data_aluminium.dat.root");
//TFile *f = new TFile("data/test_reaction123_daid.dat.root");
//TFile *f = new TFile("data/test_reaction123.dat.root");
// TFile *f = new TFile("data/test_reaction_conor_1.dat.root");
// TFile *f = new TFile("data/test_reaction_conor_2.dat.root");
// TFile *f = new TFile("data/data_conor_ti2.5.dat.root");
// TFile *f = new TFile("data/data_conor_ti4.0.dat.root");
// TFile *f = new TFile("data/data_conor_ti6.62.dat.root");
// TFile *f = new TFile("data/data_conor_al_test6.62.dat.root");
// TFile *f = new TFile("data/data_conor_al6.62.dat.root");
// TFile *f = new TFile("data/data_conor_si3n41.00.dat.root");
//TFile *f = new TFile("data/data_conor_ti4.0_150torr.dat.root");
//TFile *f = new TFile("25Mg_d_p_run15_16degrees.txt.root");
// TFile *f = new TFile("data/data_conor_ti_6.00_200torr_2.8MeVu.dat.root");
// TFile *f = new TFile("data/data_conor_ti_6.00_200torr_2.2MeVu.dat.root");
TFile *f = new TFile("data/data_conor_al_4.00_200torr_1.90MeVu.dat.root");

// const char *file_name="data/datTFile *f = new TFile("data/data_conor_ti_3.00_200torr_1.7MeVu.dat.root");

// file_name="data/data_conor_si3n4_1.00_200torr_1.88MeVu.dat.root";
// TFile *f = new TFile(file_name);

//Getting variables out of file name



// Make sure this is correct if you change the fortran outputs!
const Int_t columns=3;

void histogram(const int entries, TNtuple *ntuple){
  TCanvas *c1 = new TCanvas();
  c1->Divide(1,2);
  Float_t p[entries];
  char parameter[2];
  Float_t theta[entries], de[entries], e[entries], etotal[entries];
  for (Int_t i=0;i<columns;i++){
    sprintf(parameter,"p%d",i);
    ntuple->SetBranchAddress(parameter,&p[i]);
  }
  for (Int_t i=0;i<entries;i++){
    ntuple->GetEntry(i);
    theta[i]=p[0];
    de[i]=p[1];
    e[i]=p[2];
   etotal[i]=de[i]+e[i];
  }
  int xbin,xmin,xmax,ybin,ymin,ymax;
  xbin=120;ybin=100;xmin=0;xmax=22;ymin=0;ymax=10;
  TH2F *hdE_E = new TH2F("hdE_E","#DeltaE-E 4.64 um Ti",xbin,xmin,xmax,ybin,ymin,ymax);
  hdE_E->GetXaxis()->SetTitle("Energy (MeV)");
  hdE_E->GetYaxis()->SetTitle("Energy Loss (MeV)");

  //Getting variables out of file name
  // cout << file_name[7] << endl;
  // std::string file_name_string(file_name);
  // cout << file_name_string << endl;
  // std::string thickness(file_name_string.substr(22,4));
  // std::string pressure(file_name_string.substr(27,3));
  // std::string material(file_name_string.substr(16,4));
  // cout << thickness << pressure << material << endl;
  // std::string energy(file_name_string.substr(30,4));
  // std::string file_name_substring(file_name_string.substr(20,30));
  // cout << file_name_substring << endl;
  // cont char *file_name_subchar = file_name_substring.c_str();




  // hdE_E->SetTitle(file_name);
  xmin=0;xmax=22;
  xbin=(xmax-xmin)*10;
  TH1F *hESpectrum = new TH1F("hESpectrum","Energy Spectrum",xbin,xmin,xmax);
  hESpectrum->GetXaxis()->SetTitle("Total Energy (MeV)");
  hESpectrum->GetYaxis()->SetTitle("Counts");
  for (Int_t i=0;i<entries;i++){
    hdE_E->Fill(e[i],de[i]);
    hESpectrum->Fill(etotal[i]);
  }

  c1->cd(1);
  hdE_E->Draw("COLZ");
  c1->cd(2);
  hESpectrum->SetFillColor(kBlue);
  hESpectrum->Draw();
  return;

}

// We use this hack to define the number of entries dynamically
void in(){


  TNtuple *myNTuple;
  myNTuple = (TNtuple*)(f->Get("ntuple"))->Clone("myNTuple");
  const int entries = myNTuple->GetEntries();
  histogram(entries, myNTuple);
  return;
}

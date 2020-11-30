//ROOT macro for reading in the TNtuple
// daid

//TFile *f = new TFile("data/test_reaction123.dat.root");
const Int_t columns=3; //be wary of this
TFile *f = new TFile("data/daid2018.dat.root");

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
    theta[i]=p[0]; //could be lab frame of proton?
    de[i]=p[1];
    e[i]=p[2];
    etotal[i]=de[i]+e[i];
  }
  int xbin,xmin,xmax,ybin,ymin,ymax;
  xbin=120;ybin=100;xmin=0;xmax=18;ymin=0;ymax=10;
  TH2F *hdE_E = new TH2F("hdE_E","#DeltaE-E nominal test example",xbin,xmin,xmax,ybin,ymin,ymax);
  hdE_E->GetXaxis()->SetTitle("Energy (MeV)");
  hdE_E->GetYaxis()->SetTitle("Energy Loss (MeV)");
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

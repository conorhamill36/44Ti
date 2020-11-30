//ROOT macro
// reading in some two column data, plotting it, fitting it, and outputting the gaussian peak+sigma
//21 Nov 2010 21:13:48 
//daid
#include <iomanip> // for setprecision call
void plot_energy(const char *beam="",Int_t energymax=0,Int_t pressure=0)
{
Int_t manual=0;
if (energymax==0){
	manual=1;
}
Int_t i,j;
ifstream fin1, fin2;
// ROOT is bad with ASCII data -- let's count the lines
fin1.open("energies.txt");
Int_t w;
while (!fin1.eof()) { string blah; fin1 >> blah; w= w+1;}w=(w-1)/2;
fin1.close();
const Int_t p = w;
Double_t E[p], counts[p], countsmax, peakE=0;
countsmax=0;
fin2.open("energies.txt");

for(i=0;i<(p);i++){ 
fin2 >> E[i]; 
fin2 >> counts[i];
if (counts[i]>countsmax)
	countsmax=i;
}
fin2.close();
peakE=E[countsmax];

// Set up the style of the plots
gStyle->SetPalette(1);
gStyle->SetOptFit();
gStyle->SetLineColor(kBlack);
gStyle->SetFrameFillColor(kWhite);
gStyle->SetFrameLineColor(kBlack);
gStyle->SetFrameBorderMode(kWhite);//remove the hidden red border line
gStyle->SetTitleFillColor(kWhite);
gStyle->SetStatColor(kWhite);

// Define the canvas and make it a 2x2 square for printing purposes.
c1 = new TCanvas();
c1->SetFillColor(kWhite);
c1->SetLineColor(kBlack);
c1->SetFrameFillColor(kWhite);
c1->SetFrameLineColor(kBlack);
c1->Divide(2,2);
c1->cd(1);

Double_t *x = E;
Double_t *z = counts;
TGraph *Graph1 = new TGraph(p,x,z);
Graph1->Draw("AP");
Graph1->SetMarkerStyle(20);
Graph1->SetMarkerSize(0.5);
Graph1->SetMarkerColor(kBlue);
char plot_title[200];
if ( beam=="" && pressure==0 && energymax==0){
  sprintf(beam,"%s","^{44}Ti");
  pressure=4.64;
  energymax=1300;
}
sprintf(plot_title,"%s E_{beam} vs. Counts @ Entrance, 6.62\mum Al, %d MeV",beam,energymax);

Graph1->SetTitle(plot_title);
sprintf(plot_title,"%s E_{beam} (MeV)",beam);
Graph1->GetXaxis()->SetRangeUser(1000,1200);
Graph1->GetXaxis()->SetTitle(plot_title);
Graph1->GetXaxis()->CenterTitle(true);
Graph1->GetYaxis()->SetTitle("Counts per 100 keV");
Graph1->GetYaxis()->CenterTitle(true);

/*
Double_t par[3];
fit = new TF1("fit","gaus");
Graph1->Fit("fit","Q");
fit->GetParameters(&par[0]);
*/
//Double_t peakE = par[1]+par[2];// the best-guess for the RIB energy with best transmission is something like Mean+sigma, which are the parameters from the fit used here
// for basic reasoning of this peak energy, the best transmitted ions are at the most forward angles with the least straggling

ofstream fout;
fout.open("peakE.txt");
fout << setprecision(4);
fout << peakE << endl;
fout.close();
if (manual==0){
c1->SaveAs("energies.ps");
// this is meant to be called from a script, which doesn't want to keep ROOT open, so kill ROOT
gApplication->Terminate();}
}

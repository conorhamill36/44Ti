{
//#include "Riostream.h"
//#include <TH2F.h>
//#include <TGraph.h>

ifstream fEMeasured,fECalculated;
ofstream fEcm;

fEMeasured.open("after_subtract_background_runs.txt");
fECalculated.open("E_RECOIL_2_5000_3digits.DAT");

fEcm.open("after_subtract_background_Ecm.txt");

Float_t EM[4000][2];  //store measured proton energy and count
Float_t EC[5000][2];  //store calculated Ecm and proton energy from table
//Float_t Ecm[4000][2];  //store final Ecm and count

Float_t * x = new Float_t[4000];   //for graph. x stores Ecm and y stores count
Int_t*    y = new Int_t[4000];


//TH1F *hPsdSsdE0c = new TH1F("hPsdSsdEc", "SSD E + PSD E", 4096, 0, 4096*5);
//TH2F *hPsdSsdE0c = new TH2F("hPsdSsdE0c", "PSD E + SSD E", 128, 0, 4096*4, 128, 0, 4096); 

Int_t i=0,j=0,k=0,index=0;
Int_t NEMeasured,NECalculated;
Float_t TempEnergy;
Int_t    TempCount;

Int_t NEcm;    // # of values of ECalculated Ecm corresponding to the ECalculated proton 
               // energies meeting the condition for the same EMeasured  
               //       |EPCalculated-EPMeasured|<5 (keV)
Float_t TEcm; // the sum of these NEcm Ecm
Float_t AEcm; // the average of these NEcm Ecm

Int_t pos;


while(!fEMeasured.eof())
   {   
     fEMeasured>>TempEnergy;
     fEMeasured>>TempCount;
     if (TempCount>0)
       {  
        EM[i][0]=TempEnergy;
        EM[i][1]=TempCount;
        i++;
       }
       //EM[i][0] is the measured Ep(unit:bin),EM[i][1] is count
        
    }
   
NEMeasured=i;

Int_t TempEcm;
while(!fECalculated.eof())
   {
     fECalculated>>TempEnergy;     //skip the first column in the DAT file which is E(AL)
     fECalculated>>TempEcm;
     fECalculated>>TempEnergy;

     if (TempEnergy>0)
       {
        EC[k][0]=1000*TempEcm;     //EC[k][0] is Ecm, EC[k][1] is the calculated proton energy. unit:MeV
        EC[k][1]=1000*TempEnergy;  //convert to unit: keV
        k++;
       }
       else
        break;
   }

NECalculated=k;

/*    search in EC[k][1] the calculated Ep matching the measured Ep    */
Int_t Difference;

for(i=0;i<NEMeasured;i++)
   {
     TempEnergy=5*EM[i][0];     // measured Ep in EM is in unit bin. 1bin=5keV
     TempCount =EM[i][1];
      
     index = NMCalculated/2;
     
     Difference =TempEnergy-EC[index][1];

     while(abs(Difference)>5)
       {
         if (Difference >0)
            index=index+index/2;
         else
            index=index/2;
         Difference =TempEnergy-EC[index][1];
       }

     NEcm =1;
     TEcm =EC[index][1];
     pos=index;	      
//==================================================  
     index=pos-1;
     Difference =TempEnergy-EC[index][1]
     while(abs(Difference)<=5)
       {
          NEcm++;
          TEcm=TEcm+EC[index][1];
          index--;
          
          if (index<0) break;
       }

//==================================================
     index=pos+1;
     Difference =TempEnergy-EC[ndex][1]
     while(abs(Difference)<=5)
       {
          NEcm++;
          TEcm=TEcm+EC[index][1];
          index++;
          
          if (index>NECalculated) break;
       }

 //=================================================

     AEcm = TEcm/NEcm;
  //   Ecm[i][0] = AEcm;
  //   Ecm[i][1] = TempCount;
     x[i]=AEcm;
     y[i]=TempCount;
     fEcm<<AEcm<<"   "<<TempCount<<endl;
   }  
//end for

//===================================================
c1 = new TCanvas("c1","After subtracting background",200,10,700,500);
c1->SetFillColor(42);
c1->SetGrid();

gr = new TGraph(NEMeasured,x,y);
gr->SetLineColor(2);
gr->SetLineWidth(4);
gr->SetMarkerColor(4);
gr->SetMarkerStyle(21);
gr->SetTitle("Ecm After subtracting background");
gr->GetXaxis()->SetTitle("Ecm");
gr->GetYaxis()->SetTitle("Count");
gr->Draw("ACP");

// TCanvas::Update() draws the frame, after which one can change it
c1->Update();
c1->GetFrame()->SetFillColor(21);
c1->GetFrame()->SetBorderSize(12);
c1->Modified();


fEMeasured.close();
fECalculated.close();

fEcm.close();

//myfile->Write();
//new TBrowser();
}

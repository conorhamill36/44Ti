{

#include <iomanip>	
#include <iostream>
#include <TH1F.h>
//#include <TGraph.h>

ifstream fEMeasured,fECalculated;
ofstream fEcm;

fEMeasured.open("after_subtract_background_4096bin.txt");
fECalculated.open("E_RECOIL_2_5000_3digits.DAT");

fEcm.open("after_subtract_background_Ecm.txt");

//debug
//cout<<"debug1"<<endl;

Float_t EM[4000][2];  //store measured proton energy and count
Float_t EC[5000][2];  //store calculated Ecm and proton energy from table
//Float_t Ecm[4000][2];  //store final Ecm and count

//=======================================================
Float_t* x=new Float_t[4000];   //for graph. x stores Ecm and y stores count
Int_t*    y=new Int_t[4000];

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

TFile *myfile = new TFile("Ecm_after_correcting_E_loss.root","RECREATE");
TH1F *hEcm0 = new TH1F("hEcm0", "Ecm", 4096,0,4096);

//debug
//cout<<"debug2"<<endl;

while(!fEMeasured.eof())
   { 
     fEMeasured>>TempEnergy;
     fEMeasured>>TempCount;


     if (TempCount>0)
       {  
//debug
//cout<<"EM read #: "<<i+1<<endl;

        EM[i][0]=TempEnergy;
        EM[i][1]=TempCount;
        i++;
       }
       //EM[i][0] is the measured Ep(unit:bin),EM[i][1] is count
        
   }
   
NEMeasured=i;
//debug
//cout<<"The last measured proton energy:"<<NEMeasured<<"  "<<EM[NEMeasured-1][0]<<endl;

Float_t TempEcm;

while(!fECalculated.eof())
   {
     fECalculated>>TempEnergy;    //skip the first column in the DAT file which is E(AL)
     fECalculated>>TempEcm;
     fECalculated>>TempEnergy;



     if (TempEnergy>0)
       {
//debug
//cout<<"EC read line: "<<k+1<<endl;

//debug
//cout<<"The Ecm & Ep: "<<TempEcm<<"  "<<TempEnergy<<endl;

        EC[k][0]=1000*TempEcm;     //EC[k][0] is Ecm, EC[k][1] is the calculated proton energy. unit:MeV
        EC[k][1]=1000*TempEnergy;  //convert to unit: keV
        k++;
       }
     else
       break;
   }

NECalculated=k;

//debug
//cout<<"The last calculated proton energy:"<<NECalculated<<"  "<<EC[NECalculated-1][0]<<endl;

/*    search in EC[k][1] the calculated Ep matching the measured Ep    */
Float_t Difference;
Int_t LowIndex,HighIndex;


//cout<<"# of Measured: "<<NEMeasured<<endl;
Int_t n; 
// some measured energies are out of range of the calculated proton energy. for
// those we don't need to find the corresponding Ecm  

Float_t ECMax=EC[0][1];


for(i=0;i<NEMeasured;i++)
   {
     TempEnergy=5*EM[i][0];     // measured Ep in EM is in unit bin. 1bin=5keV
     TempCount =EM[i][1];
     
//==============================================================     
//====================   important ! ===========================
      
     if (TempEnergy>(ECMax+5))    //EC[0][1] is the maximum of the calculated Ep
          break;
//==============================================================
//==============================================================
		    

     index = NECalculated/2;
     LowIndex=0;
     HighIndex=NECalculated;

     Difference =TempEnergy-EC[index][1];
//debug
//cout<<"Index :"<<index<<endl;
//cout<<"difference: "<<Difference<<endl;
//cout<<"EM  EC :"<<TempEnergy<<"  "<<EC[index][1]<<endl;


     while(abs(Difference)>5.0&&(index>=0)&&(index<=NECalculated))
       {
         if (Difference >0.0)
            HighIndex=index-1;   // data value in EC is from biggest to smallest sequentlly
         else
            LowIndex=index+1;
        
         index = (LowIndex+HighIndex)/2;
  
//         if ((index>NECalculated) || (index<0))
             
          
	 
         Difference =TempEnergy-EC[index][1];

//debug
//if (index>0)
//{
//cout<<"Index :"<<index<<endl;
//cout<<"Difference: "<<Difference<<endl;
//}
//else
//{
//cerr<<"Searching Error!"<<endl;
//break;
//}
       }

     NEcm =1;
     TEcm =EC[index][0];;
     pos=index;	 

//debug
//cout<<"the pos of the "<<i+1<<"th is :"<<pos<<endl;
     
//==================================================  
     if (pos>0)
       {	     
         index=pos-1;
         Difference =TempEnergy-EC[index][1];
         while(abs(Difference)<=5.0)
          {
           NEcm++;
           TEcm=TEcm+EC[index][0];
           index--;
           if (index<0) break;
           Difference =TempEnergy-EC[index][1];
           
          }
       }
//==================================================
     if (pos<NECalculated)
       {	     
         index=pos+1;
         Difference =TempEnergy-EC[index][1];
         while(abs(Difference)<=5.0)
          {
           NEcm++;
           TEcm=TEcm+EC[index][0];
           index++;
           if (index>NECalculated) break;
           Difference =TempEnergy-EC[index][1];
           
          }
       }
 //=================================================

     AEcm = TEcm/NEcm;
  //   Ecm[i][0] = AEcm;
  //   Ecm[i][1] = TempCount;
     x[i]=AEcm;
     y[i]=TempCount;
     
     for (n=0;n<TempCount;n++)
	hEcm0->Fill(AEcm);
     
     fEcm<<setprecision(1)<<setw(10)<<fixed;
     fEcm<<AEcm;
     fEcm<<setw(4);
     fEcm<<TempCount<<endl;
//debug     cout<<"# of measured: "<<NEMeasured<<endl;
   }

//Debug
//cout<<"# of measured protons: "<<NEMeasured<<endl;
//cout<<"# of searching:        "<<i<<endl;
//cout<<"This is the end!"<<endl;
//end for

cout<<"Finish searching!"<<endl;

//===================================================
/*c1 = new TCanvas("c1","After subtracting background",200,10,700,500);
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

*/

fEMeasured.close();
fECalculated.close();

fEcm.close();

myfile->Write();
new TBrowser();

}

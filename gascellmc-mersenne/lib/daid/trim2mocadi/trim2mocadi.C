// ---------------------------  trim_exotic.c  ---------------------------
//
// This macro converts the output file of TRIM ("TRANSMIT.txt") to the 
// input file of either the standard version of MOCADI ("test_read.in") 
// 
// The charge state is set by the user.
//
// Marco Mazzocco : Last version: March 21st 2008
//
// daid 2009 May 13 22:28:37 changed nf/nsf from 0.0 to 1.0, otherwise no particles are transmitted
// daid - changed to output energies to a text file for plotting with ROOT
// daid 26 Nov 2010 05:01:20 changed to allow command line parameters instead of user input for shell script calling
// daid 26 Nov 2010 05:04:37 commented out information for mocadi.dat since it's a local version I never use

#include <iostream>
#include <fstream>
#include <math.h>
#include <getopt.h> // so we can take command line options for running by script
using namespace std;

int main(int argc, char **argv)
   {

   // external variables
   
   int mass, event_number;
   

   // internal variables
   
   int event_index, atomic_number;
   float energy,total_energy,pos_z,pos_x,pos_y,ang_z,ang_x,ang_y;
   int max_energy;
   //bins per MeV.  2 means 0.5 MeV bins
   int energy_bins = 1;
   char first_char = 'T';
   int no_electrons, total_events = 0;

	int Zflag = 0;
	int aflag = 0;
	int zflag = 0;
	int nflag = 0;
	int eflag = 0;
	int c;
	opterr = 0;
	while ((c = getopt (argc, argv, "Z:a:z:n:e:")) != -1)
         switch (c)
           {
           case 'Z':
             Zflag = 1;
		sscanf(optarg,"%d",&atomic_number);
             break;
           case 'a':
             aflag = 1;
		sscanf(optarg,"%d",&mass);
             break;
           case 'z':
             zflag = 1;
		sscanf(optarg,"%d",&no_electrons);
             break;
           case 'n':
             nflag = 1;
		sscanf(optarg,"%d",&event_number);
             break;
           case 'e':
             eflag = 1;
		sscanf(optarg,"%d",&max_energy);
             break;
           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             //abort ();
	     return(0);
           }

   // input and output files

   //FILE *energies, *finput, *foutput, *foutput2;
   FILE *energies, *finput, *foutput;

   finput=fopen("TRANSMIT.txt","r");
   	if(finput==NULL)
  		{
		fprintf(stderr,"File not opened1\n");	
        	return(-1);
		}

   foutput=fopen("test_read.in","w");
   	if(foutput==NULL)
  		{
		fprintf(stderr,"File not opened2\n");	
        	return(-1);
		}

/*   foutput2=fopen("mocadi.dat","w");
   	if(foutput2==NULL)
  		{
		fprintf(stderr,"File not opened2\n");	
        	return(-1);
		}*/

   energies=fopen("energies.txt","w");
   	if(energies==NULL)
  		{
		fprintf(stderr,"File not opened4\n");	
        	return(-1);
		}


   // output files for the energy distribution

   int ene[800];

   for(int m = 0 ; m < 800; m++)
	{
	ene[m] = 0;
	}


   // input parameters

   fprintf(stderr,"---------------------------trim2mocadi----------------------------\n");
   fprintf(stderr,"-------------------------Input Parameters-------------------------\n");
   fprintf(stderr,"Insert the atomic number:   Z = ");
   if (Zflag == 0){
   fscanf(stdin,"%d",&atomic_number);}
   else{
   fprintf(stderr,"%d\n",atomic_number);}
   fprintf(stderr,"Insert the mass number:     A = ");
   if (aflag == 0){
   fscanf(stdin,"%d",&mass);}
   else{
   fprintf(stderr,"%d\n",mass);}
   fprintf(stderr,"Insert the number of electrons: ");
   if (zflag == 0){
   fscanf(stdin,"%d",&no_electrons);}
   else{
   fprintf(stderr,"%d\n",no_electrons);}
   fprintf(stderr,"Insert the number of generated events: ");
   if (nflag == 0){
   fscanf(stdin,"%d",&event_number);}
   else{
   fprintf(stderr,"%d\n",event_number);}
   fprintf(stderr,"Insert the maximum energy in MeV quanta (overestimate okay): ");
   if (eflag == 0){
   fscanf(stdin,"%d",&max_energy);}
   else{
   fprintf(stderr,"%d\n",max_energy);}
   fprintf(stderr,"------------------------------------------------------------------\n");

   // output header

   fprintf(foutput,"********** MOCADI ascii listmode output file *********\n");
   fprintf(foutput,"*(mass,charge): primary, fragment1, 2....\n");
   fprintf(foutput,"%d %d 0.000000 0\n", mass, atomic_number);
   fprintf(foutput,"*save point, fragment, teilchen(1-14): x[cm], x'[mrad], y[cm], y'[mrad], energy[AMeV], time[us], mass[amu], z, electrons, nf/nsf,range[mg/cm2], tof[us], deltaE[MeV]\n");

   // skipping the first 12 lines

   char temp[2000];

   for(int f = 0; f < 12; f++)
   	int r = fscanf(finput,"%[^\n]\n",temp);


   // main code

   for(int i = 0; ; i++)
      	{ 

	// input reading
	
	fscanf(finput, "%c",&first_char);
 
      	fscanf(finput,"%d\t",&event_index);

      	fscanf(finput,"%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",&atomic_number,&energy,&pos_z,&pos_x,&pos_y,&ang_z,&ang_x,&ang_y);
      

	// units converter

	energy    = energy/1000000; 	// energy (in MeV)
	pos_z     = pos_z/100000000;  	// depth (in cm) z for MOCADI
	pos_x     = pos_x/100000000;  	// lateral position (in cm) x for MOCADI
	pos_y     = pos_y/100000000;  	// lateral position (in cm) y for MOCADI
        ang_x = ang_x / ang_z *1000;	// angular divergence (in mrad) a for MOCADI
	ang_y = ang_y / ang_z *1000;	// angular divergence (in mrad) b for MOCADI
      	energy = energy/mass;   	// energy (in AMeV)


        if(energy <= 0)
		continue;
		

	total_energy = energy * mass;

       	for(int m = 0 ; m < (max_energy*energy_bins); m++)
       		{
		if( (total_energy >= (1./energy_bins)*m) && (total_energy < (1./energy_bins)*(m+1) ) )	
		//if( (total_energy >= 0.2*m) && (total_energy < 0.2*(m+1) ) )	
		++ene[m];
		}

      	/*fprintf(foutput2,"%d\t%d\t%f\t%f\t%f\t0\t%f\t%f\t%d\n",
	atomic_number,mass,total_energy,pos_x,pos_y,ang_x,ang_y,no_electrons);*/


	// filling mocadi input file

      	fprintf(foutput,
	"  1   0\t%f\t%f\t%f\t%f\t%f\t0.0\t%d\t%d\t%d\t1.0\t0.0\t0.0\t0.0\n",
        pos_x,ang_x,pos_y,ang_y,energy,mass,atomic_number,no_electrons);

	total_events = total_events +1;

      	if(event_index==event_number)
		break;

       	}


  //fprintf(foutput,"2743\n");

  // output file filling
	
  for(int p = 0 ; p < (max_energy*energy_bins); p++)
	{
        fprintf(energies, "%f \t %d\n", (1./energy_bins)*p + 0.1, ene[p]);
//	cout << "energies: " << p << endl;
	}


  // file closure

  fclose(energies);
  fclose(finput);
  fclose(foutput);
  //fclose(foutput2);
  
  }

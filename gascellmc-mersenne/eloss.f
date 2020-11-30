c      eloss subroutine
c     inputs - elosstype, ein and thick
c     output - eout

      subroutine eloss(elosstype,ein,eout,thick)
      integer elosstype,i,linebefore,lineafter
      double precision ein,eout,thick,frac,rangebefore,rangeafter
      double precision d_rangebefore,d_rangeafter
      double precision eld1(6,109)

!      COMMON /mem1/ eld1



      if(ein.lt.0.02)then       !stopped
         eout=0.0
         goto 1000
      endif

                                


!      elosstype 
                                ! 1 is 18f in ch2
                                ! 2 is 18o in ch2
                                ! 3 is p in ch2
                                ! 4 is a in ch2
                                ! 5 is 12c in ch2
                                ! 6 is 18f in Si
                                ! 7 is 18o in Si
                                ! 8 is p in Si
                                ! 9 is a in si
                                !10 is 12c in Si
                                !11 is 15O in CH2
                                !12 is 15N in Ch2
                                !13 is 15O in Si
                                !14 is 15N in Si
                                !15 is 18F in Au
                                !16 is 18O in Au
                                !17 is 44Ti in He 200T, all lengths in mm
                                !18 is 44Ti in Al
                                !19 is p in Al
                                !20 is p in He 200T, all lengths in mm
                                !21 is 47V in He 200T, all lengths in mm
                                !22 is 47V in Al 
                                !23 is 4He in He 200 T, lengths in mm
                                !24 is 4He in Al
                                !25 is 44Ti in Si
                                !26 is 47V in Si
                                !27 is 44Ti in My
                                !28 is 44Ti in Au
                                !29 is 14O in Al
                                !30 is 14O in Au
                                !31 is 14O in My
                                !32 is 14O in He200Torr
                                !33 is 17F in He200Torr
                                !34 is 17F in Al
                                !35 is 17F in Si
                                !36 is 14O in Si

                                !37 is 21Na in Al
                                !38 is 21Na in Au
                                !39 is 21Na in CH2
                                !40 is 21Na in He200Torr
                                !41 is 14N in My
                                !42 is 14N in Al
                                !43 is 14N in Au
                                !44 is 14N in Si
                                !45 is 14N in He200Torr

                                !101 is 44Ti in Ti
                                

      if(elosstype.eq.1)then
         open(7,status='old',file='lib/18F_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.2)then
         open(7,status='old',file='lib/18O_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.3)then
         open(7,status='old',file='lib/p_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.4)then
         open(7,status='old',file='lib/4He_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.5)then
         open(7,status='old',file='lib/12C_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.6)then
         open(7,status='old',file='lib/18F_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.7)then
         open(7,status='old',file='lib/18O_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.8)then
         open(7,status='old',file='lib/p_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.9)then
         open(7,status='old',file='lib/4He_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.10)then
         open(7,status='old',file='lib/12C_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.11)then
         open(7,status='old',file='lib/15O_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.12)then
         open(7,status='old',file='lib/15N_in_CH2.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.13)then
         open(7,status='old',file='lib/15O_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.14)then
         open(7,status='old',file='lib/15N_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.15)then
         open(7,status='old',file='lib/18F_in_Au.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.16)then
         open(7,status='old',file='lib/18O_in_Au.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.17)then
         open(7,status='old',file='lib/44Ti_in_He200T.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.18)then
         open(7,status='old',file='lib/44Ti_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.19)then
         open(7,status='old',file='lib/p_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.20)then
         open(7,status='old',file='lib/p_in_He.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.21)then
         open(7,status='old',file='lib/47V_in_He200T.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.22)then
         open(7,status='old',file='lib/47V_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.23)then
         open(7,status='old',file='lib/4He_in_He200T.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.24)then
         open(7,status='old',file='lib/4He_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.25)then
         open(7,status='old',file='lib/44Ti_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.26)then
         open(7,status='old',file='lib/47V_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.27)then
         open(7,status='old',file='lib/44Ti_in_My.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.28)then
         open(7,status='old',file='lib/44Ti_in_Au.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.29)then
         open(7,status='old',file='lib/14O_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.30)then
         open(7,status='old',file='lib/14O_in_Au.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.31)then
         open(7,status='old',file='lib/14O_in_My.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.32)then
         open(7,status='old',file='lib/14OinHe200Torr.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.33)then
         open(7,status='old',file='lib/17FinHe200Torr.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.34)then
         open(7,status='old',file='lib/17F_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.35)then
         open(7,status='old',file='lib/17F_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.36)then
         open(7,status='old',file='lib/14O_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif


      if(elosstype.eq.41)then
         open(7,status='old',file='lib/14N_in_My.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.42)then
         open(7,status='old',file='lib/14N_in_Al.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.43)then
         open(7,status='old',file='lib/14N_in_Au.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.44)then
         open(7,status='old',file='lib/14N_in_Si.dat')
         read(7,*) eld1
         close(7)
      endif
      if(elosstype.eq.45)then
         open(7,status='old',file='lib/14N_in_He200Torr.dat')
         read(7,*) eld1
         close(7)
      endif
      
      if(elosstype.eq.101)then
         open(7,status='old',file='lib/44Ti_in_Ti.dat')
         read(7,*) eld1
         close(7)
      endif
      
      
      if(elosstype.eq.102)then
         open(7,status='old',file='lib/44Ti_in_Si3N4.dat')
         read(7,*) eld1
         close(7)
      endif
      
      


      do i=1,109                 !calculte which line of SRIM dat file the start energy corresponds to
         if(ein.le.eld1(1,i))then
            linebefore=i-1
            lineafter=i
            frac1=(ein-eld1(1,i-1))
	    frac2=(eld1(1,(i))-eld1(1,i-1))
	    frac=frac1/frac2
            goto 100
         endif
      enddo
 100  continue



         rangebefore=eld1(4,lineafter-1)+frac*( eld1(4,lineafter) - eld1(4,lineafter-1) )
         d_rangebefore=(eld1(5,lineafter-1)+frac*( eld1(5,lineafter) - eld1(5,lineafter-1) ))/1.0e4
         rangeafter=rangebefore-thick
         
         if(rangeafter.le.0.03)then !stopped
            eout=0.0
            goto 1000
         endif

         do i=1,109 
            if(rangeafter.le.eld1(4,i))then
               linebefore=i-1
               lineafter=i
               frac1=(rangeafter-eld1(4,i-1))
	       frac2=(eld1(4,i)-eld1(4,i-1))
	       frac=frac1/frac2
               eout=eld1(1,linebefore)+frac*(eld1(1,lineafter)-eld1(1,linebefore)) 
               d_rangeafter=(eld1(5,linebefore)+frac*(eld1(5,lineafter)-eld1(5,linebefore)))/1.0e4
               goto 1000
            endif
         enddo
            



 1000 continue

!      write(6,*)dsqrt((d_rangebefore/rangebefore)**2+(d_rangeafter/rangeafter)**2)
!      write(6,*)real(ein),real(eout)
      

!      write(6,*)ein,eout
!      write(6,*)rangeafter

      return

      end

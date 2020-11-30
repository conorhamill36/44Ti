      subroutine smear(val_init,sigma,val_returned)

!      integer elosstype,i,linebefore,lineafter
      double precision val_init,sigma,val_returned,chosen_line,r,sarea
      double precision gauss(2,1000)
      integer i



!      if(val_init.lt.1e-5.or.sigma.le.1e-5)then       !stopped
!         val_returned=val_init
!      goto 299
!      endif

                                


      open(7,status='old',file='lib/gauss.dat')
      read(7,*) gauss
      close(7)
 100  continue



c      Gauss smearing of parameters.
c      THIS CODE WAS USED TO MAKE THE LOOK UP TABLE.
c      mean=500
c      sigma=100
c      amp=1/(sigma*sqrt(2*3.14159))
c
c      gaussarea=0
c
c
!      open(unit=8,status='unknown',file='/Users/alex/Documents/prog/S1195/gauss.dat')
!      do i=1,1000
!         y=amp*exp(-1 *((float(i)-mean)**2)/(2*sigma*sigma))
!         gaussarea=gaussarea+y
!         write(8,*)real(i),real(gaussarea)
!      enddo
!      close(8)

C     NOW WE CAN USE IT AND SCALE ANY SMEARING APPROPRIATELY
c     ...AND THIS IS DONE WITH A SUBROUTINE - SMEAR.F
c      Gauss smearing of parameters.
c      THIS CODE WAS USED TO MAKE THE LOOK UP TABLE.
c      mean=500
c      sigma=100
c      amp=1/(sigma*sqrt(2*3.14159))
c
c      gaussarea=0
c
c
!      open(unit=8,status='unknown',file='/Users/alex/Documents/prog/S1195/gauss.dat')
!      do i=1,1000
!         y=amp*exp(-1 *((float(i)-mean)**2)/(2*sigma*sigma))
!         gaussarea=gaussarea+y
!         write(8,*)real(i),real(gaussarea)
!      enddo
!      close(8)

C     NOW WE CAN USE IT AND SCALE ANY SMEARING APPROPRIATELY
c     ...AND THIS IS DONE WITH A SUBROUTINE - SMEAR.F      end


c     gauss data file has centroid at 500 and width 100
c     need to scale that

      r=rand(0)

      do i=1,1000
         
         sarea=gauss(2,i)
         if(r.ge.sarea)then
            chosen_line=gauss(1,i)
         else
            goto 200
         endif
      enddo
 200     continue

         val_returned=(sigma*(chosen_line-500)/100)+val_init

 299     continue
         

      return

      end

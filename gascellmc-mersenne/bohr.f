      subroutine bohr(elosstype,ein,thick,d_eout)

      integer elosstype
      DOUBLE PRECISION a_ion, a_medium, c1, c2, density, q_e, energy,ein
      DOUBLE PRECISION e_max, fwhm, k, m_e, m_u, n_a, permittivity_0
      DOUBLE PRECISION pi, x, xi, z_ion, z_medium,d_eout,thick,scaling

      scaling=4.9                 !gross scaling of Bohr estimate to reality.

C----67---------------------------------------------------------------72------80
C     Define some constants
C     Charge of electron (C)

      if(ein.le.0.001)then
         d_eout=0.0
         goto 998
      endif

      energy=ein
      q_e = 1.60217733D-19

C     Mass of electron (g)

      m_e = 9.1093897D-28

C     Unified atomic mass unit (g)

      m_u = 1.6605402D-24

C     Avagadro's number (/mol)

      n_a = 6.0221367D+23

C     Permittivity of free space (F/m)

      permittivity_0 = 8.854186D-12

      pi = 3.141592653589D+00

C----67---------------------------------------------------------------72------80
C     Announce program

!      WRITE( output_stream, 9000 )

C     Request atomic number, atomic mass and energy of ion.

!      WRITE( output_stream, 9010 )
!      READ( input_stream, * ) z_ion, a_ion, energy

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
                                !17 is 44Ti in He 200T
                                !18 is 44Ti in Al
                                !19 is p in Al
                                !20 is p in He 200 T
                                !21 is 47V in He 200T
                                !22 is 47V in Al
                                !23 is 4He in He 200 T
                                !24 is 4He in Al
                                !25 is 44Ti in Si
                                !26 is 47V in Si
                                !27 is 47V in My
                                !28 is 47V in Au
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


      if(elosstype.eq.1) then
         z_ion=9
         a_ion=18
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.2) then
         z_ion=8
         a_ion=18
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.3) then
         z_ion=1
         a_ion=1
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.4) then
         z_ion=2
         a_ion=4
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.5) then
         z_ion=6
         a_ion=12
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.6) then
         z_ion=9
         a_ion=18
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.7) then
         z_ion=8
         a_ion=18
         z_medium=14
         a_medium=18
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.8) then
         z_ion=1
         a_ion=1
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.9) then
         z_ion=2
         a_ion=4
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.10) then
         z_ion=6
         a_ion=12
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.11) then
         z_ion=8
         a_ion=15
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.12) then
         z_ion=7
         a_ion=15
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um
      endif
      if(elosstype.eq.13) then
         z_ion=8
         a_ion=15
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.14) then
         z_ion=7
         a_ion=15
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um
      endif
      if(elosstype.eq.15) then
         z_ion=9
         a_ion=18
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um
      endif
      if(elosstype.eq.16) then
         z_ion=8
         a_ion=18
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um
      endif
      if(elosstype.eq.17) then
         z_ion=22
         a_ion=44
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.18) then
         z_ion=22
         a_ion=44
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um
      endif
      if(elosstype.eq.19) then
         z_ion=1
         a_ion=1
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um
      endif
      if(elosstype.eq.20) then  !p in He
         z_ion=1
         a_ion=1
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.21) then  !47V in He
         z_ion=23
         a_ion=47
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.22) then  !47V in Al
         z_ion=23
         a_ion=47
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.23) then  !4He in He200T
         z_ion=2
         a_ion=4
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.24) then  !4He in Al
         z_ion=2
         a_ion=4
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.25) then  !44Ti in Si
         z_ion=22
         a_ion=44
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um!!
      endif
      if(elosstype.eq.26) then  !47V in Si
         z_ion=23
         a_ion=47
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um!!
      endif
      if(elosstype.eq.27) then  !44Ti in My
         z_ion=22
         a_ion=44
         z_medium=8*.333+6*.625+1*.0420 !mean from chem formula
         a_medium=16*.333+12*.625+1*.0420 !mean from chem formula
         density=1.397
         x=thick                !um!!
      endif
      if(elosstype.eq.28) then  !44Ti in Au
         z_ion=22
         a_ion=44
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um!!
      endif

      if(elosstype.eq.29) then  !14O in Al
         z_ion=8
         a_ion=14
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.30) then  !14O in Au
         z_ion=8
         a_ion=14
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um!!
      endif
      if(elosstype.eq.31) then  !14O in My
         z_ion=8
         a_ion=14
         z_medium=8*.333+6*.625+1*.0420 !mean from chem formula
         a_medium=16*.333+12*.625+1*.0420 !mean from chem formula
         density=1.397
         x=thick                !um!!
      endif
      if(elosstype.eq.32) then  !14O in 200Torr He
         z_ion=8
         a_ion=14
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.33) then  !17F in 200Torr He
         z_ion=9
         a_ion=17
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.34) then  !17F in Al
         z_ion=9
         a_ion=17
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.35) then  !17F in Si
         z_ion=9
         a_ion=17
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um!!
      endif
      if(elosstype.eq.36) then  !14O in Si
         z_ion=8
         a_ion=14
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um!!
      endif

      if(elosstype.eq.37) then  !21Na Al
         z_ion=11
         a_ion=21
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.38) then  !21Na in Au
         z_ion=11
         a_ion=21
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um!!
      endif
      if(elosstype.eq.39) then  !21Na in Ch2
         z_ion=11
         a_ion=21
         z_medium=(2*1+1*6)/3
         a_medium=(2*1)+(1*12)
         density=0.93
         x=thick                !um!!
      endif
      if(elosstype.eq.40) then  !21Na in He200Torr
         z_ion=11
         a_ion=21
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !um!!
      endif
      if(elosstype.eq.41) then  !14N in My (c10 H8 O4)
         z_ion=7
         a_ion=14
         z_medium=8*.333+6*.625+1*.0420 !mean from chem formula
         a_medium=16*.333+12*.625+1*.0420 !mean from chem formula
         density=1.397
         x=thick                !um!!
      endif
      if(elosstype.eq.42) then  !14N in Al
         z_ion=7
         a_ion=14
         z_medium=13
         a_medium=27
         density=2.699
         x=thick                !um!!
      endif
      if(elosstype.eq.43) then  !14N in Au
         z_ion=7
         a_ion=14
         z_medium=79
         a_medium=197
         density=19.311
         x=thick                !um!!
      endif
      if(elosstype.eq.44) then  !14N in Si
         z_ion=7
         a_ion=14
         z_medium=14
         a_medium=28
         density=2.33
         x=thick                !um!!
      endif
      if(elosstype.eq.45) then  !14N in He200Torr
         z_ion=7
         a_ion=14
         z_medium=2
         a_medium=4
         density=4.3e-5
         x=thick                !mm!!
      endif
      if(elosstype.eq.101)then  !44Ti in Ti
         z_ion=22
         a_ion=44
         z_medium=22
         a_medium=48
         density=4.5189
         x=thick                !um!!
      endif




C     Request atomic number, atomic mass, density and thickness of medium

      e_max = 4.0D+00 * m_e * a_ion * energy * 1.0D+03
     +        / ( m_u *  ( m_e + a_ion )**2.0D+00 )

      c1 = ( q_e**4.0D+00 * n_a * density * z_medium )
     +   / ( 16.0D+00 * pi * permittivity_0**2.0D+00 * A_medium * m_e )

      c1 = c1 * m_u / ( 1.0D+09 * q_e**2.0D+00 )


C     Calculate quantity xi in units of keV

      xi = c1 * z_ion**2.0D+00 * a_ion * x / energy

C     Calculate k

      k = xi / e_max
      
      c2 = ( q_e**4.0D+00 * n_a * density * z_medium )
     +     / ( 4.0D+00 * pi *  permittivity_0**2.0D+00 * A_medium)

      c2 = DSQRT( c2 )

C     Calculate constant of proportionality in units of keV

      c2 = c2 / ( 1.0D+03 * q_e )


C     Calculate standard deviation (sigma) of energy straggling
C     distribution in units of keV.
C     Thickness of medium in units of microns.

      d_eout = c2 * z_ion * DSQRT( x )/1000


C     Calculate full-width half-maximum (FWHM) of energy straggling
C     distribution in units of keV.

      IF ( k.LE.0.01D+00 ) THEN
       fwhm = 4.0D+00 * xi
      ELSEIF( k.GE.1.0D+00 ) THEN
       fwhm = 2.0D+00 * SQRT( 2.0D+00 * DLOG(2.0D+00) ) * d_eout
      ENDIF

      if(elosstype.le.5.or.elosstype.eq.11.or.elosstype.eq.12)d_eout=d_eout*1.25 !CH2 not C

      d_eout=d_eout*scaling

 998  continue

      return
      end

!      STOP




C----67---------------------------------------------------------------72------80

! 9000 FORMAT(/' Energy straggling (Bohr derivation)' )
! 9010 FORMAT(/' Enter Z, A and energy (MeV) of incident ion: ' $ )
! 9020 FORMAT( ' Enter Z, A, density (g/cm3) and thickness (um) of',
!     +        ' stopping medium: ' $ )
! 9030 FORMAT(/'      k = ', f10.4,
!     +       /' e(max) = ', f10.4, ' keV',
!     +       /'     xi = ', f10.4, ' keV' )
! 9040 FORMAT(/'  Width                                       Shape')
! 9050 FORMAT(/'  sigma = ', f8.2, ' keV  FWHM = ', f8.2, ' keV',
!     +       '   Landau' )
! 9060 FORMAT(/'  sigma = ', f8.2, ' keV                    '
!     +       '    Skewed Gaussian' )
! 9070 FORMAT(/'  sigma = ', f8.2, ' keV  FWHM = ', f8.2, ' keV',
!     +       '   Gaussian' )
! 9080 FORMAT(/'  sigma = ', f8.2, ' keV  FWHM = ', f8.2, ' keV',
!     +       '   Gaussian (if dE/E < 10%)' )
!
!      END
!
C----67---------------------------------------------------------------72------80

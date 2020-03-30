c************************************************************************
c**                                                                    **
c**           MadGraph/MadEvent Interface to FeynRules                 **
c**                                                                    **
c**          C. Duhr (Louvain U.) - M. Herquet (NIKHEF)                **
c**                                                                    **
c************************************************************************

      subroutine setpara(param_name,readlha)
      implicit none

      character*(*) param_name
      logical readlha

      include 'coupl.inc'
      include 'input.inc'

      integer maxpara
      parameter (maxpara=5000)
      
      integer npara
      character*20 param(maxpara),value(maxpara)

      double precision Pi
      common/FRPi/ Pi
      Pi = 3.141592654 

      if(readlha) then
         call LHA_loadcard(param_name,npara,param,value)
         include 'param_read.inc'
      end if
      call coup(readlha)

      return

      end




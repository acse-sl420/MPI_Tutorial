indexed.f90
---------
Set up the lengths and displacements arrays so that the cells marked with * are
sent and the cells marked with - are not. Remember that displacements are 0 based
even in Fortran

**--***-

different.f90
-----------
Set up a different but valid set of lengths and displacements so that the data
is reshaped during the send

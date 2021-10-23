#!/bin/bash

date

mpiexec -np 64 --hostfile hostfile --oversubscribe /Users/dol4/Desktop/radlib_fds/Build/mpi_gnu_osx_64/fdsradlib norad.fds

date

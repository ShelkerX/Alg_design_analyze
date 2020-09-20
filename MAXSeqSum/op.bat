@echo off
::setlocal EnableDelayedExpansion
::set min = -9
::set max = 9
title Comparison of algorithms for sum of maximal subsequence 
@echo 1
randarr.exe 1 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt & maxseqsumtest.exe 0 arr.txt
echo.
@echo 10
randarr.exe 10 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt & maxseqsumtest.exe 0 arr.txt
echo.
@echo 100
randarr.exe 100 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt & maxseqsumtest.exe 0 arr.txt
echo.
@echo 1000
randarr.exe 1000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt & maxseqsumtest.exe 0 arr.txt
echo.
@echo 2000
randarr.exe 2000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt & maxseqsumtest.exe 0 arr.txt
echo.
@echo 5000
randarr.exe 5000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt
echo.
@echo 7000
randarr.exe 7000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt
echo.
@echo 10000
randarr.exe 10000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt
echo.
@echo 100000
randarr.exe 100000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt & maxseqsumtest.exe 1 arr.txt
echo.
@echo 1000000
randarr.exe 1000000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt 
echo.
@echo 10000000
randarr.exe 10000000 -9 9 & maxseqsumtest.exe 3 arr.txt & maxseqsumtest.exe 2 arr.txt
echo.
@echo 100000000
randarr.exe 100000000 -9 9 & maxseqsumtest.exe 3 arr.txt

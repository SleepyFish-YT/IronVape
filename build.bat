@echo off
color 02
title Builder
make clean
make re
RMDIR /S /Q "%CD%\Build"

pause
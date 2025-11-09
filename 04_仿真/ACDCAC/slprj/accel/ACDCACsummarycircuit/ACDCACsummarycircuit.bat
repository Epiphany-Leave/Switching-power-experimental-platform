@echo off
set MATLAB=D:\Program Files\MATLAB\R2023b

call  "\\Epiphany\D$\Program Files\MATLAB\R2023b\bin\win64\checkMATLABRootForDriveMap.exe" "\\Epiphany\D$\Program Files\MATLAB\R2023b"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
"%MATLAB%\bin\win64\gmake" -f ACDCACsummarycircuit.mk MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  OPTS="-DTID01EQ=1"

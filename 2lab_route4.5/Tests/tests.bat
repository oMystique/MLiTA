rem echo off
SET program = "%1"
if %program% == "" goto err

%program% input.txt > input_out.txt
if errorlevel 1 goto testFailed
fc /b input_out.txt input_for_comparison.txt
if errorlevel 1 goto testFailed

%program% input1.txt > input1_out.txt
if errorlevel 1 goto testFailed
fc /b input1_out.txt input_for_comparison.txt
if errorlevel 1 goto testFailed

echo OK
exit /b

:testFailed
echo Testing failed 
pause
exit /b

:err
echo Usage: test.bat <Path to program>
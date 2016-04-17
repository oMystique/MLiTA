@echo off
SET program="%1"
if %program% == "" goto err

%program% input.txt > test_output.txt
if errorlevel 1 goto testFailed
fc /b test_output.txt output.txt
if errorlevel 1 goto testFailed

%program% input1.txt > test_output1.txt
if NOT errorlevel 1 goto testFailed
fc /b test_output1.txt output1.txt
if errorlevel 1 goto testFailed

%program% input2.txt > test_output2.txt
if errorlevel 1 goto testFailed
fc /b test_output2.txt output2.txt
if errorlevel 1 goto testFailed

%program% input3.txt > test_output3.txt
if errorlevel 1 goto testFailed
fc /b test_output3.txt output3.txt
if errorlevel 1 goto testFailed

%program% input4.txt > test_output4.txt
if NOT errorlevel 1 goto testFailed
fc /b test_output4.txt output4.txt
if errorlevel 1 goto testFailed

%program% input5.txt > test_output5.txt
if NOT errorlevel 1 goto testFailed
fc /b test_output5.txt output5.txt
if errorlevel 1 goto testFailed

echo OK
exit /b

:testFailed
echo Testing failed 
pause
exit /b

:err
echo Usage: test.bat <Path to program>
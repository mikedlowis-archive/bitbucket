@echo off
echo %* | parser.exe | dot -Tbmp > test.bmp
test.bmp

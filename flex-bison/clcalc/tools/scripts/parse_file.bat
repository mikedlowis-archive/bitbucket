@echo off
cat %* | parser.exe | dot -Tbmp > test.bmp
test.bmp

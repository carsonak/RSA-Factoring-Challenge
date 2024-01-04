#!/bin/bash

# Time the program and terminate it after 5 seconds, store output in file
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test00 > out00.txt
echo $?
wc -l out00.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test01 > out01.txt
echo $?
wc -l out01.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test02 > out02.txt
echo $?
wc -l out02.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test03 > out03.txt
echo $?
wc -l out03.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test04 > out04.txt
echo $?
wc -l out04.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test05 > out05.txt
echo $?
wc -l out05.txt
time timeout -.txt-preserve-status 4.99 ./factors ./tests/factorising/test06 > out06.txt
echo $?
wc -l out06.txt

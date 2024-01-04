#!/bin/bash

# Time the program and terminate it after 5 seconds, store output in file
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test00 > out00
echo $?
wc -l out00
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test01 > out01
echo $?
wc -l out01
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test02 > out02
echo $?
wc -l out02
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test03 > out03
echo $?
wc -l out03
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test04 > out04
echo $?
wc -l out04
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test05 > out05
echo $?
wc -l out05
time timeout --preserve-status 4.99 ./factors/factors ./tests/factorising/test06 > out06
echo $?
wc -l out06

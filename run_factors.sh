#!/bin/bash

# Time the program and terminate it after 5 seconds
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test00 > out00
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test01 > out01
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test02 > out02
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test03 > out03
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test04 > out04
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test05 > out05
echo $?
time timeout --preserve-status 4.99 ./task_0/factors ./tests/factorising/test06 > out06
echo $?

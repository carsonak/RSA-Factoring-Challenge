#!/bin/bash

common_name="rsa_"  # Replace the string in qoutes with your desired common name
start_at_suffix=10   # Set the starting number for the files
stop_at_suffix=40   # Set the end of the files
step_size=1	# Set the step size

for i in $(eval echo "{$start_at_suffix..$stop_at_suffix..$step_size}")
do
	touch "$common_name$i"
done

#!/usr/bin/env bash

common_name="-main.c"  # Replace the string in qoutes with your desired common name
is_suffix=0  # 0 for prefix, 1 for suffix

start_at=0   # Set the starting number for the files
stop_at=6   # Set the end of the files
step_size=1	# Set the step size

for i in $(eval echo "{$start_at..$stop_at..$step_size}")
do
	if [[ $is_suffix -eq 0 ]]; then
		touch "$i$common_name"
	else
		touch "$common_name$i"
	fi
done

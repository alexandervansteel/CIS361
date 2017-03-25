#!/usr/bin/bash
filename="$1"
while read -a line
do
   echo "Course number read: ${line[0]}"
   mkdir -p ${line[0]}
   touch ${line[0]}/${line[1]}
done < "$filename"

#!/bin/bash

INPUT="resources/engine.png"
OPERATIONS="2 8"
OUTPUT="out.png"

cp $INPUT $OUTPUT

for i in $OPERATIONS
do
  ./a.out $OUTPUT $i
done

feh $OUTPUT &


#!/bin/bash

###############################################################################
# This file compares the runtime of different implementations of set:
# unsorted array, sorted array (quicksort and insertion sort) and Red-Black set.
#
# Usage: ./timeTree
###############################################################################

if [ $# -lt 3 ]
then
  echo "Syntax: timeTree min_nodes max_nodes stp_nodes"
  echo "Default values: min_nodes = 100, max_nodes = 110101, stp_nodes = 10000"
  min=1000
  max=110100
  stp=10000
else
  min=$1
  max=$2
  stp=$3
  echo "min_nodes = $min, max_nodes = $max, stp_nodes = $stp"
fi

run_test() {
  echo "$1, Num-Nodes"
  for ((num_nodes = $min; num_nodes < $max; num_nodes += $stp))
  do
    ./$1 $num_nodes $num_nodes
  done
}

clang -o IntArraySet CompSetMain.c IntArraySet.c -Iinclude
run_test IntArraySet

clang RedBlackSet.c RBT.c CompSetMain.c -o RBTMain -Iinclude
run_test RBTSet

clang -o BitArraySet CompSetMain.c BitArraySet.c -Iinclude
run_test BitArraySet

clang -o HashSet CompSetMain.c HashSet.c -Iinclude
run_test HashSet

clang -o NoEqualHashSet CompSetMain.c NoEqualHashSet.c -Iinclude
run_test NoEqualHashSet

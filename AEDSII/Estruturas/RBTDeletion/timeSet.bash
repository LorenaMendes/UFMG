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
  min_nodes=100
  max_nodes=11010
  stp_nodes=1000
else
  min_nodes=$1
  max_nodes=$2
  stp_nodes=$3
  echo "min_nodes = $min_nodes, max_nodes = $max_nodes, stp_nodes = $stp_nodes"
fi

echo "un_sort, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./UnsortedArraySet $num_nodes $num_nodes ;
done

echo "rb_sort, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./RedBlackSet $num_nodes $num_nodes ;
done

echo "in_sort, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./IsortArraySet $num_nodes $num_nodes ;
done

echo "qk_sort, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./QsortArraySet $num_nodes $num_nodes ;
done

#!/bin/bash

###############################################################################
# This file compares the runtime of different trees: balanced, and unbalanced.
# program.
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

echo "deg-tr, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./TimeTreeMain $num_nodes 0 > /dev/null ;
done

echo "ran-tr, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./TimeTreeMain $num_nodes 1 > /dev/null ;
done

echo "deg-rb, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./TimeTreeMain $num_nodes 2 > /dev/null ;
done

echo "ran-rb, Time (s)"
for ((num_nodes = $min_nodes; num_nodes < $max_nodes; num_nodes += $stp_nodes))
do
  ./TimeTreeMain $num_nodes 3 > /dev/null ;
done

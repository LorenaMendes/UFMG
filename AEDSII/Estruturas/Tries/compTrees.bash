#!/bin/bash

###############################################################################
# This file compares the runtime of different trees: simple binary search
# tree, Trie, Red-Black tree.
# Usage: ./compTrees
###############################################################################

if [ $# -lt 3 ]
then
  echo "Syntax: timeTree min max stp"
  echo "Default values: min = 100, max = 110101, stp = 10000"
  min=10000
  max=100001
  stp=10000
else
  min=$1
  max=$2
  stp=$3
  echo "min_nodes = $min, max_nodes = $max, step = $stp"
fi

run_test() {
  echo "$1, Num-Nodes, Time (s)"
  for ((num_nodes = $min; num_nodes < $max; num_nodes += $stp))
  do
    ./$1 $num_nodes ;
  done
}

# Testing the binary search tree:
clang BinT.c T2.c -o BinTComp -Iinclude ;
run_test BinTComp ;

# Testing the bit-trie:
clang Trie.c T2.c -o TrieComp -Iinclude ;
run_test TrieComp ;

# Testing the Red-Black tree:
clang RBT.c T2.c -o RBTComp -Iinclude ;
run_test RBTComp ;

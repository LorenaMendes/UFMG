#!/bin/bash

###############################################################################
# This file opens up the dot file containing a tree produced by the DotMain.c
# program.
# Usage: showDot DESIRABLE_NUM_NODES MAX_KEY
#   where
#   - DESIRABLE_NUM_NODES is the number of nodes that will be randomly
#     generated and then inserted in the tree. Notice that some nodes can be
#     generated twice, and the tree only takes one of them. Thus, this is not
#     the number of nodes in the final tree.
#   - MAX_KEY is the size of the largest tree that can be produced. The larger
#     the ratio MAX_KEY/DESIRABLE_NUM_NODES, the larger the number of nodes
#     in the final tree.
###############################################################################

if [ $# -lt 2 ]
then
    echo Syntax: showDot desirable_num_nodes max_key
    exit 1
else
  desirable_num_nodes=$1
  max_key=$2
  dot_name=file.dot
  ./DotMain $desirable_num_nodes $max_key > $dot_name ;
fi

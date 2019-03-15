#!/bin/bash

###############################################################################
# This file opens up the dot file containing a tree produced by the treeGen.c
# program.
# Usage: cfgllvm file.c
###############################################################################

if [ $# -lt 1 ]
then
    echo Syntax: showDot num_nodes
    exit 1
else
  num_nodes=$1
  dot_name=file.dot
  ./DotMain $num_nodes > $dot_name ;
  open $dot_name
fi

#!/bin/sh

# A solution with a Shell loop
tr -s [:space:][:punct:] '\n' < mda3.tex > mda3.words
while read keyword
do
    grep -ixc $keyword mda3.words
done < keywords | paste -d ' ' keywords -

# Another solution
tr -s [:space:][:punct:] '\n' < mda3.tex | grep -ixf keywords | sort -f | uniq -ci

# To only know the present keywords (not their numbers of occurrences)
tr -s [:space:][:punct:] '\n' < mda3.tex | grep -ixf keywords | sort -uf

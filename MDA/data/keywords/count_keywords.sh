#!/bin/sh

# List the present keywords
sort keywords > keywords.sorted
tr -s [:space:][:punct:] '\n' < mda3.tex | tr [:upper:] [:lower:] | sort -u | comm -12 keywords.sorted -

# Count the number of occurrences of each keyword
sort keywords > keywords.sorted
tr -s [:space:][:punct:] '\n' < mda3.tex | tr [:upper:] [:lower:] | sort | uniq -c | join -2 2 keywords.sorted -

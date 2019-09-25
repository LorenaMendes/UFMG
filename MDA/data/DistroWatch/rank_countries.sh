#!/bin/sh

cut -d ^ -f 1 */INDEX | sort | uniq -c | sort -nk 1,1 | tail # keeping the counts
cut -d ^ -f 1 */INDEX | sort | uniq -c | sort -nk 1,1 | tail | tr -s ' ' | cut -d ' ' -f 3 # removing the counts

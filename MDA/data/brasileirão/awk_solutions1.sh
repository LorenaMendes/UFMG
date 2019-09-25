#!/bin/sh

awk '{ print $4, $3, $2, 1 / (1 + exp(.2 * (20 - $1))) }' retweets.txt

awk '$4 == "milton_neves" { sum += $1 }
END { print sum }' retweets.txt

awk '$3 > 40 { ++$3 }
{ print }' retweets.txt

awk '$1 >= 20 { print $4 }' retweets.txt | sort -u

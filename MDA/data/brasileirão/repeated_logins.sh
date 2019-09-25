#!/bin/sh

tr -s ' ' < retweets.txt | cut -d ' ' -f 5 | sort -u | sort -f | uniq -id

# uniq --all-repeated (-D) to get the different versions of the logins:
tr -s ' ' < retweets.txt | cut -d ' ' -f 5 | sort -u | sort -f | uniq -i --all-repeated=separate

# Avoiding the cut by using uniq -f N to discard the N first fields:
sort -uk 4 retweets.txt | sort -fk 4 | uniq -idf 3

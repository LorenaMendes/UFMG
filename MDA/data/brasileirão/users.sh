#!/bin/sh

grep -i galo retweets.txt | grep -vi sangalo | sort -uk 4 | wc -l

tr -s ' ' < retweets.txt | cut -d ' ' -f 5 | grep -v '[0-9]' | sort -u | wc -l
grep -o ' [^0-9]*$' retweets.txt | sort -u | wc -l
grep -o ' [a-zA-Z_]*$' retweets.txt | sort -u | wc -l # noticing that, besides digits, only alphabetic characters and underscores are allowed in a user name

#!/bin/sh

grep -vx ' *\( [0-9][0-9]*\)\{3\} [a-zA-Z0-9_][a-zA-Z0-9_]*' retweets.txt # no output: every whole line satisfies the format
# or, using egrep (Extended Regular Expressions):
egrep -vx ' *( [0-9]+){3} [a-zA-Z0-9_]+' retweets.txt # idem

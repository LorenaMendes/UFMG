#!/bin/sh

ls */* | cut -d / -f 2 | grep -v INDEX | sort -uo distros
# or
ls */ | grep -ve INDEX -e / -e '^$' | sort -uo distros

# wget -B http://distrowatch.com/ -i distros -P ../distrowatch_pages

# With sed (1'00 on my laptop)
sed -n 's/.*origin=\(.*\)#.*/\1/p' ../distrowatch_pages/* | paste distros -
# With sed (faster: .24s on my laptop)
sed -n '/origin=/ s/.*origin=\(.*\)#.*/\1/p' ../distrowatch_pages/* | paste distros -
# Without sed (fastest: .06s on my laptop; add grep's option "-m 1" to get down to .04s)
grep -o 'origin=[^#]*' ../distrowatch_pages/* | cut -d = -f 2 | paste distros -

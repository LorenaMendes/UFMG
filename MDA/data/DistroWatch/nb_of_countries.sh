#!/bin/sh

sort -ut ^ -k 1,1 */* | wc -l

cut -d ^ -f 1 20100429/* | sort -u > countries
cut -d ^ -f 1 20100429/ubuntu | sort -u > UbuntuCountries
comm -23 countries UbuntuCountries
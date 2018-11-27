#!/bin/bash
cat=$(curl -s 'https://api.thecatapi.com/v1/images/search?size=full' | jq -r '.[].url')
wget $cat
cat=$(basename "$cat")
img2txt $cat
curl -s "http://api.icndb.com/jokes/random" | jq '.value.joke'
rm $cat

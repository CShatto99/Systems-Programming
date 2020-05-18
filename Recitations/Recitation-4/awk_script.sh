#!/bin/bash
# Name: Cameron Shatto
# EUID: chs0090
clear

cat $1 | awk -F '[,;: ]' '{print $1}' 

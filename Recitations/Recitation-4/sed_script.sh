#!/bin/bash
# Name: Cameron Shatto
# EUID: chs0090
clear

cat $1 | sed '1,3d

/^#/d

s/#.*$//g

/^[/*].*[*/]$/d

s/BEGIN/#include<stdio.h>\n\nint main() \n\n{\n/g

s/HELLO/\tprintf("hello,world\\n");\n/g

s/END/}/g;'

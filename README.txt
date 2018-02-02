#!/bin/bash
# EE569 Homework Assignment #1
# Date: 2018.1.29
# Name: Jun Liu
# ID  : 4871562115
# email:liu494@usc.edu
# Operating System: Mac OS X 10.12.6
# Compiler: g++ 4.2.1

#****************************************************************************************
# How to run the programs:
# Question 1
# Q1_part1: ./Q1_part1 Tiffany.raw
# Q1_part2: ./Q1_part2 Bear.raw
# Q1_part2: ./Q1_part2 Dance.raw
# Q1_part3: ./Q1_part3 Airplane.raw

# Question 2
# Q2_part1: ./Q2_part1 Desk.raw
# Q2_part2: ./Q2_part2 Barn.raw 4 3
# You need to change the source code’s variable “Size1” and “Size2” manually 
# to apply this function to different size’s image
# the second input variable “4” indicates the amount of colors want remained
# the third input variable “3” indicates the size of the filter
# Q2_part3(check histogram of example):./Q2_part3_check Original.raw Film.raw
# Q2_part3(process the given image): ./Q2_part3 Girl.raw

# Question 3
# Q3_part1: ./Q3_1 Lena.raw Lena_mixed.raw 3
# the third input variable “3” indicates the size of the filter

#****************************************************************************************
all: Q1_part1.o Q1_part1.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part1.o

Q1_part1: Q1_part1.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part1.o
    
Q1_part1.o: Q1_part1.cpp
	g++ -ggdb -Wall -Wno-sign-compare -c Q1_part1.cpp

Q1_part2: Q1_part2.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q1_part2.o
    
Q1_part2.o: Q1_part2.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q1_part2.cpp

Q1_part3: Q1_part3.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q1_part3.o
    
Q1_part3.o: Q1_part3.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q1_part3.cpp

Q2_part1: Q2_part1.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q2_part1.o
    
Q2_part1.o: Q2_part1.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q2_part1.cpp

Q2_part2: Q2_part2.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q2_part2.o
    
Q2_part2.o: Q2_part2.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q2_part2.cpp

Q2_part3: Q2_part3.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q2_part3.o
    
Q2_part3.o: Q2_part3.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q2_part3.cpp

Q2_part3_check: Q2_part3_check.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q2_part3_check.o
    
Q2_part3_check.o: Q2_part3_check.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q2_part3_check.cpp

Q3_part1: Q3_part1.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q3_part1.o
    
Q3_part1.o: Q3_part1.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q3_part1.cpp
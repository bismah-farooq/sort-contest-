# Sorting Contest (C++)

This project compares the performance of a custom Bubble Sort implementation against the Linux system sort command. It generates a large dataset of random integers, sorts them using both methods, and records timing results.

## Description
The program generates up to 1,000,000 random integers within a specified range and writes them to a file called numbers.dat. The Linux sort command is used to sort the file, and its execution time is recorded. A custom sorting program using Bubble Sort is then run on the same data, and its execution time is also recorded.

The goal of this project is to understand sorting performance, command-line arguments, file I/O, and shell scripting.

## Programs Included

generate.cpp
- Generates a file called numbers.dat
- Accepts three command-line arguments:
  generate COUNT MIN MAX
- Writes COUNT random numbers between MIN and MAX to numbers.dat
- Displays an error message if arguments are missing

mysort.cpp
- Reads integers from an input file
- Sorts the numbers using Bubble Sort
- Writes sorted output to a specified file
- Uses an array (not a vector)
- Includes a function:
  bubble(int A[], int size)

## Shell Script

sortrace.sh
- Automates the sorting contest
- Runs both system sort and custom Bubble Sort
- Logs timing results to sortrace.log
- Executes sorting tasks in the background

## How to Compile

Compile generate:
```text
g++ generate.cpp -o generate
```
Compile mysort:
```text
g++ mysort.cpp -o mysort
```
## How to Run

Generate random numbers:
```text
./generate 1000000 -100000 100000
```
Run sorting contest:
```text
chmod +x sortrace.sh
./sortrace.sh >> sortrace.log &
```
## Verification
- Output file is checked using:
  sort -c -n mysort.out
- wc is used to confirm correct number of sorted values

## Learning Objectives
- Work with command-line arguments
- Perform file input and output
- Implement Bubble Sort
- Compare algorithm performance
- Use shell scripts and background processes
- Understand system-level programming concepts

## Author
Bismah Farooq


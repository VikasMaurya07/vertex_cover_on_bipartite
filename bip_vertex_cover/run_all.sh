#!/bin/bash

# Exit immediately if a command fails
set -e

echo "Compiling..."
g++ -o main main.cpp

echo "Running C++ program on tests.txt..."
./main < tests.txt > output_for_python.txt

echo "Generating visualizations with Python..."
python3 visualise.py < output_for_python.txt

echo "Cleaning up..."
rm -f main output_for_python.txt

echo "Done ✔"

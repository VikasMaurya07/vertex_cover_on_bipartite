#!/usr/bin/env bash
set -euo pipefail

EXE=main
INPUT=tests.txt
OUT=output_for_python.txt

echo "Compiling..."
g++ -std=c++17 -O2 -o ${EXE} main.cpp

echo "Running program on ${INPUT}..."
./${EXE} < "${INPUT}" > "${OUT}"

echo "Plotting..."
python3 plot_groups.py "${OUT}"

echo "Cleaning up..."
rm -f ${EXE} "${OUT}"

echo "Done."

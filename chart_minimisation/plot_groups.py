#!/usr/bin/env python3
# plot_groups.py
# Usage: python3 plot_groups.py output_for_python.txt
# Produces visuals/plot_case_1.png, plot_case_2.png, ... and displays them.

import sys
from pathlib import Path
import matplotlib.pyplot as plt
import itertools
import math

def parse_output(filename):
    """Parse the machine-readable output produced by main.cpp"""
    with open(filename, 'r') as f:
        lines = [ln.rstrip("\n") for ln in f]

    i = 0
    cases = []
    while i < len(lines):
        line = lines[i].strip()
        if not line:
            i += 1
            continue
        if line.startswith("PRINT_CASE"):
            parts = line.split()
            n = int(parts[1]); p = int(parts[2])
            i += 1
            # read next n lines as stocks
            stocks = []
            for _ in range(n):
                vals = list(map(float, lines[i].strip().split()))
                if len(vals) != p:
                    raise RuntimeError(f"Expected {p} values but got {len(vals)} on line: {lines[i]}")
                stocks.append(vals)
                i += 1
            # read PRINT_GROUPS
            if i >= len(lines):
                raise RuntimeError("Missing PRINT_GROUPS after stock data")
            grp_line = lines[i].strip()
            if not grp_line.startswith("PRINT_GROUPS"):
                raise RuntimeError("Expected PRINT_GROUPS, got: " + grp_line)
            # parse groups line: PRINT_GROUPS G | k v v ... | k v ...
            rest = grp_line[len("PRINT_GROUPS"):].strip()
            groups = []
            if rest:
                blocks = [b.strip() for b in rest.split("|")]
                # first token is number of groups (already consumed)
                # but our format was PRINT_GROUPS <g> | <k> v v | <k> v v ...
                # so blocks[0] might be "<g>" or "<g> <maybe more>" — handle carefully
                # We'll parse tokens sequentially:
                tokens = rest.split()
                G = int(tokens[0])
                # Now parse the | separated group specs
                # easier: split on '|' then parse each after the first
                items = rest.split("|")
                # items[0] contains G (maybe with spaces); items[1:] each group
                for item in items[1:]:
                    toks = item.strip().split()
                    if not toks:
                        continue
                    k = int(toks[0])
                    members = [int(x) for x in toks[1:1+k]]
                    groups.append(members)
            i += 1
            cases.append({
                "n": n, "p": p,
                "stocks": stocks,
                "groups": groups
            })
        else:
            i += 1
    return cases

def plot_case(case, idx, outdir="visuals"):
    n = case["n"]; p = case["p"]
    stocks = case["stocks"]
    groups = case["groups"]

    # prepare x axis labels (point names)
    x = list(range(p))
    xticks = [f"t{j}" for j in range(p)]

    # choose colors per group (cycle)
    colors = plt.get_cmap("tab10")
    color_cycle = [colors(i % 10) for i in range(max(1, len(groups)))]
    # if groups empty (shouldn't) treat each stock separate
    if not groups:
        groups = [[i] for i in range(n)]
        color_cycle = [colors(i % 10) for i in range(n)]

    # build mapping stock -> group index
    stock_to_group = {}
    for gi, g in enumerate(groups):
        for v in g:
            stock_to_group[v] = gi

    Path(outdir).mkdir(parents=True, exist_ok=True)

    plt.figure(figsize=(10,6))
    for s in range(n):
        grp = stock_to_group.get(s, -1)
        col = color_cycle[grp] if grp >= 0 else "#888888"
        label = f"Stock {s} (G{grp})" if grp >= 0 else f"Stock {s} (ungrouped)"
        plt.plot(x, stocks[s], marker='o', linestyle='-', linewidth=1.6, label=label, color=col)

        # annotate each point with its value (optional)
        for xi, yi in zip(x, stocks[s]):
            plt.text(xi, yi + 0.03* (max(stocks[s]) - min(stocks[s]) if max(stocks[s])!=min(stocks[s]) else 1.0),
                     f"{yi:g}", fontsize=8, ha='center', color=col)

    plt.xticks(x, xticks)
    plt.xlabel("Points")
    plt.ylabel("Value")
    plt.title(f"Stocks grouped into {len(groups)} chains")
    plt.grid(alpha=0.25)
    plt.legend(loc="upper left", bbox_to_anchor=(1.01, 1.0))
    fname = Path(outdir) / f"case_{idx}.png"
    plt.tight_layout()
    plt.savefig(fname, dpi=180)
    print(f"Saved: {fname}")
    plt.show()
    plt.close()

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 plot_groups.py output_for_python.txt")
        sys.exit(1)
    cases = parse_output(sys.argv[1])
    if not cases:
        print("No cases parsed.")
        return
    for idx, case in enumerate(cases, start=1):
        plot_case(case, idx)

if __name__ == "__main__":
    main()

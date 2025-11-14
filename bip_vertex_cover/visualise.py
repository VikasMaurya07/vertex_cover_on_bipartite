#!/usr/bin/env python3
"""
visualise.py

Reads the C++ program output that contains blocks like:

PRINT_GRAPH n m
u v
...
[optional diagnostic lines, e.g. "Graph is not Bipartite"]
PRINT_COVER k v1 v2 ...

This script is tolerant: it will visualize every PRINT_GRAPH block,
highlight any cover nodes, and annotate the figure if a "not bipartite"
diagnostic is present in the block.

It saves images graph_1.png, graph_2.png, ... and also shows them.
"""

import sys
import networkx as nx
import matplotlib.pyplot as plt
import re
from pathlib import Path

def parse_blocks(lines):
    i = 0
    L = len(lines)
    blocks = []
    bipartite_phrase = re.compile(r'not\s*bipartite', re.IGNORECASE)

    while i < L:
        line = lines[i].strip()
        if not line:
            i += 1
            continue

        if line.startswith("PRINT_GRAPH"):
            parts = line.split()
            if len(parts) < 3:
                # malformed header
                i += 1
                continue
            n = int(parts[1]); m = int(parts[2])
            i += 1

            edges = []
            read_edges = 0
            # read next m lines as edges (skip blanks)
            while read_edges < m and i < L:
                s = lines[i].strip()
                # if a new header appears unexpectedly, stop early
                if not s:
                    i += 1
                    continue
                if s.startswith("PRINT_GRAPH") or s.startswith("PRINT_COVER"):
                    break
                toks = s.split()
                if len(toks) >= 2:
                    try:
                        u, v = int(toks[0]), int(toks[1])
                        edges.append((u, v))
                        read_edges += 1
                    except ValueError:
                        # not an edge line; treat as diagnostic
                        pass
                i += 1

            # now collect any intervening diagnostic lines up to PRINT_COVER or next PRINT_GRAPH
            diagnostics = []
            found_cover = False
            cover = []
            while i < L:
                s = lines[i].strip()
                if not s:
                    i += 1
                    continue
                if s.startswith("PRINT_COVER"):
                    parts = s.split()
                    nums = []
                    if len(parts) > 1:
                        try:
                            nums = list(map(int, parts[1:]))
                        except ValueError:
                            nums = []
                    if nums:
                        k = nums[0]
                        cover = nums[1:1+k] if k > 0 else []
                    else:
                        cover = []
                    i += 1
                    found_cover = True
                    break
                if s.startswith("PRINT_GRAPH"):
                    # no PRINT_COVER found for this block
                    break
                # otherwise accumulate diagnostics
                diagnostics.append(s)
                i += 1

            # detect bipartite diagnostic
            is_non_bipartite = any(bool(bipartite_phrase.search(d)) for d in diagnostics)

            blocks.append({
                "n": n,
                "edges": edges,
                "cover": cover,
                "diagnostics": diagnostics,
                "non_bipartite_flag": is_non_bipartite
            })
        else:
            # skip any stray lines (diagnostics printed outside a block)
            i += 1
    return blocks

def visualize_block(block, idx, out_dir="visuals"):
    n = block["n"]
    edges = block["edges"]
    cover = set(block["cover"])
    non_bip = block["non_bipartite_flag"]
    diagnostics = block["diagnostics"]

    G = nx.Graph()
    G.add_nodes_from(range(n))
    G.add_edges_from(edges)

    # layout -- if graph disconnected, spring_layout still OK
    pos = nx.spring_layout(G, seed=42)

    # Node colors: cover -> red, otherwise -> lightblue
    node_colors = []
    for v in G.nodes():
        if v in cover:
            node_colors.append("red")
        else:
            node_colors.append("lightblue")

    plt.figure(figsize=(7,7))
    title = f"Graph {idx}  (Vetex Count={n}, Edge Count={len(edges)})"
    if non_bip:
        title += " — NOT BIPARTITE"
    plt.title(title, fontsize=14)

    nx.draw_networkx_edges(G, pos, edge_color="gray", alpha=0.8)
    nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=600)
    nx.draw_networkx_labels(G, pos, font_size=10, font_color="black")

    # If there is a cover, add a legend in-plot
    legend_parts = []
    if cover:
        # add a small legend box
        plt.scatter([], [], c="red", label="Vertex cover")
        plt.scatter([], [], c="lightblue", label="Other nodes")
        plt.legend(loc="upper right")

    # If non-bipartite, annotate diagnostics text on the plot (small font)
    if non_bip or diagnostics:
        # show first diagnostic lines (up to 3) under the plot title
        diag_text = ""
        if diagnostics:
            # prefer explicit "Graph is not Bipartite" if present
            diag_text = "\n".join(diagnostics[:4])
        else:
            diag_text = "Non-bipartite"
        # put the diagnostics as an annotation box
        plt.gcf().text(0.02, 0.02, diag_text, fontsize=9, color="darkred",
                       bbox=dict(facecolor="white", edgecolor="red", alpha=0.6))

    # ensure output directory exists
    out_path = Path(out_dir)
    out_path.mkdir(parents=True, exist_ok=True)
    fname = out_path / f"graph_{idx}.png"
    plt.tight_layout()
    plt.savefig(fname, dpi=150)
    print(f"Saved visualization to {fname}")
    plt.show()
    plt.close()

def main():
    lines = [line.rstrip("\n") for line in sys.stdin]
    blocks = parse_blocks(lines)
    if not blocks:
        print("No graph blocks found.", file=sys.stderr)
        return

    for idx, block in enumerate(blocks, start=1):
        visualize_block(block, idx)

if __name__ == "__main__":
    main()

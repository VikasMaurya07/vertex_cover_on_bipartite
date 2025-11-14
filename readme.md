## ⚙️ 1. **What is a Matching?**

Given a graph ( G = (V, E) ):

A **matching** ( M \subseteq E ) is a set of edges such that **no two edges share a common vertex**.

Formally:
[
\forall (u_1,v_1),(u_2,v_2)\in M,\quad {u_1,v_1}\cap{u_2,v_2} = \emptyset
]

So each vertex is incident to **at most one edge** of the matching.

---

## 💎 2. **Maximum Matching Problem**

The **maximum matching problem** asks:

> Find a matching ( M ) of **maximum cardinality** (i.e., with the largest number of edges).

That is:
[
\text{Maximize } |M| \quad \text{subject to } M \text{ is a matching in } G
]

---

## 🧩 3. **Example**

Graph:

```
A --- B --- C --- D
```

Edges: ( {(A,B), (B,C), (C,D)} )

Possible matchings:

* ( M_1 = {(A,B)} )
* ( M_2 = {(B,C)} )
* ( M_3 = {(C,D)} )
* ( M_4 = {(A,B), (C,D)} ) ✅ (no shared vertices)

Maximum matching size = **2** (edges: (A,B) and (C,D)).

---

## 🧭 4. **Types of Matchings**

| Type                 | Meaning                                                                             |
| -------------------- | ----------------------------------------------------------------------------------- |
| **Matching**         | No two edges share a vertex                                                         |
| **Maximum Matching** | Matching with the largest number of edges                                           |
| **Perfect Matching** | Every vertex is matched (no free vertex)                                            |
| **Maximal Matching** | Cannot add more edges without violating matching property (not necessarily maximum) |

Example:
Every **perfect matching** is **maximum**, but not every **maximum** matching is perfect.

---

## 🔍 5. **Why It Matters**

* It’s the “dual” of the **vertex cover problem** (via **König’s theorem** in bipartite graphs).
* It’s a fundamental **combinatorial optimization** problem.
* Appears in:

  * Job assignment
  * Stable marriage problem
  * Network flow formulations
  * Scheduling and resource allocation

---

## 🧮 6. **Algorithmic View**

### For **bipartite graphs**:

* The problem can be solved in **polynomial time**.
* **Hopcroft–Karp algorithm** → ( O(E\sqrt{V}) )
* Can also be reduced to a **maximum flow** problem.

### For **general (non-bipartite)** graphs:

* Solved using **Edmonds’ Blossom algorithm** (polynomial time but more complex).

---

## ⚖️ 7. **Connection to Vertex Cover (König’s Theorem)**

In bipartite graphs:
[
\boxed{\text{Size of Maximum Matching } = \text{Size of Minimum Vertex Cover}}
]
So — the set of matched edges (maximum matching) “dually corresponds” to the smallest number of vertices needed to cover all edges.

---

## 💡 Example Combining Both

Let’s take the bipartite graph:

```
X1 --- Y1
 |      |
 |      |
X2 --- Y2
```

Edges:
( E = {(X1,Y1), (X1,Y2), (X2,Y1), (X2,Y2)} )

* Maximum Matching: size = 2 (e.g. ( (X1,Y1), (X2,Y2) ))
* Minimum Vertex Cover: size = 2 (e.g. ( {X1, X2} ))

✅ Matches König’s theorem perfectly.

---

Would you like me to show **how the maximum matching problem can be solved via max-flow formulation** (step-by-step construction)?
## ⚙️ 1. **What is a Matching?**

Given a graph ( G = (V, E) ):

A **matching** ( M \subseteq E ) is a set of edges such that **no two edges share a common vertex**.

Formally:
[
\forall (u_1,v_1),(u_2,v_2)\in M,\quad {u_1,v_1}\cap{u_2,v_2} = \emptyset
]

So each vertex is incident to **at most one edge** of the matching.

---

## 💎 2. **Maximum Matching Problem**

The **maximum matching problem** asks:

> Find a matching ( M ) of **maximum cardinality** (i.e., with the largest number of edges).

That is:
[
\text{Maximize } |M| \quad \text{subject to } M \text{ is a matching in } G
]

---

## 🧩 3. **Example**

Graph:

```
A --- B --- C --- D
```

Edges: ( {(A,B), (B,C), (C,D)} )

Possible matchings:

* ( M_1 = {(A,B)} )
* ( M_2 = {(B,C)} )
* ( M_3 = {(C,D)} )
* ( M_4 = {(A,B), (C,D)} ) ✅ (no shared vertices)

Maximum matching size = **2** (edges: (A,B) and (C,D)).

---

## 🧭 4. **Types of Matchings**

| Type                 | Meaning                                                                             |
| -------------------- | ----------------------------------------------------------------------------------- |
| **Matching**         | No two edges share a vertex                                                         |
| **Maximum Matching** | Matching with the largest number of edges                                           |
| **Perfect Matching** | Every vertex is matched (no free vertex)                                            |
| **Maximal Matching** | Cannot add more edges without violating matching property (not necessarily maximum) |

Example:
Every **perfect matching** is **maximum**, but not every **maximum** matching is perfect.

---

## 🔍 5. **Why It Matters**

* It’s the “dual” of the **vertex cover problem** (via **König’s theorem** in bipartite graphs).
* It’s a fundamental **combinatorial optimization** problem.
* Appears in:

  * Job assignment
  * Stable marriage problem
  * Network flow formulations
  * Scheduling and resource allocation

---

## 🧮 6. **Algorithmic View**

### For **bipartite graphs**:

* The problem can be solved in **polynomial time**.
* **Hopcroft–Karp algorithm** → ( O(E\sqrt{V}) )
* Can also be reduced to a **maximum flow** problem.

### For **general (non-bipartite)** graphs:

* Solved using **Edmonds’ Blossom algorithm** (polynomial time but more complex).

---

## ⚖️ 7. **Connection to Vertex Cover (König’s Theorem)**

In bipartite graphs:
[
\boxed{\text{Size of Maximum Matching } = \text{Size of Minimum Vertex Cover}}
]
So — the set of matched edges (maximum matching) “dually corresponds” to the smallest number of vertices needed to cover all edges.

---

## 💡 Example Combining Both

Let’s take the bipartite graph:

```
X1 --- Y1
 |      |
 |      |
X2 --- Y2
```

Edges:
( E = {(X1,Y1), (X1,Y2), (X2,Y1), (X2,Y2)} )

* Maximum Matching: size = 2 (e.g. ( (X1,Y1), (X2,Y2) ))
* Minimum Vertex Cover: size = 2 (e.g. ( {X1, X2} ))

✅ Matches König’s theorem perfectly.

---

Would you like me to show **how the maximum matching problem can be solved via max-flow formulation** (step-by-step construction)?



## 🧩 **1. Definition — Vertex Cover Problem**

Given a graph ( G = (V, E) ):

A **vertex cover** is a set of vertices ( C \subseteq V ) such that **every edge** in ( E ) has at least one endpoint in ( C ).
Formally:
[
\forall (u, v) \in E,\quad u \in C \text{ or } v \in C
]

In words:

> A vertex cover “touches” every edge — no edge is left completely uncovered.

---

## 🎯 **2. The Vertex Cover Problem**

The **Vertex Cover Problem** asks:

> Find a vertex cover of **minimum possible size**.

Mathematically:
[
\text{Minimize } |C| \text{ such that } C \text{ is a vertex cover of } G.
]

---

## 💡 Example

Consider this simple graph:

```
   A --- B --- C
```

Edges: ( {(A,B), (B,C)} )

* Possible vertex covers:

  * ( C = {B} ) ✅ (covers both edges)
  * ( C = {A,C} ) ✅ (also covers both edges)
  * ( C = {A,B,C} ) ✅ (but not minimal)

So, **minimum vertex cover size = 1** (the vertex {B}).

---

## 🧮 **3. Relation to Matching**

There’s a deep duality between **vertex cover** and **matching** (a set of edges with no shared vertices):

* **Matching problem:** Find the **largest** set of non-overlapping edges.
* **Vertex cover problem:** Find the **smallest** set of vertices that touch all edges.

In **bipartite graphs**, these two have the *same* optimal value — that’s **König’s theorem**:

[
\boxed{\text{Maximum Matching Size} = \text{Minimum Vertex Cover Size}}
]

---

## ⚙️ **4. Complexity**

* For **general graphs** (not necessarily bipartite),
  the Vertex Cover Problem is **NP-hard** — we don’t know any polynomial-time algorithm to find the minimum one.

* For **bipartite graphs**, however, König’s theorem + polynomial matching algorithms (like Hopcroft–Karp) give a **polynomial-time solution**.

---

## 🧠 **5. Connection to Independent Set**

Complementary view:

An **independent set** is a set of vertices with **no edges** between them.
If ( I ) is an independent set, then ( V \setminus I ) is a vertex cover.

So:
[
\text{Max Independent Set} + \text{Min Vertex Cover} = |V|
]
and since maximum independent set is also NP-hard, so is minimum vertex cover.

---

## 🧭 Summary

| Concept              | Description                           |
| -------------------- | ------------------------------------- |
| **Vertex cover**     | Set of vertices touching all edges    |
| **Goal**             | Find smallest such set                |
| **Bipartite graphs** | Solvable efficiently (via matching)   |
| **General graphs**   | NP-hard                               |
| **Relation**         | Complement of maximum independent set |

---

Would you like me to show how to **formulate it as an integer linear program (ILP)** or **how to find it using matching (in bipartite case)** next?




# König’s theorem (vertex-cover form) — statement and proof

**Theorem (König).**
In any finite bipartite graph (G=(X\cup Y, E)) the size of a maximum matching equals the size of a minimum vertex cover:
[
\nu(G)=\tau(G),
]
where (\nu(G)) is the maximum number of pairwise disjoint edges (maximum matching size) and (\tau(G)) is the minimum number of vertices meeting every edge (minimum vertex cover size).

We prove (\nu(G)\le\tau(G)) (easy) and then show (\tau(G)\le\nu(G)) by constructing a vertex cover of size equal to a maximum matching.

---

## 1. Easy direction: (\nu(G)\le\tau(G))

Every edge in a matching must be covered by distinct vertices of any vertex cover (no two matched edges share an endpoint in a matching). Thus a vertex cover must contain at least one endpoint from each matched edge; so the cover size is at least the matching size. Hence (\nu(G)\le\tau(G)).

---

## 2. Constructing a cover of size (\nu(G))

Let (M) be a maximum matching in the bipartite graph (G=(X\cup Y,E)). We will build a vertex cover (C) with (|C|=|M|), proving (\tau(G)\le|M|=\nu(G)).

### 2.1 Build the alternating-reachability set

* Call a vertex **free** if it is *not* incident to any edge of (M).
* Consider the directed exploration that starts from all free vertices in (X) and follows **alternating paths**:

  * From a vertex in (X) follow edges **not** in (M) to (Y).
  * From a vertex in (Y) follow edges **in** (M) to (X).
* Let (Z) be the set of vertices reachable from free vertices of (X) by such alternating paths. Partition (Z) as (Z_X=Z\cap X) and (Z_Y=Z\cap Y).

Intuition: (Z) is exactly the set of vertices reachable by alternating paths starting at unmatched left-side vertices.

### 2.2 Define the candidate cover

Define
[
C = (X\setminus Z_X)\ \cup\ (Z_Y).
]
In words: take all vertices of (X) that were **not** reached, together with all vertices of (Y) that **were** reached.

We will show (i) (C) is a vertex cover and (ii) (|C|=|M|).

---

### 2.3 (C) is a vertex cover

Take any edge (e=uv) with (u\in X), (v\in Y). We show (u\in C) or (v\in C).

* If (u\in Z_X) then by the definition of (Z) every edge (u w) not in (M) that is outgoing from (u) to (Y) leads to a reachable (w\in Z_Y). In particular, if (uv\in E) and (uv\notin M), then (v\in Z_Y\subseteq C).
* If (uv\in M), and (u\in Z_X), then the matched edge from (u) goes to some (v) — but our alternating reachability rules ensure that when a vertex in (X) is reachable, the matched edge (if any) goes to the corresponding (Y) vertex only if that (Y) vertex is also reachable; so again (v\in Z_Y\subseteq C).
* If (u\notin Z_X), then (u\in X\setminus Z_X\subseteq C).

Thus every edge has at least one endpoint in (C). So (C) is a vertex cover.

*(A compact way to see this: if an edge has its (X)-endpoint reachable then its (Y)-endpoint is reachable too (by alternating-step rules) and so in (C); otherwise the (X)-endpoint itself is in (C).)*

---

### 2.4 (|C|=|M|)

We count how many vertices of (C) come from (X) and from (Y).

**Claim A.** Every vertex of (Z_Y) is matched (incident to an (M)-edge).
Proof: If (y\in Z_Y) is reachable by an alternating path, the path alternates and the last step to (y) came along a non-matching edge from some (x\in Z_X); but by the alternating rules from (y) we follow the matching-edge (if any) to continue. If (y) were unmatched, the alternating path from a free (x) to (y) would be an augmenting path (starts and ends at free vertices and alternates), contradicting maximality of (M). So all vertices in (Z_Y) are matched.

**Claim B.** Every vertex of (X\setminus Z_X) is matched.
Proof: If (x\in X\setminus Z_X) were unmatched (free), then it would have been in the starting set of the exploration and thus in (Z_X). So it must be matched.

Thus every vertex in (C=(X\setminus Z_X)\cup Z_Y) is matched by (M). Moreover, each matched edge of (M) has exactly one endpoint in (C):

* If an edge (xy\in M) has (x\in X\setminus Z_X), then (x\in C) while (y\notin Z_Y) (otherwise (x) would be reachable via that matched edge), so (y\notin C).
* If (x\in Z_X), then matching forces (y\in Z_Y); then (y\in C) while (x\notin C).

Therefore the matched edges give a bijection between elements of (M) and vertices of (C): each matched edge contributes exactly one vertex to (C), and every vertex of (C) is matched and corresponds to a distinct matched edge. So (|C|=|M|).

---

## 3. Conclusion

From part 1 we had (\nu(G)\le\tau(G)). From part 2 we constructed a vertex cover (C) with (|C|=|M|) for a maximum matching (M), hence (\tau(G)\le|M|=\nu(G)). Combining,
[
\nu(G)=\tau(G).
]
That proves König’s theorem.

---

## Remarks

* The proof is constructive: given a maximum matching one can efficiently produce a minimum vertex cover via the alternating-reachability sets (this is the classical proof used in algorithms such as the Hopcroft–Karp algorithm).
* A dual statement (Kőnig–Egerváry theorem) relates maximum matching and minimum vertex cover in bipartite graphs; for general graphs the equality need not hold.


## Applications

1) Stock Overlaid Chart Minimization (Your Problem) 📊

    ### Dilworth's Theorem

    Application: Determining the minimum number of overlaid charts required to display the performance of n stocks such that no two lines in a single chart cross.

    Description: This problem can be transformed into finding a minimum path cover in a directed acyclic graph (DAG) where the vertices are the stocks. If we create a bipartite graph where an edge exists between two stocks if their lines must cross, the problem becomes finding the minimum number of groups (charts) such that no two stocks in the same group have an edge between them. The final connection is that the minimum number of paths needed to cover all vertices in a DAG is equal to n−∣M∣, where n is the number of vertices and ∣M∣ is the size of the maximum matching in an associated bipartite graph (derived from the DAG's structure). This is a direct application of Dilworth's theorem/Minimum Path Cover theorem, which is strongly linked to maximum matching in bipartite graphs.

2) Logic Minimization/Circuit Design 💡

    Application: Optimizing the design of digital logic circuits (e.g., using Karnaugh maps or Quine-McCluskey).

    Description: The process involves finding a minimum set of prime implicants to cover all the minterms (product terms corresponding to 1s in the output) of a Boolean function. This is a classic Set Cover problem. While Set Cover is generally NP-hard, if the underlying structure of the cover problem can be mapped to a bipartite graph's minimum vertex cover (which is polynomial-time solvable via maximum matching), König's theorem provides the theoretical foundation for the efficient solution.

3) Network Security/Covering Attacks 🛡️

    Application: Identifying the minimum set of nodes (routers, servers) to monitor to detect all potential malicious communication paths.

    Description: If a communication network can be modeled as a bipartite graph (perhaps between different subnets), finding the minimum vertex cover (the smallest set of nodes to monitor to intercept every communication link/edge) is crucial. König's theorem ensures this minimum set can be found efficiently by calculating the maximum matching in the network's bipartite representation.

4) Resource Allocation/Test Case Reduction 🧪

    Application: Minimizing the number of test cases required to cover all necessary conditions or code paths in software testing.

    Description: Similar to the logic minimization, this involves creating a bipartite graph between "Test Cases" and "Conditions/Code Paths." An edge exists if a test case covers a condition. Finding the minimum number of test cases (a minimum vertex cover in the test case side) needed to cover all conditions can sometimes be solved or approximated using maximum matching techniques rooted in König's theorem.

5) Graph Decompositions/Edge Coloring 🎨

    Application: Finding the minimum number of colors needed to color the edges of a bipartite graph such that no two edges incident to the same vertex have the same color.

    Description: By König's edge coloring theorem, the chromatic index χ′(G) (the minimum number of colors) for a bipartite graph G is equal to its maximum degree Δ(G). While this is a different "König's theorem," it is deeply related to matching theory. Furthermore, finding a decomposition of a graph into a minimum number of matchings is a related problem where maximum matching provides the core building block for an efficient solution.

6) Job Assignment/Maximum Bipartite Matching 🧑‍💻

    Application: Optimally assigning jobs to workers or tasks to machines.

    Description: This is the most direct and common application. Given a set of workers and a set of jobs, and a list of which worker can perform which job, the problem is to find the maximum number of jobs that can be assigned to different workers (one-to-one). König's theorem guarantees that the maximum number of such assignments (maximum matching) is equal to the minimum number of workers or jobs you need to select (minimum vertex cover) to "cover" all possible assignment links.

## References

https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html

https://en.wikipedia.org/wiki/Vertex_cover
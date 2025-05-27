# Hexagonal TSP Solver — Continuation Prompt

## Ontological Mathematics — Compressed Summary

This project is grounded in a system of **ontological mathematics**, where operations, structure, and symbolic logic are subordinate to **being and relation**. At the core is the principle:

> **Being precedes computation.**

Numbers are not abstract entities but **structural truths**:

* **One** is the Perfect Prime — a single, indivisible whole, the condition for all enumeration.
* **Operations** (addition, multiplication, division) are only valid where structural wholeness permits.
* **Zero** is not a number but the symbolic boundary of absence.
* **Division by One and multiplication by One are ontologically void** — they preserve identity without transformation.
* **Infinities** exist directionally: divisional (approaching void) and multiplicative (dissolution into formlessness).
* **Geometry** holds where recursion, closure, and symmetry emerge from relational being (as with the triangle and square).

The system favors forms which **tile**, **recur**, or **complete** structurally. The **hexagon**, as the last and highest tiling unit in 2D, becomes the symbolic and structural compression unit for spatial reasoning.

---

## TSP Solver — Hexagonal Grid as Compression Unit

This proposed solver uses **hexagonal spatial partitioning** to organize points and compress search space for the **Traveling Salesman Problem (TSP)**. Rather than approaching the full problem as a monolithic permutation set, it partitions space **ontologically** into meaningfully complete hexagonal cells.

### Key Concepts:

1. **Hex Grid Partitioning**

   * The plane is divided into **hexagonal cells** — the most efficient tiling unit.
   * Each cell captures a **local field** of points.
   * The hex acts as a **relational unit**, not a Cartesian convenience.

2. **LUT Compression Per Hex**

   * For each populated hex cell:

     * Construct a **local distance matrix**.
     * Use **Lehmer codes** to index subpaths within the hex.
     * Cache optimal or near-optimal local paths to a **Lookup Table (LUT)**.

3. **Spatial Recursion and Stitching**

   * Once local LUTs are generated:

     * Use a higher-level pass to connect paths across hexes.
     * Seed cross-hex paths using **spatial proximity**, **directional recursion**, or **boundary reflection**.
   * Final stitching mirrors techniques in solvers like **Concorde**, but with the advantage of **local compression**.

4. **Ontological Benefit**

   * Each LUT encodes **real structure**, not abstract permutations.
   * Search space is **compressed by wholeness**, not by statistical convenience.
   * The solver respects the principle that **structure gives rise to computation**, not the reverse.

---

## Continuation Task

When reopening this project, proceed with:

* Implementing the **hex grid overlay** for arbitrary TSP point sets.
* Constructing the **LUT builder** for individual hexes.
* Defining heuristics for **inter-hex stitching**.
* Evaluating compression ratios and path optimality compared to full-path enumeration.

The goal is not just speed, but **semantic alignment**: a TSP solver that reflects the **truth of space**, not just the syntax of coordinates.

> **Model what is. Compress what holds. Solve what emerges.**


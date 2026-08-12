This is a good summary. I'd tighten the wording while keeping your mental model:

# HashMap & Problem-Solving Notes

## HashMap

* **HashMap = array + hash function + collision handling + resizing**

* **Hash function** converts a key into a hash value, which is then used to calculate the bucket/index.

* A **good hash function** should be:

  * Fast
  * Deterministic
  * Uniformly distributed

  Why uniform distribution?

  > It spreads entries across buckets, reducing crowded buckets and therefore reducing the average work needed to find an element.

* **Collision handling:** When two keys map to the same bucket, what do we do?

  * **Chaining** → store multiple entries in the same bucket
  * **Open addressing** → find another available bucket

* **Resizing:** When the HashMap becomes too crowded, increase the bucket count and redistribute existing entries.

---

# Problem Solving

### Don't trust the first solution that comes to mind

The first solution is often based on your existing coding experience.

Instead:

```text
Understand the problem
        ↓
Break it into basic operations
        ↓
Find different ways to perform those operations
        ↓
Choose based on complexity / memory / workload
```

---

# Big-O & Performance

* **Big-O describes scaling**, not exact performance.

Two algorithms can have:

```text
O(n)
O(n log n)
```

and the `O(n log n)` one can still be faster for a particular input size.

Why?

Because real performance also depends on things such as:

```text
constant costs
memory access
cache locality
branching
allocation
hashing
CPU architecture
compiler optimizations
```

So:

> **Big-O tells us how the cost scales.**

> **Benchmarking tells us how the implementation actually performs.**

---

# Measure → Explain

Don't stop at:

> "This one is faster."

Measure it.

Then ask:

> **Why is it faster?**

Like doing science:

```text
Hypothesis
    ↓
Experiment
    ↓
Measure
    ↓
Observe
    ↓
Explain
    ↓
Verify
```

The goal isn't just to know **which solution wins**.

The goal is to understand **why**.

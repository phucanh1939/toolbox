# Contains Duplicate — Benchmark

We have three approaches:

```text
v1 → For each number, search the rest       O(n²)
v2 → Sort, then check neighbors             O(n log n)
v3 → Store seen values in HashSet            O(n) average
```

We benchmarked them with arrays containing **no duplicates**, so every solution processes the entire input.

```text
                      100           1000          10000          50000    
--------------------------------------------------------------------------
v1 O(n^2)               3 us        298 us      27854 us     293841 us
v2 O(nlogn)             2 us          2 us         18 us         45 us
v3 O(n)                 6 us         58 us        507 us        928 us
```

## What does the scaling show?

### v1 — O(n²)

From `1,000 → 10,000`:

```text
n × 10
time: 298 → 27,854 us
      ≈ ×93
```

From `10,000 → 50,000`:

```text
n × 5
time: 27,854 → 293,841 us
      ≈ ×10.5
```

The runtime grows very quickly because the number of comparisons grows approximately with `n²`.

---

### v2 — O(n log n)

From `1,000 → 10,000`:

```text
n × 10
time: 2 → 18 us
      ≈ ×9
```

From `10,000 → 50,000`:

```text
n × 5
time: 18 → 45 us
      = ×2.5
```

It scales much better than v1.

---

### v3 — O(n)

From `1,000 → 10,000`:

```text
n × 10
time: 58 → 507 us
      ≈ ×8.7
```

From `10,000 → 50,000`:

```text
n × 5
time: 507 → 928 us
      ≈ ×1.8
```

This is roughly the linear scaling we expect.

---

## Why is v3 not the fastest?

Theoretical complexity says:

```text
O(n) < O(n log n) < O(n²)
```

But the actual runtime also depends on the **cost of each operation**.

`v3` uses a HashSet, which involves:

```text
hashing
bucket lookup
collision handling
memory access
possible allocation
```

`v2` uses `std::sort` on a contiguous array, which has very efficient memory access and CPU-cache behavior.

Therefore, in this benchmark:

```text
50,000 elements

v2 →     45 us
v3 →    928 us
```

`v2` is about **20× faster** than v3 here, despite having worse Big-O.

---

## The important lesson

Big-O tells us:

> **How does the cost grow as the input gets larger?**

It does **not** tell us:

> **How many microseconds will this implementation take?**

For example:

```text
v2: O(n log n)
v3: O(n)
```

v3 has the better scaling, but v2 can still be faster for a particular range of `n`.

So when choosing an algorithm:

```text
Big-O
  ↓
Understand scaling

Implementation
  ↓
Understand actual cost

Workload
  ↓
Understand what matters in practice
```

> **Don't use Big-O alone to predict performance. Use it to understand how the solution scales, then consider the actual operations, memory behavior, and workload.**

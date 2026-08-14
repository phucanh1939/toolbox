# Two Sum — Benchmark Results

## Problem

Given an array of integers and a target, find two different indices whose values add up to the target.

For this benchmark, the input is guaranteed to contain **exactly one valid pair**.

We tested three approaches:

```text
v1 - AllPairs       Check every pair
v2 - HashMap        Store value → index
v3 - SortedArray    Sort (value, index), then use two pointers
```

## Results

```text
                                          100           1000          10000          50000
------------------------------------------------------------------------------------------
v1 - AllPairs       O(n^2)               4 us         359 us       26912 us      342014 us
v2 - HashMap        O(n)                41 us         103 us         590 us        1761 us
v3 - SortedArray    O(nlogn)             4 us          40 us         528 us        1756 us
```

---

## v1 — All Pairs

The naive solution checks every possible pair:

```text
(0,1)
(0,2)
(0,3)
...
```

The number of pairs is:

```text
n(n - 1) / 2
```

Therefore:

```text
O(n²)
```

The benchmark shows the scaling clearly.

From `1,000 → 10,000`:

```text
n × 10

359 us → 26,912 us
≈ ×75
```

From `10,000 → 50,000`:

```text
n × 5

26,912 us → 342,014 us
≈ ×12.7
```

The quadratic growth quickly dominates.

At `50,000` elements:

```text
342,014 us ≈ 342 ms
```

---

## v2 — HashMap

For every number `x`, we calculate:

```text
needed = target - x
```

Then we ask the HashMap:

```text
"Have we already seen needed?"
```

Average complexity:

```text
lookup  → O(1)
insert  → O(1)

n elements → O(n) average
```

The measured scaling is much better.

From `1,000 → 10,000`:

```text
n × 10

103 us → 590 us
≈ ×5.7
```

From `10,000 → 50,000`:

```text
n × 5

590 us → 1,761 us
≈ ×3
```

At `50,000`:

```text
v1 → 342,014 us
v2 →   1,761 us
```

The HashMap solution is roughly **194× faster** than the naive solution in this benchmark.

---

## v3 — Sorted Array + Two Pointers

Instead of using extra lookup storage, we:

1. Store `(value, originalIndex)`.
2. Sort by value.
3. Put one pointer at each end.
4. Move the pointers based on the current sum.

Because the array is sorted:

```text
sum > target → move right left
sum < target → move left right
```

Complexity:

```text
Create pairs    → O(n)
Sort            → O(n log n)
Two-pointer     → O(n)

Total           → O(n log n)
```

The interesting result is that it performs **very similarly to the HashMap**.

At `50,000`:

```text
HashMap       → 1,761 us
SortedArray   → 1,756 us
```

The `O(n log n)` solution is actually **slightly faster** in this particular benchmark.

---

# Why can O(n log n) beat O(n)?

This is the important lesson from the benchmark.

The theoretical ordering is:

```text
O(n) < O(n log n) < O(n²)
```

But that doesn't mean:

```text
O(n) is always faster than O(n log n)
```

Big-O describes **how the cost scales**, not the complete cost of the implementation.

### HashMap has hidden costs

The HashMap approach involves things such as:

```text
hash calculation
bucket lookup
pointer/indirect memory access
collision handling
memory allocation
rehashing/resizing
```

Even though the lookup is theoretically `O(1)` average, each lookup can be relatively expensive.

### SortedArray has favorable memory behavior

The sorted approach works with a contiguous `vector`:

```text
[value, index]
[value, index]
[value, index]
[value, index]
...
```

After sorting, the two-pointer scan moves sequentially through this contiguous memory.

This gives the CPU good **cache locality**.

`std::sort` is also a highly optimized library implementation.

So the actual cost can look like:

```text
HashMap:
O(n) × relatively expensive operations

SortedArray:
O(n log n) × relatively cheap operations
```

For this input range, those constant factors are large enough that the `O(n log n)` solution can compete with—or slightly beat—the `O(n)` solution.

---

# What the Benchmark Actually Tells Us

The benchmark does **not** prove that SortedArray is always faster than HashMap.

It tells us:

> **For this implementation, hardware, compiler, input distribution, and input sizes, the measured performance is very close, with SortedArray slightly faster at 50,000 elements.**

The complexity still matters.

If the input becomes sufficiently large, the asymptotic difference can eventually become important.

And if the workload changes, the result can change too.

For example:

```text
different input distribution
different CPU
different compiler
different allocator
different container implementation
different input size
```

can all affect the result.

---

# Main Lesson

This benchmark reinforces the same lesson from **Contains Duplicate**:

> **Big-O describes scaling, not absolute performance.**

And more importantly:

> **Don't choose an algorithm only by looking at its Big-O. Understand what operations it performs, measure the implementation, and explain the observed result.**

The process is:

```text
Understand the problem
        ↓
Break it into basic operations
        ↓
Find different ways to perform them
        ↓
Analyze complexity
        ↓
Implement
        ↓
Measure
        ↓
Explain the result
        ↓
Question the explanation
```

That's the useful part of this exercise: **we didn't just learn that HashMap is O(n). We discovered what "O(n)" actually means when it meets a real CPU and real memory.**

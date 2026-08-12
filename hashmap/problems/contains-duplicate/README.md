# Contains Duplicate

Problem:

```text
Given an array of integers,
determine whether any number appears more than once.
```

Example:

```text
[1, 2, 3, 1] → true
[1, 2, 3, 4] → false
```

## Basic Operation

Instead of immediately thinking about an algorithm:

```text
What do we actually need to know?

For each number:
    Has this number appeared before?
```

This gives us a few different approaches.

## Approach 1: Brute Force

For each number, search the rest of the array:

```cpp
for (int i = 0; i < size - 1; ++i)
{
    for (int j = i + 1; j < size; ++j)
    {
        if (array[i] == array[j])
            return true;
    }
}
```

```text
Time:   O(n²)
Memory: O(1)
```

Simple, but we do a lot of comparisons.

---

## Approach 2: Sort

Sort the array first:

```text
[4, 2, 1, 3, 2]
        ↓
[1, 2, 2, 3, 4]
```

After sorting, duplicates must be next to each other.

```cpp
std::sort(array, array + size);

for (int i = 0; i < size - 1; ++i)
{
    if (array[i] == array[i + 1])
        return true;
}
```

```text
Time:   O(n log n)
Memory: depends on sorting implementation
```

Trade-off:

> **We spend time sorting to make the duplicate check simple.**

---

## Approach 3: HashSet

Think about the operation directly:

```text
For each number:
    Have I seen this before?
```

We need a structure with:

```text
Fast lookup
Fast insertion
```

A HashSet fits:

```cpp
std::unordered_set<int> seen;
seen.reserve(size);

for (int i = 0; i < size; ++i)
{
    if (seen.find(array[i]) != seen.end())
        return true;

    seen.emplace(array[i]);
}
```

```text
Average time: O(n)
Worst case:   O(n²)
Memory:       O(n)
```

The key idea:

```text
A → remember A
B → remember B
C → remember C
A → already seen → duplicate
```

---

## What We Learned

The important lesson isn't:

> **"Contains Duplicate → use HashSet."**

The useful reasoning is:

```text
Problem
  ↓
What does it actually ask?
  ↓
For each number:
    Has it appeared before?
  ↓
What information do we need?
  ↓
A collection of previously seen values
  ↓
What operations do we need?
    lookup + insert
  ↓
Choose a data structure
```

And there are multiple valid solutions:

```text
Brute Force     → O(n²), O(1) memory
Sort            → O(n log n)
HashSet         → O(n) average, O(n) memory
```

> **The first solution that comes to mind is not necessarily the structure of the problem. First identify the basic operation, then explore different ways to perform it.**

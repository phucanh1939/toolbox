# A General Way to Approach Problems

Don't immediately optimize the first solution that comes to mind.

> **The first solution in your mind can be a trap.**

> **Don't let your first implementation define how you think about the problem.**

For example, the problem is:

```text
Given an array of numbers,
determine whether any number appears more than once.
```

The first solution that may come to mind:

```text
For each number:
    Search in the rest
```

This is a valid solution, but don't assume it represents the structure of the problem.

```text
Understand the question
        ↓
Identify the basic operation(s)
        ↓
Find different ways to perform them
        ↓
Choose based on complexity / memory / workload
```

### 1. Understand the Question

Don't start with:

> **"How can I make my first solution faster?"**
> **"What algorithm should I use?"**

Start with:

> **"What is the problem actually asking me to do?"**
> **"What are the basic operations required to do it?"**

### 2. Identify the Basic Operations

Break the problem down into the fundamental operations we need.

For the duplicate problem:

```text
Does this array contain a duplicate?

        ↓

For each number:
    Does this number have a duplicate?
```

Now we have identified an important operation:

```text
Does X have a duplicate?
```

### 3. Find Different Ways to Perform the Operations

Only after understanding the operations, explore different approaches:

```text
Search the rest of the array
    → O(n²) overall

Check a "seen" collection
    → O(n) overall

Sort + check neighboring values
    → O(n log n)
```

Different approaches may require completely different algorithms or data structures.

### 4. Choose

Compare:

```text
Time complexity
Memory usage
Input size
Workload / access pattern
Cache behavior
Implementation complexity
```

Then choose the approach that fits the problem.

### The Important Habit

> **Understand the problem → identify the basic operations → explore ways to perform them → choose the appropriate solution.**

**Don't let your first implementation define how you think about the problem.**
# Algorithm Toolbox

A collection of algorithms, data structures, patterns, and problem-solving techniques learned through implementation and practice.

The goal is not to memorize solutions.

The goal is to build a toolbox that helps answer:

* What is the basic operation?
* What makes the straightforward solution expensive?
* What data structure or algorithm can reduce that cost?
* What trade-offs does that introduce?
* Does the benchmark actually support our reasoning?

## Learning Process

For each topic, the general process is:

```text
Understand the problem
        ↓
Find the basic operation
        ↓
How to do it?
        ↓
How to do it effectively?
        ↓
Choose the structure / algorithm
        ↓
Implement
        ↓
Test & benchmark
        ↓
Explain the result
```

The benchmark is not there to prove that one algorithm is universally better.

It is there to compare implementations under controlled conditions and understand where the costs actually come from.

## Structure

```text
toolbox/
├── common/
│   └── shared benchmarking utilities
│
├── hashmap/
│   ├── README.md
│   └── problems/
│       ├── two-sum/
│       └── map-sum-pairs/
│
└── README.md
```

Each topic has its own section and README.

The topic README contains the concepts, reasoning, implementations, and conclusions learned while working through its problems.

## Current Topics

### HashMap

`hashmap/`

The first completed section of the toolbox.

Topics explored:

* HashMap fundamentals
* Lookup and insertion
* Hashing and its costs
* Two Sum
* Map Sum Pairs
* Prefix aggregation
* Comparing naive, HashMap, and Trie-based approaches
* Benchmarking theoretical complexity against real implementation costs

See [`hashmap/README.md`](hashmap/README.md).

## Philosophy

The toolbox is built around understanding rather than memorization.

A solution is useful when we understand:

1. **What the problem is really asking.**
2. **What basic operation dominates the work.**
3. **Why the straightforward approach becomes expensive.**
4. **How a different algorithm or data structure changes that cost.**
5. **What new costs or trade-offs that solution introduces.**
6. **Whether the implementation behaves as expected in practice.**

The goal is to eventually have a collection of tools that can be recognized and applied naturally when solving new problems.

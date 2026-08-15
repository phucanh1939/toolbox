# Map Sum Benchmark Results

## Benchmark

The benchmark inserts all keys, then queries a 3-character prefix for every key.

| Version | Approach              | Complexity |    100 |    1,000 |     10,000 |        50,000 |
| ------- | --------------------- | ---------: | -----: | -------: | ---------: | ------------: |
| v0      | Naive                 |      O(NP) |  98 us | 8,858 us | 455,527 us | 12,118,656 us |
| v1      | HashMap + Prefix Sums |       O(L) | 225 us | 1,192 us |   3,239 us |     16,208 us |
| v2      | Trie                  |       O(L) |  17 us |   125 us |     325 us |      1,624 us |

Where:

* `N` = number of stored keys
* `P` = prefix length
* `L` = key length

The benchmark uses a fixed 3-character prefix, so the naive solution effectively behaves like `O(N)` for this particular test.

## v0 — Naive

The naive solution stores the key-value pairs and, for every `sum(prefix)`, scans every stored key.

For each key, it checks whether the key starts with the requested prefix.

The problem is that the same work is repeated for every query.

As the number of keys grows:

```text
100 → 1,000 → 10,000 → 50,000
```

the runtime grows dramatically:

```text
98 us
8,858 us
455,527 us
12,118,656 us
```

This is the clearest sign that we are doing unnecessary repeated work.

## v1 — HashMap + Prefix Sums

The next approach precomputes the sum for every prefix during `insert()`.

Instead of asking:

> "Which keys start with this prefix?"

every time `sum()` is called, we maintain:

```text
"a"   → sum
"ap"  → sum
"app" → sum
"appl" → sum
"apple" → sum
```

Then `sum(prefix)` becomes a HashMap lookup.

This moves work from `sum()` to `insert()`.

The result is a large improvement for larger inputs:

```text
50,000 keys

Naive:    12,118,656 us
HashMap:       16,208 us
```

The trade-off is that insertion now performs work for every character in the key and requires storing the generated prefixes.

## v2 — Trie

The Trie takes the same basic idea as the prefix-sum approach but represents the prefix relationship directly in the data structure.

Instead of storing:

```text
"app"
"appl"
"apple"
```

as independent string keys, the Trie represents them as a shared path:

```text
a → p → p → l → e
```

Each node stores the accumulated prefix sum.

Therefore, `sum(prefix)` simply walks the prefix path.

The benchmark shows a substantial improvement:

```text
50,000 keys

HashMap:  16,208 us
Trie:      1,624 us
```

The Trie is approximately 10× faster than the HashMap version in this benchmark.

## What Changed Between the Versions?

The progression is more important than the absolute numbers.

### v0

```text
For every query:
    scan every key
    check whether it matches
```

We repeatedly discover the same prefix relationship.

### v1

```text
During insert:
    calculate prefixes
    store their sums

During sum:
    lookup the prefix
```

We eliminate the repeated scanning by precomputing the information.

### v2

```text
During insert:
    walk the prefix path
    update prefix sums

During sum:
    walk the prefix path
```

The Trie stores the prefix relationship itself, eliminating the need to construct and hash separate prefix strings.

## Main Takeaway

The benchmark demonstrates three different ways to solve the same problem:

> **Naive:** repeatedly discover the information when it is needed.

> **HashMap:** precompute the information and store it explicitly.

> **Trie:** structure the data so the prefix relationship is represented directly.

The Trie performs best in this particular benchmark, but this does **not** mean "Trie is always better."

The concrete implementation matters. A Trie can have significant memory overhead depending on how its child nodes are represented. Our earlier memory experiment showed exactly this: our `children[26]` Trie used substantially more memory than the HashMap implementation.

So the useful conclusion is not simply that one data structure wins.

The more general lesson is:

> **When a problem repeatedly asks questions about a relationship in the data, we can often improve performance by choosing a data structure that stores that relationship directly.**

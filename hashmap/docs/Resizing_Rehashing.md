# HashMap Resizing & Rehashing

As more entries are inserted, the HashMap becomes more **crowded**.

We measure this using the **load factor**:

```text
load factor = entries / buckets (entries per bucket)
```

For example:

```text
10 buckets
7 entries

load factor = 7 / 10 = 0.7
```

A HashMap usually defines a **maximum load factor**.

When inserting would make the load factor too high:

```text
Insert
  ↓
Too crowded?
  ↓ Yes
Increase bucket count
  ↓
Recalculate bucket for existing entries
  ↓
Move entries
```

### Why do we need to move existing entries?

Because the bucket index depends on the number of buckets.

Before:

```text
hash(key) % 10
```

After resizing:

```text
hash(key) % 20
```

The same key can therefore belong to a different bucket.

```text
Before:

hash(A) = 42
42 % 10 = 2

After:

hash(A) = 42
42 % 20 = 2
```

Another key might change:

```text
hash(B) = 13

13 % 10 = 3
13 % 20 = 13
```

So existing entries must be **redistributed**.

This process is commonly called **rehashing**.

### Cost

Resizing requires processing all existing entries:

```text
O(n)
```

So a resize is expensive, but it doesn't happen on every insertion.

The HashMap accepts occasional expensive resizes to keep normal operations fast.

> **Resize → redistribute existing entries → continue inserting.**

### Avoiding Unnecessary Resizing

If we know approximately how many entries we will store, we can provide an **initial capacity** or use `reserve()`:

```cpp
std::unordered_map<int, Unit> units;
units.reserve(10000);
```

The library normally provides its own:

* Hash function
* Maximum load factor
* Growth/resizing strategy

`reserve(10000)` tells the HashMap to prepare for at least that many elements, allowing us to avoid unnecessary resizing as the map grows.

This is similar to:

```cpp
std::vector<Unit> units;
units.reserve(10000);
```

> **If you know the expected size, reserve ahead of time to avoid unnecessary resizing.**

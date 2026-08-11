## Real Example: Collision Detection

A common game-engine example is **broad-phase collision detection**.

Suppose we have `n` game objects and want to find which pairs might collide.

### Approach 1: Check Every Pair

Store all objects in a contiguous array:

```text
[Object][Object][Object][Object]...
```

Then check every pair:

```text
Object 1 ↔ Object 2
Object 1 ↔ Object 3
...
Object 999 ↔ Object 1000
```

The algorithm is:

```text
O(n²)
```

The advantage is excellent cache locality:

```text
[ A ][ B ][ C ][ D ][ E ][ F ]
  ↓    ↓    ↓    ↓
sequential memory access
```

For a small number of objects, this can be extremely fast.

---

### Approach 2: Spatial Structure

Instead of comparing every object with every other object, organize objects by their location.

For example, use a **spatial grid**:

```text
World

┌───────┬───────┬───────┐
│ A  B  │       │   C   │
│       │   D   │       │
├───────┼───────┼───────┤
│       │ E  F  │       │
│   G   │       │   H   │
└───────┴───────┴───────┘
```

An object only needs to check objects in nearby cells.

This dramatically reduces the number of collision checks and can approach **O(n)** for suitable distributions.

The structure may have more complicated memory access:

```text
Object
  ↓
Spatial cell
  ↓
Objects in cell
```

so it may have worse locality than a simple contiguous array.

---

### When Does Big-O Win?

With only:

```text
20 objects
```

the simple approach performs roughly:

```text
20² = 400 pair checks
```

400 very cheap, sequential operations may be faster than maintaining and querying a spatial structure.

But with:

```text
10,000 objects
```

the naive approach performs roughly:

```text
10,000² = 100,000,000 pair checks
```

At this point, the excellent cache locality cannot compensate for the enormous amount of unnecessary work.

The spatial structure wins because it dramatically reduces the amount of work.

---

### Lesson

This demonstrates the relationship between **Big-O and cache locality**:

```text
Small n
    ↓
Cache locality + low constant cost
can make the simple algorithm faster

Large n
    ↓
The scaling difference becomes dominant
    ↓
Better Big-O wins
```

The general principle is:

> **Cache locality can make an algorithm faster, but it cannot usually compensate for a sufficiently large difference in how the amount of work scales.**

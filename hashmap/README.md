# HashMap

## What is a HashMap?

A **HashMap** stores values using a **key** and uses the key to quickly find where the value is stored.

```text
Key
 ↓
Hash Function
 ↓
Bucket / Index
 ↓
Value
```

Example:

```text
"player_123" → Player
"enemy_42"   → Enemy
```

Typical complexity:

```text
Average: O(1)
Worst:   O(n)
```

> **Use the key to calculate where to look instead of searching through every element.**

---

## Why Does HashMap Exist?

With an array:

```text
[Player][Enemy][NPC][Boss]...
```

Finding an element by ID requires searching:

```text
O(n)
```

A HashMap transforms:

```text
ID
 ↓
Hash
 ↓
Bucket
```

so it can go directly to the relevant location.

The problem it solves is:

> **Fast lookup by an arbitrary key.**

---

## How Does It Work?

A simplified HashMap uses an array of buckets:

```text
Key
 ↓
hash(key)
 ↓
hash % bucketCount
 ↓
bucket
```

Example:

```text
"Apple"
   ↓
hash → 42
   ↓
42 % 8 → 2
   ↓
bucket[2]
```

If multiple keys map to the same bucket, we have a **collision**.

The HashMap needs a collision-handling strategy, such as:

```text
Chaining
Open Addressing
```

---

## Load Factor & Rehashing

As more entries are inserted, buckets become more crowded.

```text
load factor = entries / buckets
```

When the load factor becomes too high:

```text
Increase buckets
      ↓
Redistribute entries
      ↓
Rehashing
```

This keeps collisions under control.

---

## When Should I Use It?

Use a HashMap when the main operation is:

> **Find something using a key.**

Good examples:

```text
EntityId → Entity
ItemId   → Item
Name     → Object
```

Don't automatically use it just because lookup is involved.

Consider:

```text
How often do I lookup?
Is it a hot path?
How large is the data?
Could an array/vector be simpler and faster?
```

---

## Trade-offs

### Advantages

```text
Average O(1) lookup
Fast insertion/removal
Works with arbitrary keys
```

### Costs

```text
More memory
Collision handling
Rehashing
More complex than an array
Usually worse cache locality
```

---

## Mental Model

Think of a HashMap as:

```text
Array
  +
Hash Function
  +
Collision Handling
  +
Resizing
```

The core idea:

> **Turn a key into a location so we don't have to search the entire collection.**

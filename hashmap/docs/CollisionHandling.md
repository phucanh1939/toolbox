# Collision Handling

## What is a Collision?

A **collision** happens when different keys map to the same bucket.

```text
Key A → hash → bucket 3
Key B → hash → bucket 3
```

The HashMap cannot store both as if they were the same entry, so it needs a way to handle the collision.

---

## 1. Chaining

Each bucket can contain multiple entries.

```text
Bucket 3

[A → Value]
[B → Value]
[C → Value]
```

When looking up `B`:

```text
hash(B)
  ↓
bucket 3
  ↓
compare keys
  ↓
A ✗
B ✓
```

The bucket can be implemented using a linked list, dynamic array, or another structure.

**Pros:**

* Simple
* Bucket can hold an arbitrary number of entries

**Cons:**

* More memory overhead
* Following pointers can hurt cache locality
* Too many collisions make lookup slower

---

## 2. Open Addressing

Store every entry directly inside the bucket array.

If the target bucket is occupied, find another slot.

```text
hash(A) → 3

bucket:
0
1
2
3 → A
4
5
```

Now `B` also hashes to `3`:

```text
hash(B) → 3 → occupied
              ↓
            try 4
              ↓
            bucket 4
```

Common strategies include:

```text
Linear probing
Quadratic probing
Double hashing
```

**Pros:**

* Entries are stored contiguously
* Good cache locality
* No separate linked nodes

**Cons:**

* Clustering can occur
* Performance degrades as the table becomes full
* Removal is more complicated

---

## The Important Idea

Collision handling doesn't eliminate collisions.

It answers:

> **"What do we do when multiple keys want the same bucket?"**

The two major approaches are:

```text
Collision
   │
   ├── Chaining
   │     └── Multiple entries in one bucket
   │
   └── Open Addressing
         └── Find another empty slot
```

And the choice affects:

* Memory usage
* Cache locality
* Lookup performance
* Insertion/removal complexity

> **A good HashMap needs both a good hash function and a good collision-handling strategy.**

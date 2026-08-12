# Hash Function

## What is a Hash Function?

A **hash function** takes an input key and deterministically produces a hash value.

```text
key
 ↓
hash function
 ↓
hash value
 ↓
bucket/index
```

For a HashMap, the hash value is used to decide **where the key should be stored or searched for**.

For example:

```text
key = 42
      ↓
hash(42) = 123456
      ↓
123456 % bucketCount
      ↓
bucket 6
```

The same key should always produce the same hash value.

---

## What Makes a Good Hash Function?

A good hash function for a HashMap should have:

* **Fast computation** — hashing happens during lookup and insertion.
* **Deterministic result** — the same key produces the same hash.
* **Good distribution** (Uniform distribution) — keys should be spread as uniformly as possible across buckets.
* **Few predictable collisions/clusters** — different keys shouldn't repeatedly end up in the same bucket.

We don't need zero collisions. With many possible keys and limited buckets, collisions are unavoidable.

The goal is:

> **Fast to calculate + distribute keys evenly.**

---

## Why Does Distribution Matter?

Consider 100 keys and 10 buckets.

### Good distribution

```text
Bucket 0 → 10 keys
Bucket 1 → 10 keys
...
Bucket 9 → 10 keys
```

A lookup examines about **10 entries per bucket on average**.

### Bad distribution

```text
Bucket 0 → 1 key
Bucket 1 → 1 key
...
Bucket 8 → 1 key
Bucket 9 → 91 keys
```

91% of the keys are now in bucket 9.

A random lookup therefore has:

```text
9%  → bucket with 1 key
91% → bucket with 91 keys
```

Average bucket size examined (Average operations needed for a lookup):

```text
0.09 × 1 + 0.91 × 91 = 82.9
```

So roughly:

```text
Good distribution → 10 entries / lookup
Bad distribution  → 82.9 entries / lookup
```

The bad distribution creates much more work because of **clustering**.

> **Uniform distribution keeps buckets small, which keeps collision handling cheap.**

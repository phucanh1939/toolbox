# HashMap

## 1. What is a HashMap?

A **HashMap** is a data structure that stores values using a **key**.

Instead of asking:

> "Where is the value?"

by searching through every element, we ask:

> "Given this key, where should its value be?"

Conceptually:

```text
Key → Value

"player_123" → Player
"enemy_42"  → Enemy
"sword_01"  → Item
```

The important property is that a HashMap is designed to make lookup **very fast**, typically:

```text
Average: O(1)
Worst:   O(n)
```

The key idea is:

> **Use the key itself to calculate where the value should live.**

---

# 2. Why Does HashMap Exist?

## The problem

Suppose we have an array:

```text
[ Player, Enemy, NPC, Boss, ... ]
```

And we want to find an entity with ID `9001`.

With an array, we don't know where `9001` is.

We have to search:

```text
0 → 1 → 2 → 3 → 4 → ... → 9001
```

If there are `n` elements, lookup can take:

```text
O(n)
```

A sorted array can improve this to:

```text
O(log n)
```

using binary search.

But we want something closer to:

```text
O(1)
```

We want to go directly to the answer.

---

# 3. The Core Idea

Imagine we have:

```text
Key: "Alice"
```

We need to turn `"Alice"` into a number.

For example:

```text
hash("Alice") → 137421
```

Then we turn that number into an array index:

```text
137421 % capacity → 5
```

So:

```text
"Alice"
   ↓
hash
   ↓
137421
   ↓
% capacity
   ↓
5
   ↓
array[5]
```

Now we know where to look.

That's the fundamental idea behind a HashMap.

---

# 4. How Does It Work?

A simplified HashMap contains an array called **buckets**.

```text
Bucket array

0
1
2
3
4
5
6
7
```

Suppose we insert:

```text
"Apple" → 100
```

First:

```text
hash("Apple")
```

Suppose it produces:

```text
42
```

With 8 buckets:

```text
42 % 8 = 2
```

So we store it in bucket `2`.

```text
0
1
2 → ("Apple", 100)
3
4
5
6
7
```

Later, when we ask:

```text
map["Apple"]
```

the HashMap performs the same calculation:

```text
hash("Apple") → 42
42 % 8 → 2
```

It immediately goes to bucket `2`.

That's why lookup can be approximately **O(1)**.

---

# 5. But What If Two Keys Go To The Same Bucket?

This is called a **collision**.

For example:

```text
hash("Apple") % 8 = 2
hash("Banana") % 8 = 2
```

Both want bucket `2`.

We can't simply overwrite Apple.

One common solution is **chaining**.

The bucket contains multiple entries:

```text
2 → ("Apple", 100)
    ("Banana", 200)
    ("Orange", 300)
```

When looking for `"Banana"`:

```text
hash("Banana")
       ↓
bucket 2
       ↓
compare keys
       ↓
"Apple"  ✗
"Banana" ✓
```

So a HashMap actually performs two operations:

```text
1. Hash the key → find bucket
2. Compare keys → find exact entry
```

The hash gets us **close**.

The key comparison gives us the **exact answer**.

---

# 6. Hash Function

A hash function takes a key and produces an integer.

Conceptually:

```cpp
size_t hash(Key key);
```

For example:

```text
hash("Apple")  → 123456
hash("Banana") → 987654
hash("Orange") → 456789
```

A good hash function should generally:

* Be deterministic
* Be fast
* Spread keys across buckets
* Minimize collisions

For the same key:

```text
hash("Apple")
```

must always produce the same result during that map's operation.

---

# 7. Why Not Just Use The Key As An Array Index?

For integers, we could theoretically do:

```cpp
array[playerId]
```

If:

```text
playerId = 500
```

we use:

```text
array[500]
```

That's extremely fast.

But IDs might look like:

```text
10
1000000
938475923
```

Creating an array large enough for:

```text
array[938475923]
```

would waste enormous amounts of memory.

A HashMap lets us **compress a huge key space into a smaller bucket array**.

For example:

```text
Key space:

0 ──────────────────────────────── 1,000,000,000

Buckets:

0 1 2 3 4 5 6 7 8 9
```

The hash function maps the huge key space onto a manageable number of buckets.

---

# 8. When Should You Use a HashMap?

Use a HashMap when you frequently need:

> **Find something using a key.**

Typical pattern:

```text
Key → Object
```

### Example: Game entities

```cpp
unordered_map<EntityId, Entity> entities;
```

Then:

```cpp
entities[entityId]
```

gives us the entity.

---

## Example: Item database

```text
Item ID → Item data

"sword_01" → Sword
"bow_01"   → Bow
"potion_01" → Potion
```

Instead of:

```cpp
for (Item item : items)
{
    if (item.id == id)
        return item;
}
```

we can do:

```cpp
items[id]
```

---

## Example: Counting things

HashMaps are also useful when the key represents a category.

For example, count how many times each word appears:

```text
"apple"  → 3
"banana" → 7
"orange" → 2
```

Conceptually:

```cpp
counts[word]++;
```

---

# 9. When NOT To Use It

A HashMap isn't automatically better than an array or vector.

If your keys are dense integers:

```text
0
1
2
3
4
5
6
7
```

then an array is usually simpler and faster:

```cpp
players[id]
```

A HashMap makes more sense when keys are sparse or not naturally usable as array indices:

```text
100
9384
928374
1000000000
```

or:

```text
"player_abc"
"sword_legendary"
"quest_42"
```

---

# 10. Trade-offs

HashMaps trade memory and complexity for fast lookup.

## Advantages

### Fast lookup

Average:

```text
O(1)
```

### Fast insertion

Average:

```text
O(1)
```

### Fast removal

Average:

```text
O(1)
```

### Flexible keys

Keys can be:

```text
integer
string
enum
struct
custom object
```

as long as we can hash and compare them.

---

## Disadvantages

### More memory

A HashMap needs additional structures:

```text
buckets
entries
links / metadata
unused capacity
```

An array can simply be:

```text
[value][value][value][value]
```

A HashMap is usually more complicated.

---

### Collisions

Different keys can produce the same bucket:

```text
Key A ──┐
        ├→ bucket 5
Key B ──┘
```

Too many collisions make lookup slower.

In the extreme:

```text
O(n)
```

---

### Poorer cache locality

An array/vector stores elements close together:

```text
[A][B][C][D][E][F]
```

The CPU cache likes this.

A HashMap can involve jumping around memory:

```text
bucket
   ↓
entry
   ↓
another entry
```

So even though both operations may theoretically be O(1), a vector can sometimes be much faster in practice.

---

### Ordering

A normal HashMap does not generally guarantee that elements come out in insertion order.

If you need ordering, another data structure may be more appropriate.

---

# 11. Load Factor

Imagine:

```text
10 buckets
```

and:

```text
2 entries
```

Most buckets are empty.

```text
[x][ ][ ][x][ ][ ][ ][ ][ ][ ]
```

That's good for collisions, but wastes memory.

Now imagine:

```text
10 buckets
100 entries
```

Many entries must share buckets.

```text
[x][xxxxxxxx][xx][xxxxxxxxx]...
```

Collisions become more likely.

The **load factor** describes how full the table is.

Conceptually:

```text
load factor = number of entries / number of buckets
```

For example:

```text
50 entries / 100 buckets = 0.5
```

When the load factor becomes too high, the HashMap usually **grows**.

---

# 12. Rehashing and Load Factor

A HashMap has a limited number of **buckets**. As more entries are inserted, the buckets become more crowded, which increases the chance of collisions.

To control this, a HashMap defines a **maximum load factor**.

```text
load factor = number of entries / number of buckets
```

For example:

```text
10 buckets
7 entries

load factor = 7 / 10 = 0.7
```

Suppose the maximum load factor is `0.75`.

```text
7 / 10 = 0.7   → okay
8 / 10 = 0.8   → too high
```

When an insertion would make the load factor exceed the maximum, the HashMap **resizes** its bucket array.

For example:

```text
10 buckets
    ↓
20 buckets
```

The existing entries cannot simply stay in their old buckets because the bucket index depends on the number of buckets:

```text
old: hash(key) % 10
new: hash(key) % 20
```

Therefore, the HashMap goes through the existing entries and calculates their new bucket positions.

This process is called **rehashing** or **redistribution**:

```text
Insert
  ↓
Load factor too high?
  ↓ yes
Increase bucket count
  ↓
Redistribute existing entries
  ↓
Insert new entry
```

The important idea is:

> **A HashMap grows not because every bucket is literally full, but because the table has become crowded enough that collisions would become too expensive.**


---

# 13. A Simple HashMap From Scratch

A very simplified implementation could look like:

```cpp
struct Entry
{
    Key key;
    Value value;
};

std::vector<std::vector<Entry>> buckets;
```

Insertion:

```cpp
void insert(Key key, Value value)
{
    size_t hash = hashFunction(key);
    size_t index = hash % buckets.size();

    buckets[index].push_back({key, value});
}
```

Lookup:

```cpp
Value* find(Key key)
{
    size_t hash = hashFunction(key);
    size_t index = hash % buckets.size();

    for (Entry& entry : buckets[index])
    {
        if (entry.key == key)
            return &entry.value;
    }

    return nullptr;
}
```

This tiny implementation already contains the essential idea:

```text
key
 ↓
hash
 ↓
bucket
 ↓
compare keys
 ↓
value
```

Real implementations are considerably more sophisticated.

---

# 14. How Did People Create HashMaps?

The idea came from a simple observation:

> We want array-like direct access, but our keys aren't suitable array indices.

Suppose we have keys:

```text
17
42
91
123
```

We could create a function:

```text
key → array position
```

For example:

```text
key % 10
```

Then:

```text
17  → 7
42  → 2
91  → 1
123 → 3
```

Now we can use an array:

```text
0
1 → 91
2 → 42
3 → 123
4
5
6
7 → 17
8
9
```

That's basically the beginning of a HashMap.

The key insight wasn't:

> "Let's invent a complicated data structure."

It was:

> **"Can we transform arbitrary keys into positions in an array?"**

---

# 15. The Collision Problem

The first obvious problem appears immediately.

Consider:

```text
17 % 10 = 7
27 % 10 = 7
37 % 10 = 7
```

Three different keys want the same location.

So people needed strategies for handling collisions.

Two major approaches became common.

---

## Chaining

Store multiple entries in the same bucket.

```text
bucket 7

17 → value
27 → value
37 → value
```

Usually implemented with some form of linked structure or bucket-local storage.

---

## Open Addressing

Instead of storing multiple entries at the same bucket, search for another empty bucket.

For example:

```text
17 → bucket 7
27 → bucket 7 → occupied
          ↓
        bucket 8
```

So:

```text
7 → 17
8 → 27
```

There are different strategies for finding the next location:

```text
Linear probing
Quadratic probing
Double hashing
```

Modern high-performance HashMaps often use sophisticated forms of open addressing.

---

# 16. Why Is It Called "Hash"?

The word **hash** comes from the idea of taking something complicated and producing a smaller representation.

A hash function transforms:

```text
large / arbitrary input
        ↓
    hash value
```

For example:

```text
"player_928374"
        ↓
     1847293
```

The result isn't the original key.

It's a value useful for locating it.

---

# 17. The Important Mental Model

Don't think of HashMap as:

> "A magic data structure that gives O(1) lookup."

Think of it as:

> **An array + a function that decides where a key should go + collision handling.**

The entire idea can be reduced to:

```text
             Key
              │
              ▼
         Hash Function
              │
              ▼
        Hash Number
              │
              ▼
       Bucket Selection
              │
              ▼
       Collision Handling
              │
              ▼
            Value
```

That's the core of a HashMap.

---

# 18. Complexity

| Operation | Average | Worst Case |
| --------- | ------: | ---------: |
| Find      |    O(1) |       O(n) |
| Insert    |    O(1) |       O(n) |
| Remove    |    O(1) |       O(n) |
| Resize    |       — |       O(n) |

The important word is **average**.

HashMap doesn't magically guarantee constant-time lookup.

Its performance depends heavily on:

* Hash function quality
* Number of buckets
* Load factor
* Collision strategy
* Memory layout

---

# 19. HashMap vs Array vs Sorted Array

| Structure    |        Lookup |       Insert | Memory | Main Strength    |
| ------------ | ------------: | -----------: | -----: | ---------------- |
| Array        | O(1) by index |  O(1) at end |    Low | Direct indexing  |
| Sorted Array |      O(log n) |         O(n) |    Low | Ordered data     |
| HashMap      |  O(1) average | O(1) average | Higher | Key-based lookup |

The important question isn't:

> "Which one is fastest?"

It's:

> **"What information do I have, and what operation do I need?"**

If you have:

```text
index → value
```

use an array.

If you have:

```text
ordered values
```

a sorted structure may make sense.

If you have:

```text
arbitrary key → value
```

a HashMap is a strong candidate.

---

# 20. Final Mental Model

A HashMap solves this problem:

```text
"I have a key.
I don't know where the value is.
I want to find it quickly."
```

It solves it by turning:

```text
Key
 ↓
Hash
 ↓
Bucket
 ↓
Compare
 ↓
Value
```

The trade is:

```text
More memory
+ more complexity
+ possible collisions
+ weaker cache locality

        ↓

Fast average key-based lookup
```

And historically, the idea grows naturally from one simple structure:

```text
Array
  ↓
Need key → position
  ↓
Hash function
  ↓
Collisions
  ↓
Collision handling
  ↓
Resizing / load factor
  ↓
HashMap
```

That is the important story to understand—not just the API.

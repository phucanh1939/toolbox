# Choosing a Data Structure for Game Units

Suppose we are implementing a game with many `Unit` objects.

Each unit has:

```text
Unit
├── Id
├── Position
├── Health
├── ...
```

Different game systems may need different access patterns.

---

## Case 1: We Mostly Iterate Over All Units

Suppose the AI system needs to update every unit:

```cpp
for (Unit& unit : units)
{
    updateAI(unit);
}
```

A vector is a very good choice:

```text
[Unit][Unit][Unit][Unit][Unit][Unit]
```

The units are contiguous in memory.

The CPU can efficiently load nearby units into the cache while iterating.

The operation is:

```text
O(n)
```

The access pattern is predictable:

```text
Unit 0
 ↓
Unit 1
 ↓
Unit 2
 ↓
Unit 3
 ↓
...
```

This is ideal for cache locality.

For systems such as:

* Updating movement
* Updating AI
* Applying status effects
* Rendering preparation
* Physics processing

a vector can be excellent.

---

## Case 2: We Frequently Find a Specific Unit By ID

Suppose another system receives:

```text
UnitId = 93842
```

and needs that exact unit.

With a vector:

```cpp
for (Unit& unit : units)
{
    if (unit.id == 93842)
        return unit;
}
```

This is:

```text
O(n)
```

If there are 10,000 units, we may need to inspect thousands of units.

A HashMap gives us:

```text
UnitId
  ↓
hash
  ↓
bucket
  ↓
Unit
```

Average lookup:

```text
O(1)
```

So if the system frequently performs random lookups by ID, a HashMap becomes attractive.

---

# Case 3: We Need Both

This is the interesting real-world case.

Suppose the game has:

```text
10,000 units
```

And we have two systems:

```text
AI System
→ iterate over every unit

Quest / Combat System
→ frequently find units by ID
```

There isn't necessarily one perfect container.

We can use two structures for the same logical dataset:

```cpp
Vector<Unit> units;
HashMap<UnitId, Unit*> unitsById;
```

Conceptually:

```text
Vector

[Unit A][Unit B][Unit C][Unit D]...
    ↑        ↑        ↑
    │        │        │
    └────────┼────────┘
             │
          HashMap
             │
      ID → Unit*
```

The vector provides:

```text
Fast sequential iteration
Excellent cache locality
```

The HashMap provides:

```text
Fast lookup by ID
```

Each access pattern gets the structure that suits it.

---

## Removing a Unit

Now we have an important problem.

Suppose the vector contains:

```text
Index:

0        1        2        3
[A]      [B]      [C]      [D]
```

We want to remove `B`.

If we preserve order, we have to move everything after it:

```text
[A]      [C]      [D]
         ↑        ↑
       move      move
```

This is `O(n)`.

But if **order doesn't matter**, we can use **swap-back removal**.

Move the last element into the removed element's position:

```text
Before:

0        1        2        3
[A]      [B]      [C]      [D]

Remove B
         ↓

0        1        2
[A]      [D]      [C]
```

Then remove the last slot:

```text
[A]      [D]      [C]
```

The removal itself is now:

```text
O(1)
```

However, there is an important consequence:

> `D` changed its index.

Therefore, if the HashMap stores a vector index:

```text
HashMap<UnitId, Index>
```

we must update `D`'s index after the swap.

For example:

```text
Before:

Vector:
0 → A
1 → B
2 → C
3 → D

HashMap:
A → 0
B → 1
C → 2
D → 3
```

Remove `B`:

```text
Vector:
0 → A
1 → D
2 → C
```

The HashMap must become:

```text
A → 0
C → 2
D → 1   ← updated
```

So the operation becomes:

```text
Find B in HashMap
        ↓
Get its vector index
        ↓
Move last element into that index
        ↓
Update moved element's index
        ↓
Remove last element
```

All of this can remain **O(1)**.

---

## Why Use `UnitId → Index` Instead of `UnitId → Unit*`?

We could store:

```cpp
HashMap<UnitId, Unit*>
```

but if `Unit` objects live inside a vector, the vector can move them when it grows.

For example:

```text
Old vector:

[Unit A][Unit B][Unit C]

       ↓ resize

New memory:

[Unit A][Unit B][Unit C][Unit D]
```

The objects may now have different addresses.

A pointer stored in the HashMap could become invalid.

Using an index:

```cpp
HashMap<UnitId, size_t>
```

can be easier to manage, because the HashMap points to a **logical position**, not a memory address.

When swap-back moves an element, we update its index.

---

# Case 4: When an Array Is Clearly Better

Suppose:

```text
Units = 20
```

and almost every system does:

```text
for each unit
```

while ID lookups are rare.

A vector is probably the simpler and better choice:

```cpp
Vector<Unit> units;
```

Even though finding a unit by ID is `O(n)`, `n` is tiny.

You get:

```text
simple memory layout
+ excellent cache locality
+ low overhead
+ simple iteration
```

A HashMap would introduce overhead that may not provide meaningful benefits.

---

# Case 5: When a HashMap Is Clearly Better

Suppose:

```text
Units = 100,000
```

and the main operation is:

```text
Find Unit with ID X
```

For example:

```text
DamageEvent
    ↓
UnitId = 928374
    ↓
find target unit
```

Doing a linear search through 100,000 units for every event would be expensive.

A HashMap gives approximately:

```text
UnitId
  ↓
HashMap
  ↓
Index
  ↓
Vector[Index]
  ↓
Unit
```

with average:

```text
O(1)
```

Here the scaling advantage is much more important than the HashMap's worse locality.

---

# The Important Question

Don't ask:

> "Should I use an array or HashMap for Units?"

Ask:

> **"How will I access the Units?"**

Think about the operations:

```text
Need to iterate all units?
        ↓
Vector is attractive

Need random lookup by ID?
        ↓
HashMap is attractive

Need both?
        ↓
Use both when the extra complexity is justified
```

A particularly useful combination is:

```text
Vector<Unit>
    +
HashMap<UnitId, Index>
```

where:

```text
Vector
→ optimized for iteration

HashMap
→ optimized for lookup

Swap-back removal
→ keeps vector removal O(1)

HashMap index update
→ keeps both structures consistent
```

The important lesson is:

> **One logical dataset can have multiple data structures, each optimized for a different access pattern.**

The cost is additional memory and the responsibility to keep the structures synchronized.

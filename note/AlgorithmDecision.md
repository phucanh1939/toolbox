# Choosing Between Different Solutions

> **Look at the workload, not the data structure.**

> **Access pattern → Scale → Cost → Measure**

For a given problem, ask myself:

* **How will I access the data?**

  * Iterate?
  * Lookup by key/ID?
  * Insert/delete?
  * Random access?

* **How large can the data become?**

  * What is the realistic `n`?

* **How much work does each solution do?**

  * What is the Big-O?
  * How many operations for the expected `n`? (work load per items * item operations)
  * How often is the operation performed?

* **Could hardware change the result?**

  * Cache locality?
  * Memory layout?
  * Allocations?
  * Pointer chasing?
  * Other constant costs?

* **Do I need multiple data structures?**

  * Can one structure optimize iteration while another optimizes lookup?

* **Can I predict which is better?**

  * If the Big-O difference is huge → better scaling usually wins.
  * If Big-O is similar → cache, memory layout, and constant costs matter more.

* **After implementing:**

  * Profile / benchmark if performance matters.

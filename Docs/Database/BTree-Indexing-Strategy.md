# Architectural Strategy: Database Indexing Mechanics

### [THE BOTTLENECK]
As the application scales, searching through millions of rows via a "Table Scan" becomes catastrophic. However, blindly adding indexes to every column slows down `INSERT` and `UPDATE` operations, as the database must rewrite the index map every time data changes.

### [THE B-TREE SOLUTION]
Most SQL and NoSQL engines (like MongoDB) utilize B-Tree (Balanced Tree) algorithms for indexing. 
1. **O(log N) Time Complexity:** Instead of scanning from top to bottom, the engine navigates a tree structure, drastically reducing read times.
2. **The Strategic Trade-off:** * **Do Index:** Columns used frequently in `WHERE`, `JOIN`, or `ORDER BY` clauses (e.g., `user_id`, `email`, `order_status`).
   * **Do NOT Index:** Columns with low cardinality (e.g., a boolean `is_active` field) or large text fields rarely queried directly.

### [THE IMPLEMENTATION RULE]
In our MongoDB backend, compound indexes must follow the **ESR Rule (Equality, Sort, Range)** to prevent in-memory sorting crashes.
# Architectural Trade-offs: The CAP Theorem

### [THE ENGINEERING DILEMMA]
When scaling from a single monolithic application (like a local MERN stack) to a distributed system (like a high-traffic campus delivery platform), network partitions are inevitable. The **CAP Theorem** dictates that a distributed data store can only guarantee two out of the following three:

1. **Consistency (C):** Every read receives the most recent write or an error.
2. **Availability (A):** Every request receives a non-error response.
3. **Partition Tolerance (P):** The system continues to operate despite network failures between nodes.

### [THE STRATEGIC DECISION]
For the university canteen infrastructure, a network drop between the order tablet and the kitchen screen is highly probable. 
* We **MUST** choose Partition Tolerance (P).
* Between C and A, we prioritize **Availability (AP model)**. 

It is better for the system to accept an order (even if the kitchen screen syncs 5 seconds late) than for the entire app to crash and refuse to take orders during peak lunch rushes. We will handle minor data inconsistencies using eventual consistency workflows in Node.js.
Purpose:
This repository contains a complex C project that implements various data structures and algorithms. Its primary purpose is to serve as a comprehensive test case for AI-based C-to-Rust code conversion.

Key Components:

 - Data Structures: AVL Tree, Hash Table, Graph
 - Algorithms: Sorting (e.g., quicksort), Searching (binary and interpolation search)
 - Memory Management: Custom memory allocator
 - Utility Functions: String utilities

Why it's a good test for Rust conversion:

 - Complex Data Structures: Implementing self-referential structures like trees and graphs is challenging in Rust due to its ownership model.
 - Memory Management: The custom allocator tests Rust's ability to handle low-level memory operations safely.
 - Pointers and Unsafe Code: C's liberal use of pointers requires careful consideration in Rust, often needing unsafe blocks.
 - Ownership and Borrowing: Converting C's manual memory management to Rust's ownership system is non-trivial.
 - Idiomatic Patterns: Translating C idioms to idiomatic Rust code tests the AI's understanding of both languages.
 - Error Handling: Converting C's error codes to Rust's Result type requires careful analysis.


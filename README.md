# **Data-Structure-Performance-Analyzer**

## **Description**

A **C++** program for comparing the performance of various data structures — **Unordered/Ordered Array**, **Binary Search Tree (BST)**, **AVL Tree**, and **Hash Table**. It measures **search times** using real text data from files and generates performance statistics for **educational analysis**.

---

### 🔍 **Key Features**

* **Data Input & Processing**:

  * Reads words from a text file (`small-file.txt`).
  * Cleans input by removing non-alphabetic characters and converting to lowercase.

* **Data Structures Implemented**:

  * **UnorderedArray**: Simple unsorted array insertion.
  * **OrderedArray**: Sorted array using **QuickSort**.
  * **BinarySearchTree (BST)**: Classic binary search tree.
  * **AVLTree**: Self-balancing AVL tree.
  * **HashTable**: Hash table implementation.

* **Performance Measurement**:

  * Measures search times for random words using **`chrono`**.
  * Exports timing results to files (`Results.txt`, `UArray.txt`, etc.).

---

### ⚙️ **Technologies**

* **C++** (STL: `fstream`, `chrono`, dynamic memory management)
* **Algorithms**: QuickSort, BST/AVL operations, hashing
* **Custom Libraries**: User-defined implementations (`UnorderedArray.h`, `AVLTree.h`, etc.)

---

### 📝 **Notes**

* **Educational Purpose**: Ideal for studying the behavior and efficiency of data structures on real datasets.
* **Configuration Options**: Adjustable parameters such as `SIZE`, `PROBABILITY`, and `INPUT_FILE`.
* **Extensibility**: Can be expanded with new structures (e.g., **B-Tree**) or metrics (e.g., **memory usage**).

---

**🏷️ Tags**: `C++`, `Data Structures`, `Performance Analysis`, `Benchmarking`, `File Handling`
**🔧 Open for Contributions**: Open to improvements via *Pull Requests* or *Issues*.

---

*"A performance analysis tool for data structures, focusing on real-world application and comparative study."* ⏱️📈

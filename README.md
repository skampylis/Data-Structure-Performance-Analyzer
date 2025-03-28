# **Data-Structure-Performance-Analyzer**

## **Περιγραφή**
Πρόγραμμα σε **C++** για σύγκριση απόδοσης δομών δεδομένων (Μη ταξινομημένος/ταξινομημένος πίνακας, Δυαδικό Δέντρο Αναζήτησης, AVL Tree, Πίνακας Κατακερματισμού). Μετράει χρόνους αναζήτησης σε πραγματικά δεδομένα από αρχεία κειμένου και εξάγει στατιστικά για εκπαιδευτική ανάλυση.

---

### 🔍 **Κύρια Χαρακτηριστικά**
- **Εισαγωγή & Επεξεργαία Δεδομένων**:
  - Ανάγνωση λέξεων από αρχείο κειμένου (`small-file.txt`).
  - Καθαρισμός λέξεων (αφαίρεση μη αλφαβητικών χαρακτήρων, μετατροπή σε πεζά).
- **Δομές Δεδομένων**:
  - **UnorderedArray**: Απλή εισαγωγή χωρίς ταξινόμηση.
  - **OrderedArray**: Ταξινομημένος πίνακας με QuickSort.
  - **BinarySearchTree**: Δυαδικό Δέντρο Αναζήτησης.
  - **AVLTree**: Ισορροπημένο δέντρο AVL.
  - **HashTable**: Πίνακας κατακερματισμού.
- **Μέτρηση Απόδοσης**:
  - Χρονομέτρηση αναζήτησης τυχαίων λέξεων (χρήση `chrono`).
  - Αποθήκευση αποτελεσμάτων σε αρχεία (`Results.txt`, `UArray.txt`, κ.λπ.).

---

### ⚙️ **Τεχνολογίες**
- **C++** (STL: `fstream`, `chrono`, δυναμική διαχείριση μνήμης).
- **Αλγόριθμοι**: QuickSort, BST/AVL operations, κατακερματισμός.
- **Βιβλιοθήκες**: Προσαρμοσμένες υλοποιήσεις δομών (`UnorderedArray.h`, `AVLTree.h`, κ.λπ.).

---

### 📝 **Σημειώσεις**
- **Εκπαιδευτικό Πλαίσιο**: Ιδανικό για μελέτη συμπεριφοράς δομών δεδομένων υπό πραγματικά δεδομένα.
- **Ρυθμίσεις**: Προσαρμογή μεγέθους δοκιμών (`SIZE`), πιθανότητας εισαγωγής (`PROBABILITY`), και αρχείου εισόδου (`INPUT_FILE`).
- **Επεκτασιμότητα**: Προσθήκη νέων δομών (π.χ. B-Tree) ή μετρικών (π.χ. μνήμη).

---

**🏷️ Tags**: `C++`, `Data Structures`, `Performance Analysis`, `Benchmarking`, `File Handling`
**🔧 Open for Contributions**: Ανοικτό σε βελτιώσεις μέσω *Pull Requests* ή αναφοράς θεμάτων σε *Issues*.

*"Εργαλείο ανάλυσης απόδοσης δομών δεδομένων με έμφαση στην πραγματική εφαρμογή και τη συγκριτική μελέτη."* ⏱️📈

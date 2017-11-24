# Hopscotch Hashing
#### CSCE 3110 - Data Structures & Algorithms
###### Programming Assignment 02

___

**To compile:**
```
$ make
```

**To run:**
```
$ make run
```

**To clean up:**
```
$ make clean
```

___

You will implement an efficient hopscotch hash table using C++ that improves on the classic linear probing algorithm. 
Specifically, you will use a TABLE_SIZE = 17 and use the single hash function h(x) = x mod TABLE_SIZE. 
You shall resolve collisions using linear probing where the maximal length of the probe sequence (i.e., distance away 
from the original hash location) is bound by the hopscotch hashing algorithm where MAX_DIST = 4.

**Program Menu :**

```
HOPSCOTCH HASHING MENU:
+------------------------+
|    1 - Insert Value    |
|    2 - Delete Value    |
|    3 - Search Value    |
|    4 - Output Table    |
|    5 - Exit Program    |
+------------------------+
```

**Overview:**

`1 - Insert Value` inserts a value into the hopscotch hash table. If necessary, values will be rearranged. If rearranging is not successful, an error will be displayed.

`2 - Delete Value` deletes a value and clears its corresponding key within the table.

`3 - Search Value` searches for a given value and returns its corresponding key within the table.

`4 - Output Table` prints the current hash table.

`5 - Exit Program` exits the running program.
# Phone list compression using front compression:
## Introduction:
the front compression algorithm is used to compress a phone list.
## Algorithms:
if we look to the file structure we find that all the available characters are:

**from _0_ to _9_, from _a_ to _z_, from _A_ to _Z_ and space _' '_**.

all the characters are **63**, so we can use **6 bits** instead of **8 bits** for all characters.

we map every character to number between **_0_ and _62_**:

**_0-9_ => _0-9_, _a-z_ => _10-35_, _A-Z_ => _36-61_, _space_ => _62_**

one combination will remain unused.

we will use it as flag to indicate that next number is the number produced by front compression algorithm and it is not a character.

**FLAG = _63_**

### Front compression algorithm:
front compression is compression algorithm whereby common prefixes or suffixes and their lengths are recorded so that they need not be duplicated.

This algorithm is particularly well-suited for compressing _sorted data_.

[front compression wikipedia](https://en.wikipedia.org/wiki/Incremental_encoding)
## Sample:
### Input:
| Ahmed | 160 |
|----|----|
| Ahmed Ataia | 30210100394233 |
| Loay Nour | 31202042087902 |
| Loay Nour | 31606022320084 |

#### Compressed:
36 17 22 14 13 62 1 6 0

63 5 62 36 29 10 18 10 62 3 0 2 1 0 1 0 0 3 9 4 2 3 3

47 24 10 34 62 49 24 30 27 62 3 1 2 0 2 0 4 2 0 8 7 9 0 2

63 9 62 3 1 6 0 6 0 2 2 3 2 0 0 8 4
## Conclusion:
**Firstly:** 

every character is encoded in _6 bit_ instead of _8 bits_.

**Secondly:**

_front compression_ algorithm is used to compress the data.

**Compression ratio:**

bit level compression ratio:

**_6 / 8  = 0.6455696202531646_**

characters compression ratio:

The program was run on file with 632 characters and the compressed file was 544 characters.

**_544 / 632 = 0.8607594936708861_**
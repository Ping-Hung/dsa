# Bit-Hacking Concepts (Programmer's perspective)
## Operators
+ Use them to modify the **binary patterns** stored in some memory address.
+ Composed of basic binary operations

    |operator name|operator type|
    |:---:|:---:|
    |OR  (\|)|binary operator|
    |AND (&)|binary operator|
    |XOR (^)|binary operator|
    |NOT (~)|unary  operator|
    |shifts (<< or >>) | binary operator|

## Binary Patterns
- varies in length, which is measured in bytes (groups of 8 bits).
    - e.g. `char` is 1 byte long, `int` is 4 bytes long on my machine.
- signed number v.s. unsigned number
    - Assume they both are `n + 1` bits long

    |signed number | unsigned number|
    |:---:|:---:|
    |represents integer | represents naturals|
    |range = [-2^n, 2^n - 1] | range = [0, 2^(n + 1) - 1]|

- floating point (usually encoded in IEEE 754) v.s. fix point
     
# Common Tricks
- Masking: intentionally cover up a portion of an entire pattern.  

```c
    unsigned mask = 1U; // or 3, 7, 15, ..., depending on the width of the preserving bit-group
    unsigned offset = lsb_of_interest - 0; // number of bits the lsb of the preserving bit-group is away from bit-0
    unsigned new_pattern = pattern & (mask << (mask_width * offset));
```  
- Looking at raw pattern (stored in an address), then (optionally) reinterpret its type.
    - Can see this type of trick in John Carmack's famous fast inverse square root code.  

```c
    /* 
     *  This "dereferencing casted address" trick preserves the bit pattern 
     *   of the operand and returns a 
     * 	"direct translation" of that bit pattern as the type specified. 
     *  e.g. 0xff << 23 --> *(float *)& --> bit pattern 0xff << 23 treated as a float.
     */
    unsigned int pattern = (0xff << 23) | 1;
    float d = *(float *)&pattern;
```  
- Toggle: change a bit-field (or a group of bit-fields) from 0 to 1 and vice versa
    - Done with XOR (let x be a 1b long boolean variable, x ^ 1 = ~x holds)  

```c
    for (char *a_c = buffer; *a_c != '\0'; a_c++) {
        // for ascii characters, toggle the 5th bit (equiv. to +/- 32) to switch cases
        if ((*a_c >= 'a' && *a_c <= 'Z') || (*a_c >= 'A' && *a_c <= 'Z')) {
            *a_c = (*a_c) ^ (1 << 5);
        }
    }
```  
- Set/unset bit(s)  

```c
    unsigned x |= 1; // turn on (set) the 0th bit in x
```

```c
    unsigned x &= ~1; // turn off (unset) the 0th bit in x
```  

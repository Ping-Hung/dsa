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

## Binary Patterns (Encoding)
- varies in length, which is measured in bytes (groups of 8 bits).
    - e.g. `char` is 1 byte long, `int` is 4 bytes long on my machine.
- signed number v.s. unsigned number
    - Assume they both are `n` bits long

    |signed number | unsigned number|
    |:---:|:---:|
    |represents integer | represents naturals|
    |range = [-2^(n - 1), 2^(n - 1) - 1] | range = [0, 2^n - 1]|

- floating point (usually encoded in IEEE 754) v.s. fix point
     
# (Some) Common Tricks, A Growing List
1. <mark>**Masking**</mark>: intentionally cover up a portion of an entire pattern.  

```c
    unsigned mask = (1U << width) - 1; // 1, 3, 7, ... 2^width - 1
    unsigned offset = lsb_of_mask_subject - 0; // distance between bit 0 and
                                               // lsb of the bit-group that's
                                               // intended to be masked
    unsigned new_pattern = pattern & ~(mask <<  offset);
```  
2. <mark>**Looking at raw pattern**</mark> (stored in an address), then (optionally) reinterpret its type.
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
3. <mark>**Toggle**</mark>: change a bit-field (or a group of bit-fields) from 0 to 1 or 1 to 0.
    - Done with XOR (let x be a 1b long boolean variable, x ^ 1 = ~x holds)  

```c
    for (char *a_c = buffer; *a_c != '\0'; a_c++) {
        // for ascii characters, toggle the 5th bit (equiv. to +/- 32) to switch
        // cases
        if ((*a_c >= 'a' && *a_c <= 'z') || (*a_c >= 'A' && *a_c <= 'Z')) {
            *a_c ^= (1 << 5);
        }
    }
```  
4. <mark>**Set/unset bit(s)**</mark>
    - use with shifting to set/unset bit(s) at specified location.
```c
    unsigned x |= 1; // turn on (set) the 0th bit in x
```

```c
    unsigned x &= ~1; // turn off (unset) the 0th bit in x
```  
5. <mark>**Zero out**</mark> (more common in assembly)
    - if x is a boolean variable, by definition of XOR operator, x XOR x = 0.

```x86
    xor eax, eax
```

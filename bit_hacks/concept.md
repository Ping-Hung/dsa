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
    - **Caution:** This trick might cause memory issue when the cast converts a smaller type to a larger type.
    - It is in general safer to use a `union` to reinterpret a single bit
      pattern to different data types (a.k.a type punning trick).

```c
    /* 
     *  This "dereferencing/accessing casted address" trick preserves the bit pattern 
     *   of the operand and returns a  "direct translation" of that bit pattern
     *   as the type specified. 
     * 	    - **Caution**: this trick is an undefined behavior (UB) by C
     * 	      standards, and is generally safer to use a union for multiple
     * 	      interpretation of a single bit pattern.
     *  e.g. 0xff << 23 --> *(float *)& --> bit pattern 0xff << 23 treated as a float.
     */
    unsigned int pattern = (0xff << 23) | 1;
    float d = *(float *)&pattern;

    /**
     *      The Union trick (a.k.a type punning)
     * Usual format: 
     *  union {
     *      type1 as_type1;
     *      type2 as_type2;
     *      ...
     *  } u_var = {...};
     */

    union {
        float as_float;
        unsigned as_uint;
    } u_var = {.as_uint = pattern};

    printf("\nUsing the union trick\n");
    printf("float interpretation: %.3f\n"
           "unsigned interpretation: %u\n",
           u_var.as_float,
           u_var.as_uint);
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

6. <mark>**Count Down with `unsigned`**</mark>
    - Usual (intuitive, no binary system knowledge) way can lead to infinite loop, which stems from counter variable `i` overflows.
    - Makes use of modular arithmetic properties to prevent this issue.
    - Can use some examples to verify.
```c
    unsigned count = BIG_NUM;
    /* usual infinite loop + overflow count down */
    for (unsigned i = count; i >=0; i--) {
        /* loop body */
    }

    /* "correct" way to count down that considers modular arithmetic (wrapping around) */
    for (unsigned i = count; i < count; i--) {
        /* loop body */
    }
```
    - Even better way: (use `size_t` instead of `unsigned`)
        - `int` or `unsigned` only garauntees valid representation of $[-2^15, 2^15 - 1]$ (union of signed and unsigned)
            - This is not neccessarily the **width of a word** (modern machines are 32 bits)
        - `size_t` is garaunteed to be **word** size wide and `unsigned`, can represent $[0, 2^31 - 1]$ values.

7. <mark>**Multiplying $2^k$ by Left Shifts**</mark>
    - Goal: after shift, $x$ becomes $x \times 2^k$
    - Assume a width of $w$.
    - Left shifts: keep the width of the first operand ($w$), shift all bits to the left by $k$ (second operand).
        - Bit $w$ to $w + k$ were discarded.
        - Lower $k$ bits are filled with $0$'s.
    - After shift, all (remaining, non-discarded) bits are $2^k$ larger than their original values.
        - Analogy: in decimal systems, $010 = 001 \times 10$; $100 = 001 \times 100$. Binary systems follow the exact same rule.
```c
    int x = CONSTANT;
    x <<= k;    /* equals to x * 2^k */
```

8. <mark> **Dividing $2^k$ by Right Shifts** </mark>
    - Goal: after shift $x$ becomes $\lfloor x \div 2^k \rfloor$
    - Assume a width of $w$.
    - Right shifts: keep the width of the first operand ($w$), shift all bits to the right by $k$ (second operand).
        - *Arithmetic right shift*: duplicate the sign-bit to the upper $k$ bits of the result.
            - Preseves signedness of the first operand.
        - *Logical right shift*: simply fill-in the upper $k$ bits of the result.
    - After shift, all (remaining, non-discarded) bits are $2^k$ smaller than their original values.
        - Analogy: in decimal systems, $001 = 010 \div 10$; $001 = 100 \div 100$. Binary systems follow the exact same rule.
```c
    /* Unsigned: easier version, no extra modification needed.*/
    unsigned x = CONSTANT;
    x >>= k;    /* equals to floor(x / 2^k) */

    /* Signed: a little more complicated, need some more stuff in addition to arithmetic right shifts 
     * to achieve Goal.
     */
     int x = SIGNED_CONSTANT;
     x = (x + ((1 << k) - 1)) >> k; /* equals to floor(x / 2^k);
```

- **Notes on Signed Right Shifts**
- when $x < 0$, `x >>= k` $neq \lfloor x \div 2^k \rfloor$
- round towards $- \infty$
- `x = (x + ((1 << k) - 1)) >> k;` $= \lfloor x \div 2^k \rfloor$
    - `(x + ((1 << k) - 1))` adds `0b1...1` (k-bit of one's) to `x`
    - This "rounds up" the upper $w - k$ bits of `x` before the shift.
    - When the shift happens, rounding is not towards $- \infty$.
    - equivalent to $x = \lfloor (x + 2^k - 1) / 2^k \rfloor$. 


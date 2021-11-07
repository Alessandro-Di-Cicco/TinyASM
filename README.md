# TinyASM
Tiny ASM is a software capable of running Assembly programs written using a custom instruction set.
An instruction has the form `INSTRUCTION OP1, .., OPN [#COMMENT]`,
where `[#comment]` represents an optional comment that follows the instruction. 
Some examples of instructions are:

`ADD R1, R2, R3 #R1 <- R2 + R3`

`BLE R0, R4, 7 # if(R0 <= R4) goto 7`
## Structure of the machine
The memory of the program is made of eight registers, `R0`-`R7`, which can contain integer values: these registers are actually of type `int`, which makes their size implementation-dependant. All registers are initialized to `0`.
Immediates are positive integer literals, without the `+` sign.
The software is case-sensitive, so all instructions have to be written in uppercase character.
## Instructions
This language has a small amount of instructions, often requiring some "workarounds" to perform some actions (one example is that negative immediates are unsupported and as such negative values have to be "built" using subtraction).
In the following sections, registers are represented using the names `Rx`,`Ry` and `Rz`. When the name of a register is surrounded by curly brackets, it means value reading (e.g.: `{Rx}` means "the value contained in `Rx`).
Immediates will be indicated with the letter `n`, representing a generic non-negative integer.
Addresses will be indicated with the word `addr`. An address is a number indicating the instruction's, zero-based index (e.g.: the fourth instruction of a program will have index `3`, the fifth will have index `4` and so on). Blank lines in the source program are not counted (e.g.: the second instruction of a program will always have index `1` even when preceded by many blank lines)
### Setting instructions
- `SET Rx, n`: stores the immediate inside the given register [`{Rx} = n`]
- `CPY Rx, Ry`: copies the contents of the `Ry` register into the `Rx` register [`{Rx} = {Ry}`]

### Arithmetic instructions
 - `ADD Rx, Ry, Rz`: sums the contents of the registers `Ry` and `Rz` , storing the result in `Rx` [`{Rx} = {Ry} + {Rz}`]
 - `SUB Rx, Ry, Rz`: subtracts the content of `Rz` from the content of `Ry` , storing the result in `Rx` [`{Rx} = {Ry} - {Rz}`]
 - `MUL Rx, Ry, Rz`: multiplies the content of `Ry` with the content of `Rz` , storing the result in `Rx` [`{Rx} = {Ry} * {Rz}`]
 - `DIV Rx, Ry, Rz`: divides the content of `Rz` by the content of `Ry` , storing the result in `Rx` [`{Rx} = {Ry} / {Rz}`]
 - `MOD Rx, Ry, Rz`: divides the content of `Rz` by the content of `Ry` , storing the remainder of the division in `Rx` [`{Rx} = {Ry} % {Rz}`]
All the instructions listed above have their "immediate" equivalent, which is distinguished by its "register" counterpart by the `I` at the end of the instruction. For example, the immediate equivalent of `ADD` is:
`ADDI Rx, Ry, n`

### Branching instructions
- `BEQ Rx, Ry, addr`: jumps to the given address if the value in `Rx` is equal to the value in `Ry` [`if ({Rx} == {Ry}) goto addr`]
- `BNE Rx, Ry, addr`: jumps to the given address if the value in `Rx` is not equal to the value in `Ry` [`if ({Rx} != {Ry}) goto addr`]
- `BGT Rx, Ry, addr`: jumps to the given address if the value in `Rx` is greater than the value in `Ry` [`if ({Rx} > {Ry}) goto addr`]
- `BGE Rx, Ry, addr`: jumps to the given address if the value in `Rx` is greater than or equal to the value in `Ry` [`if ({Rx} >= {Ry}) goto addr`]
- `BLT Rx, Ry, addr`: jumps to the given address if the value in `Rx` is lower than the value in `Ry` [`if ({Rx} < {Ry}) goto addr`]
- `BLE Rx, Ry, addr`: jumps to the given address if the value in `Rx` is lower than or equal the value in `Ry` [`if ({Rx} < {Ry}) goto addr`]
- `BRA addr`: jumps to the given address, unconditionally [`goto addr`]

### Conditional instructions
- `SEQ Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is equal to the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} == {Rz}`] 
- `SNQ Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is not equal to the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} != {Rz}`] 
- `SGT Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is greater than the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} > {Rz}`] 
- `SGE Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is greater than or equal to the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} > {Rz}`] 
- `SLT Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is lower than the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} < {Rz}`] 
- `SLE Rx, Ry, Rz`: sets the value of `Rx` to `1` if the value in `Ry` is lower than or equal to the value in `Rz`, otherwise sets it to `0` [`{Rx} = {Ry} <= {Rz}`] 

### Logic instructions
- `AND Rx, Ry, Rz`: performs the bitwise AND between the contents of `Ra` and `Rb`, storing the resulting value in `Rc` [`{Rc} = {Ra} & {Rb}`]
- `OR Rx, Ry, Rz`: performs the bitwise OR between the contents of `Ra` and `Rb`, storing the resulting value in `Rc` [`{Rc} = {Ra} | {Rb}`]
- `NOT Rx, Ry`: performs one's complement of the value stored in `Ry` storing the resulting value in `Rx` [`{Rx} = ~{Ry}`]

### Misc instructions
- `PRINT Ry`: prints the contents of the given register in the terminal, with the given format `"Ry = {Ry}"`

## Examples
There are two examples in the "Examples" folder:
- `sumOfFirstNumbers.tsm` computes the sum of the first `n` numbers, such value can be set by changing the value stored in the `R0` at line `1`
- `primes.tsm` computes the primes number up to a given maximum, which can be set by changing the value stored in `R0` at line `1`

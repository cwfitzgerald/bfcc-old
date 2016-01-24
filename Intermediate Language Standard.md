This is the desciption of bfcc's intermediate language.

Each token has three fields:
type  - Number indicating command type
data  - First data field (always used)
data2 - Second data field (sometimes used)

We will use DPTR to refer to the current data pointer.

Offset refers to the difference between the accessed cell, and the current data pointer. Ex: an add with a DPTR of 2 and an offset of -1 would write to cell #1

Short descriptions of all commands with full names:
00: NOP     (No Operation)     Does absolutely nothing.
01: ADD     (Add)              Adds $DATA to value with offset $DATA2
02: MV      (Move)             Moves the data pointer $DATA spaces
03: PRINT   (Print to output)  Prints the value $DATA times at offset $DATA2
04: FPRNT   (Print until 0)    Moves $DATA, prints the value of the cell, moves $DATA2, and continues if the value of current cell is 0
05: GET     (Read from input)  Reads one byte from stdin to offset $DATA 
06: LBK     (Left bracket)     If current cell is zero jump to instruction after matching RBK, else continue
07: RBK     (Right bracket)    If current cell isn't zero jump to matching LBK, else continue
08: CLR     (Clear)            Zero cell at offset $DATA
09: FIND    (Find a Zero)      Move $DATA until current cell is equal to zero
10: CP      (Copy cell)        Copy current cell to cell $DATA away
11: MUL     (Multiply cell)    Multiply current cell by $DATA2 and put in cell $DATA away.
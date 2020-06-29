* Standard prelude:
  0:     LD  6,0(0) 	load maxaddress from location 0
  1:     ST  0,0(0) 	clear location 0
* End of standard prelude.
* -> assign
  2:     ST  0,0(5) 	assign: store value
* <- assign
* -> repeat
* repeat: jump after body comes back here
  3:     IN  0,0,0 	read integer value
  4:     ST  0,0(5) 	read: store value
* -> Op
* -> Id
  5:     LD  0,0(5) 	load id value
* <- Id
  6:     ST  0,0(6) 	op: push left
  7:     LD  1,0(6) 	op: load left
  8:    SUB  0,1,0 	op ==
  9:    JEQ  0,2(7) 	br if true
 10:    LDC  0,0(0) 	false case
 11:    LDA  7,1(7) 	unconditional jmp
 12:    LDC  0,1(0) 	true case
* <- Op
 13:    JEQ  0,-11(7) 	repeat: jmp back to body
* <- repeat
* -> if
* -> Op
* -> Id
 14:     LD  0,1(5) 	load id value
* <- Id
 15:     ST  0,0(6) 	op: push left
 16:     LD  1,0(6) 	op: load left
 17:    SUB  0,1,0 	op ==
 18:    JEQ  0,2(7) 	br if true
 19:    LDC  0,0(0) 	false case
 20:    LDA  7,1(7) 	unconditional jmp
 21:    LDC  0,1(0) 	true case
* <- Op
* if: jump to else belongs here
 23:     IN  0,0,0 	read integer value
 24:     ST  0,1(5) 	read: store value
* if: jump to end belongs here
 22:    JEQ  0,3(7) 	if: jmp to else
 25:    LDA  7,0(7) 	jmp to end
* <- if
* End of execution.
 26:   HALT  0,0,0 	

* Standard prelude:
  0:     LD  6,0(0) 	load maxaddress from location 0
  1:     ST  0,0(0) 	clear location 0
* End of standard prelude.
* -> assign
* -> Const
  2:    LDC  0,1(0) 	load const
* <- Const
  3:     ST  0,0(5) 	assign: store value
* <- assign
* -> if
* -> Op
* -> Id
  4:     LD  0,1(5) 	load id value
* <- Id
  5:     ST  0,0(6) 	op: push left
* -> Const
  6:    LDC  0,1(0) 	load const
* <- Const
  7:     LD  1,0(6) 	op: load left
  8:    SUB  0,1,0 	op ==
  9:    JEQ  0,2(7) 	br if true
 10:    LDC  0,0(0) 	false case
 11:    LDA  7,1(7) 	unconditional jmp
 12:    LDC  0,1(0) 	true case
* <- Op
* if: jump to else belongs here
 14:     IN  0,0,0 	read integer value
 15:     ST  0,1(5) 	read: store value
* if: jump to end belongs here
 13:    JEQ  0,3(7) 	if: jmp to else
* -> assign
* -> Const
 17:    LDC  0,3(0) 	load const
* <- Const
 18:     ST  0,0(5) 	assign: store value
* <- assign
 16:    LDA  7,2(7) 	jmp to end
* <- if
* -> repeat
* repeat: jump after body comes back here
 19:     IN  0,0,0 	read integer value
 20:     ST  0,0(5) 	read: store value
* -> Op
* -> Id
 21:     LD  0,0(5) 	load id value
* <- Id
 22:     ST  0,0(6) 	op: push left
* -> Const
 23:    LDC  0,1(0) 	load const
* <- Const
 24:     LD  1,0(6) 	op: load left
 25:    SUB  0,1,0 	op ==
 26:    JEQ  0,2(7) 	br if true
 27:    LDC  0,0(0) 	false case
 28:    LDA  7,1(7) 	unconditional jmp
 29:    LDC  0,1(0) 	true case
* <- Op
 30:    JEQ  0,-12(7) 	repeat: jmp back to body
* <- repeat
* End of execution.
 31:   HALT  0,0,0 	

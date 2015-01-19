;Program: test1
start:
		 sub.i  24 , #1 , 28 		; binary operator 0, 1,$t1
	 mov.i  28 , 4 		; mov $t1 n
	 write.i  4 		; write n
		 mul.i  #3 , #4 , 32 		; binary operator 3, 4,$t2
		 add.i  #2 , 32 , 36 		; binary operator 2, $t2,$t3
		 mul.i  #1 , 36 , 40 		; binary operator 1, $t3,$t4
		 add.i  40 , #5 , 44 		; binary operator $t4, 5,$t5
	 mov.i  44 , 0 		; mov $t5 i
	 write.i  0 		; write i
	 exit

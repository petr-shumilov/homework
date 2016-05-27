; 104743
ldc 10001
st 0
ldc 1
st 5 
ldc 2 
st 1 
simple: ldc 1
ld 1
sub 
st 2
ld 1
st 3
check_div: ldc 1
ld 2
cmp 
br is_devided 
ld 0 
ld 5 
cmp  
br next_simple 
ld 1
ret
cancel: ld 2
ld 3
sub
st 3 
is_devided: ld 2 
ld 3 
cmp 
st 4 
ld 4
br bad 
jmp next_num
next_simple: ld 5
ldc 1
add
st 5     
next_num: ld 1
ldc 1
add
st 1 
jmp simple
bad: ldc -1
ld 4
cmp 
br cancel 
ld 1
st 3
ldc 1
ld 2
sub
st 2 
jmp check_div
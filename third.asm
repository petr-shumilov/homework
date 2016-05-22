;1471 
ldc 2
st 4
ldc 208574561
st 7
ldc 15000
st 9
ldc 0
st 6
func: ldc 1
st 0
ldc 0
st 5
mod: ld 4
st 1
ldc 0
st 3
mark: ldc -1
ld 0
ld 1
cmp
add
ldc 1
add
ldc 0
cmp
ldc -1
cmp
br res
ld 0
ld 1
sub
st 1
jmp mark
res: ld 1
st 3
ld 3
ld 0
cmp
br q
ld 5
ldc 1
add
st 5
q: ld 0
ldc 1
add
st 0
ld 0
ld 4
cmp
br mod
ld 5
ldc 1
cmp
ld 4
ldc 1
add
st 4
ld 4
ld 9
cmp
ldc -1
cmp
ldc 1
add
br rk
br func 
ld 7
st 1
ld 4
ldc -1
add
st 0
ldc 0
st 3
markn: ldc -1
ld 0
ld 1
cmp
add
ldc 1
add
ldc 0
cmp
ldc -1
cmp
br resn
ld 0
ld 1
sub
st 1
jmp markn
resn: ld 1
st 3
ld 3
ld 0
cmp
br func
ld 4
ldc -1
add
st 8
jmp func
rk: st 0
ld 8
ret
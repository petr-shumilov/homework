def size[Type](lst : List[Type]) : Int = {
  if (lst.isEmpty) {
    0
  }
  else{
    1 + size(lst.tail)
  }
}
var a : List[Int] = List(1,2,3)
size(a)

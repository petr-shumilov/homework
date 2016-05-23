def sum_of(lst : List[Int]) : Int = {
  if (lst.isEmpty){
    0
  }
  else{
    lst.head + sum_of(lst.tail)
  }
}
var a : List[Int] = List(1,2,3)
sum_of(a)

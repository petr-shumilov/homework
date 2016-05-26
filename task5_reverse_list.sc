def reverse_list[Type](lst : List[Type], res : List[Type]) : List[Type] = {
  if (lst.isEmpty)
    res
  else
    reverse_list(lst.tail, lst.head :: res)
}
val a : List[Int] = List(1,2, 3, 4)
val b : List[Int] = List()
reverse_list(a, b)
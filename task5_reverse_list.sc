def reverse_list[Type](lst: List[Type]): List[Type] = {
  if (lst.tail == Nil)
    List(lst.head)
  else
    reverse_list(lst.tail) ++ List(lst.head)
}
val a : List[Int] = List(1,2, 3, 4)
reverse_list(a)
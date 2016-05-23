def push_back[Type](lst : List[Type], element : Type) : List[Type] = {
  if (lst.isEmpty)
    List(element)
  else
    lst.head :: push_back(lst.tail, element)
}
var a : List[Int] = List(1,2,3)
push_back(a, 4)

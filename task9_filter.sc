def list_filter_by[Type](lst: List[Type], func: Type => Boolean): List[Type] = {//10
  if (lst.isEmpty)
    List()
  else {
    if (func(lst.head))
      lst.head :: list_filter_by(lst.tail, func)
    else
      list_filter_by(lst.tail, func)
  }
}

def list_filter(list: List[Int]): List[Int] = {//9
  list_filter_by(list, (x: Int) => x % 2 == 0)
}

var a : List[Int] = List(1,2,3,1,2,1)
list_filter(a)
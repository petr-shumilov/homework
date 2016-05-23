def list_filter[Type](lst: List[Type], filter: Type) : List[Type] = {
  if (lst.isEmpty){
    List()
  }
  else {
    if (lst.head == filter){
      List(filter) ++ list_filter(lst.tail, filter)
    } else {
      list_filter(lst.tail, filter)
    }
  }
}
var a : List[Int] = List(1,2,3,1,2,1)
list_filter(a, 2)
def comp(x: Int) : Boolean = {
  if ((x >= 0) && (x <= 5)) true else false
}

def list_filter_by[A](lst: List[A], filter : (A) => Boolean): List[A] = {
  if (lst.isEmpty){
    List()
  } else {
    if (filter(lst.head)){
      List(lst.head) ++ list_filter_by(lst.tail, filter)
    } else {
      list_filter_by(lst.tail, filter)
    }
  }
}
var a : List[Int] = List(1,6,3,-1,2,7)
list_filter_by(a, comp)
def sum_of(lst : List[Int]) : Int = {
  def loop(lst: List[Int], res: Int): Int = {
    if (lst.isEmpty)
      res
    else
      loop(lst.tail, res + lst.head)
  }
  loop(lst, 0)
}
val a : List[Int] = List(1,2, 3, 4)
sum_of(a)
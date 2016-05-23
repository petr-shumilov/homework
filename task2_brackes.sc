def check_brackes(list: List[Char]): Boolean = {
  var balance = 0
  var _list = list
  while (_list.nonEmpty){
    if (_list.head == '('){
      balance += 1
    } else {
      balance -= 1
    }
    _list = _list.tail
  }
  if (balance != 0) false else true
}
val a : List[Char] = List('(',')', '(', ')')
check_brackes(a)
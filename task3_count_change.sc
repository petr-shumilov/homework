def countChange(money: Int, coins: List[Int]): Int = {
  if ((coins.isEmpty) || (money < 0)){
    0
  }
  else if (money == 0){
    1
  }
  else {
    countChange(money, coins.init) + countChange(money - coins.last, coins)
  }
}

var coins : List[Int] = List(5, 10, 50)
var money = 400;
countChange(money, coins)
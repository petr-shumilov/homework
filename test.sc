abstract class ParagraphElement {
  def length: Int
}


class Word(S: String) extends ParagraphElement{
  var word = S
  override def toString: String = S
  def length = word.length()
}

class Space(k: Int) extends ParagraphElement{
  var x = k
  def length = x
  override def toString: String = "Space(" + x + ")"
}

class TypeOfAlignment(S: String) {
  val Type = S
  def NumOfAlignment = {
    Type match {
      case "Center" => 0
      case "Left" => -1
      case "Right" => 1
      case "Justify" => 2
      case default => 0
    }
  }
}

// Adding elem to tail of list
def AddAtTheEnd[A](InputList: List[A], Element: A): List[A] = InputList ::: List(Element)

// number new line words
def NumOfWordsOfNewLine(InputList: List[Word], Width: Int): Int = {

  var NumOfSymbols = InputList.head.length
  var CurWord = 1
  var IDontKnowHowToUseBreak = 0
  while ((CurWord <= InputList.length - 1) && (IDontKnowHowToUseBreak == 0)) {
    if (((NumOfSymbols + InputList.apply(CurWord).length + 1) <= Width)) {
      NumOfSymbols += InputList.apply(CurWord).length + 1
      CurWord += 1
    } else {
      IDontKnowHowToUseBreak = 1
    }
  }
  CurWord
}


def RemoveElementsFromBegining[A](InputList: List[A], N: Int): List[A] = {
  var ResList = InputList
  var i = 0
  for (i <- 0 to N-1) {
    ResList = ResList.tail
  }
  ResList
}

def TakeElementsFromBegining[A](InputList: List[A], N: Int): List[A] = {
  var i = 0
  var ResList: List[A] = List()
  for (i <- 0 to N-1) {
    ResList = AddAtTheEnd(ResList, InputList.apply(i))
  }
  ResList
}


// Main
def MakeText(InputListOfWords: List[Word], Width: Int, Alignment: TypeOfAlignment): List[List[ParagraphElement]] = {
  var ListOfWords = InputListOfWords
  var ResList: List[List[ParagraphElement]] = List()
  while (!ListOfWords.isEmpty) {
    ResList = ConstructLine(TakeElementsFromBegining(ListOfWords, NumOfWordsOfNewLine(ListOfWords, Width)), Width, Alignment) :: ResList
    ListOfWords = RemoveElementsFromBegining(ListOfWords, NumOfWordsOfNewLine(ListOfWords, Width))
  }
  ResList
}



def ConstructLine(InputList: List[Word], Width: Int, Alignment: TypeOfAlignment): List[ParagraphElement] = {
  val SumOfWordsLength: Int = {
    var i = 0
    var res = 0
    for (i <- 0 to InputList.length - 1) {
      res+= InputList.apply(i).length
    }
    res
  }

  def ConstructLineLeftAlignment: List[ParagraphElement] = {
    var ResList: List[ParagraphElement] = List(InputList.head)
    if (InputList.length > 1) {
      for (i <- 1 to InputList.length - 1) {
        ResList = AddAtTheEnd(ResList, new Space(1))
        ResList = AddAtTheEnd(ResList, InputList.apply(i))
      }
    }
    if (Width - (SumOfWordsLength + InputList.length - 1) > 0)
      AddAtTheEnd(ResList, new Space(Width - (SumOfWordsLength + InputList.length - 1)))
    else
      ResList
  }

  def ConstructLineRightAlignment: List[ParagraphElement] = {
    var ResList: List[ParagraphElement] = List(InputList.head)
    for (i <- 1 to InputList.length - 1) {
      ResList = AddAtTheEnd(ResList, new Space(1))
      ResList = AddAtTheEnd(ResList, InputList.apply(i))
    }
    new Space(Width - (SumOfWordsLength + InputList.length - 1)) :: ResList
  }

  def ConstructLineCenterAlignment: List[ParagraphElement] = {
    var ResList: List[ParagraphElement] = List(InputList.head)
    for (i <- 1 to InputList.length - 1) {
      ResList = AddAtTheEnd(ResList, new Space(1))
      ResList = AddAtTheEnd(ResList, InputList.apply(i))
    }
    if (((Width - (SumOfWordsLength + InputList.length - 1)) / 2) > 0)
      ResList = new Space(((Width - (SumOfWordsLength + InputList.length - 1)) / 2)) :: ResList
    if (((Width - (SumOfWordsLength + InputList.length - 1)) / 2) + ((Width - (SumOfWordsLength + InputList.length - 1)) % 2) > 0)
      ResList = AddAtTheEnd(ResList, new Space(((Width - (SumOfWordsLength + InputList.length - 1)) / 2) + ((Width - (SumOfWordsLength + InputList.length - 1)) % 2)))
    ResList
  }

  def ConstructLineJustifyAligment: List[ParagraphElement] = {
    var ResList: List[ParagraphElement] = List(InputList.head)
    val NumOfSpace = InputList.length - 1
    val SumOfSpace = Width - SumOfWordsLength
    for (i <- 1 to InputList.length * 2 - 2) {
      if (i % 2 == 0) {
        ResList = AddAtTheEnd(ResList, InputList.apply(i / 2))
      } else {
        if (i / 2 + 1 <= SumOfSpace % NumOfSpace) {
          ResList = AddAtTheEnd(ResList, new Space(SumOfSpace / NumOfSpace + 1))
        } else {
          ResList = AddAtTheEnd(ResList, new Space(SumOfSpace / NumOfSpace))
        }
      }
    }
    if (InputList.length == 1) {
      ResList = AddAtTheEnd(ResList, new Space(Width - InputList.head.length))
    }
    ResList
  }
  Alignment.NumOfAlignment match {
    case -1 => ConstructLineLeftAlignment
    case 1 => ConstructLineRightAlignment
    case 0 => ConstructLineCenterAlignment
    case 2 => ConstructLineJustifyAligment
    case default => {
      println("Undefined alignment")
      List()
    }
  }
}

// example
val TempList: List[Word] = List(new Word("Cat"), new Word("dog"), new Word("cow"), new Word("sheep"))
MakeText(TempList.reverse, 7, new TypeOfAlignment("Center"))
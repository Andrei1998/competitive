object Main {
    def printType[T](l: List[T]) {
       l match {
            case y: List[Boolean] => {
                println("List of Boolean")
            }
            case y: List[T] => {
                println("List of Something")
            }
            case y: List[Any] => {
                println("List of Any")
            }
            case y: Any => {
                println("Any")
            }
        }
    }

    def main(args: Array[String]) {
        val v = List[Any](1, 2.3, 3) // List of Boolean
        printType(v)
    }
}

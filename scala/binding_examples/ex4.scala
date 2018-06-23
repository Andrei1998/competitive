object Printer {
    def print(e: Int) {
        println("Have an Int: " + e)
    }
    def print(e: Any) = e match {
        case e: Int => {
            println("Have something else: " + e)
        }
        case e: Any => {
            println("Still have something else: " + e)
        }
    }
}

class Container(val elem: Any) {
    def show = Printer.print(elem)
}

object Main {
    def main(args: Array[String]) {
        val t = new Container(10) // Have something else: 10
        t.show 
    }
}

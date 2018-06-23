object Main extends App {
    trait Iter[T] {
        def hasNext: Boolean
        def next: T
        def copy: Iter[T]
    }

    class DropUntil[T](p: T => Boolean, iter: Iter[T]) extends Iter[T] {
        // seq = head ++ tail
        private var head: Option[T] = None
        private var tail: Iter[T]   = iter 
        
        // Pre: head = None
        private def acquire = {
            while (head == None && tail.hasNext) {
                head = Some(tail.next)
                if (!p(head.get))
                    head = None
            }
        }

        acquire
        
        // Public Interface
        def hasNext = (head != None)
        def next = {
            val ans = head.get
            head = None
            acquire
            ans
        }
        def copy: Iter[T] = new DropUntil[T](p, iter)
    }
}

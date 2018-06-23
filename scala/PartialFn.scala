object Main extends App {
    class PartialFn[T, U](val data: List[(T, U)]) {
        def get(x: T): Option[U] = {
            def crt(p: (T, U)) = p._1 == x
            val ans = data.filter(crt) 
            if (ans == List())
                None
            else
                Some(ans.head._2)
        }

        def add(x: T, y: U): PartialFn[T, U] = new PartialFn[T, U]((x, y) :: data)

        def remove(x: T): PartialFn[T, U] = {
            def crt(p: (T, U)) = p._1 != x
            val ans = data.filter(crt)
            new PartialFn[T, U](ans)
        }

        def compose[V](that: PartialFn[U, V]): PartialFn[T, V] = {
            var ans = List[(T, V)]()
            for (p1 <- this.data)
                for (p2 <- that.data)
                    if (p1._2 == p2._1)
                        ans = (p1._1, p2._2) :: ans
            new PartialFn[T, V](ans)
        }
    }
}

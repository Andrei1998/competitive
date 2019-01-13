-- Monadic add a b c = a + b + c
add1 :: Maybe Int -> Maybe Int -> Maybe Int -> Maybe Int
add1 a b c = a >>= (\x ->
             b >>= (\y ->
             c >>= (\z ->
             return (x + y + z))))

add2 :: Maybe Int -> Maybe Int -> Maybe Int -> Maybe Int             
add2 a b c =
    do x <- a
       y <- b
       z <- c
       return (x + y + z)
       
-- Monadic add a b c = [x + y + z | x <- a, y <- b, z <- c]
add3 :: [Int] -> [Int] -> [Int] -> [Int]
add3 a b c = a >>= (\x ->
             b >>= (\y ->
             c >>= (\z ->
             return (x + y + z))))
                     
add4 :: [Int] -> [Int] -> [Int] -> [Int]
add4 a b c =
    do x <- a
       y <- b
       z <- c
       return (x + y + z)
       
-- Notice how the first two and the last two are actually the same function, just with different types.
-- This shows how binding and return accomplish different tasks depending on the working monad.

-- Q: What would this code do for the IO monad?
-- A: The function would read 3 numbers and add them, wrapping the result into an IO:

add5 :: IO Int -> IO Int -> IO Int -> IO Int
add5 a b c =
    do x <- a
       y <- b
       z <- c
       return (x + y + z)

-- *Main> add5 readLn readLn readLn
-- 3
-- 10
-- 200
-- 213

-- Here's code that finds the sum of the odd elements of a read array

f = sum . (filter odd)

main = do
	inputdata <- getContents
	putStrLn $ show $ f $ map (read :: String -> Int) $ lines inputdata

-- Notice the usage of show, read and lines (non-monadic functions) together with
-- getContents and putStrLn (monadic functions)
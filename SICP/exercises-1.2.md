# 1.2 Procedures and the Processes They Generate

## Exercise 1.2.

Each of the following two procedures defines a method for adding two
positive integers in terms of the procedures `inc`, which increments its
argument by 1, and `dec`, which decrements its argument by 1.

    (define (+ a b)
      (if (= a 0)
          b
          (inc (+ (dec a) b))))
    
    (define (+ a b)
      (if (= a 0)
          b
          (+ (dec a) (inc b))))

Using the substitution model, illustrate the process generated by
each procedure in evaluating (+ 4 5). Are these processes iterative
or recursive?

## Exercise 1.10.

The following procedure computes a mathematical function called
Ackermann's function.

    (define (A x y)
      (cond ((= y 0) 0)
            ((= x 0) (* 2 y))
            ((= y 1) 2)
            (else (A (- x 1)
                     (A x (- y 1))))))

What are the values of the following expressions?

    > (A 1 10)

    > (A 2 4)

    > (A 3 3)

Consider the following procedures, where `A` is the procedure defined
above:

    (define (f n) (A 0 n))
    
    (define (g n) (A 1 n))
    
    (define (h n) (A 2 n))
    
    (define (k n) (* 5 n n))

Give concise mathematical definitions for the functions computed by the
procedures `f`, `g`, and `h` for positive integer values of `n`. For
example, `(k n)` computes 5n².

## Exercise 1.11.

A function f is defined by the rule that *f(n) = n if n<3 and f(n)
 = f(n - 1) + 2f(n - 2) + 3f(n - 3) if n≥3*.

Write a procedure that computes *f* by means of a recursive process.

Write a procedure that computes *f* by means of an iterative process.

## Exercise 1.12.

The following pattern of numbers is called *Pascal's triangle*.

        1
      1 2 1
     1 3 3 1
    1 4 6 4 1

The numbers at the edge of the triangle are all 1, and each number
inside the triangle is the sum of the two numbers above it. Write a
procedure that computes elements of Pascal's triangle by means of a
recursive process.

## Exercise 1.13.

Prove that *Fib(n)* is the closest integer to Φⁿ/5, where Φ = (1 + √5)/2.
Hint: Let Ψ = (1 - √5)/2. Use induction and the definition of the
Fibonacci numbers (see section 1.2.2) to prove that *Fib(n) = (Φⁿ - Ψⁿ)/√5*.

## Exercise 1.14.

Draw the tree illustrating the process generated by the `count-change`
procedure of section 1.2.2 in making change for 11 cents. What are the
orders of growth of the space and number of steps used by this process
as the amount to be changed increases?

## Exercise 1.15.

The sine of an angle (specified in radians) can be computed by making
use of the approximation sin x ≈ x if x is sufficiently small, and the
trigonometric identity

    sin x = 3 sin x/3 - 4 sin³ x/3

to reduce the size of the argument of sin. (For purposes of this
exercise an angle is considered "sufficiently small" if its magnitude
is not greater than 0.1 radians.) These ideas are incorporated in the
following procedures:

    (define (cube x) (* x x x))
    (define (p x) (- (* 3 x) (* 4 (cube x))))
    (define (sine angle)
       (if (not (> (abs angle) 0.1))
           angle
           (p (sine (/ angle 3.0)))))

* a. How many times is the procedure p applied when (sine 12.15) is
  evaluated?
* b. What is the order of growth in space and number of steps (as a
  function of a) used by the process generated by the sine procedure when
  `(sine a)` is evaluated?

## Exercise 1.16.

Design a procedure that evolves an iterative exponentiation process that
uses successive squaring and uses a logarithmic number of steps, as does
`fast-expt`. (Hint: Using the observation that (b^(n/2))² = (b²)^(n/2),
keep, along with the exponent *n* and the base *b*, an additional state
variable *a*, and define the state transformation in such a way that
the product *a bⁿ* is unchanged from state to state. At the beginning
of the process a is taken to be 1, and the answer is given by the value
of a at the end of the process. In general, the technique of defining
an *invariant quantity* that remains unchanged from state to state is
a powerful way to think about the design of iterative algorithms.)

## Exercise 1.17.

The exponentiation algorithms in this section are based on performing
exponentiation by means of repeated multiplication. In a similar way,
one can perform integer multiplication by means of repeated addition. The
following multiplication procedure (in which it is assumed that our
language can only add, not multiply) is analogous to the `expt` procedure:

    (define (* a b)
      (if (= b 0)
          0
          (+ a (* a (- b 1)))))

This algorithm takes a number of steps that is linear in `b`. Now suppose
we include, together with addition, operations `double`, which doubles an
integer, and `halve`, which divides an (even) integer by 2. Using these,
design a multiplication procedure analogous to fast-expt that uses a
logarithmic number of steps.

## Exercise 1.18.

Using the results of exercises 1.16 and 1.17, devise a procedure that
generates an iterative process for multiplying two integers in terms of
adding, doubling, and halving and uses a logarithmic number of steps.40

## Exercise 1.19.

There is a clever algorithm for computing the Fibonacci numbers in a
logarithmic number of steps. Recall the transformation of the state
variables a and b in the `fib-iter` process of section 1.2.2: a ← a +
b and b ← a. Call this transformation T, and observe that applying T
over and over again *n* times, starting with 1 and 0, produces the pair
Fib(n + 1) and Fib(n). In other words, the Fibonacci numbers are produced
by applying Tⁿ, the nth power of the transformation T, starting with
the pair (1,0). Now consider T to be the special case of *p* = 0 and
*q* = 1 in a family of transformations *Tpq*, where T*pq* transforms the pair
*(a,b)* according to *a ← bq + aq + ap* and *b ← bp + aq*. Show that if
we apply such a transformation *Tpq* twice, the effect is the same as
using a single transformation *Tp'q'* of the same form, and compute *p'*
and *q'* in terms of p and q. This gives us an explicit way to square these
transformations, and thus we can compute *Tⁿ* using successive squaring,
as in the `fast-expt` procedure. Put this all together to complete the
following procedure, which runs in a logarithmic number of steps:

    (define (fib n)
      (fib-iter 1 0 0 1 n))
    (define (fib-iter a b p q count)
      (cond ((= count 0) b)
            ((even? count)
             (fib-iter a
                       b
                       <??>      ; compute p'
                       <??>      ; compute q'
                       (/ count 2)))
            (else (fib-iter (+ (* b q) (* a q) (* a p))
                            (+ (* b p) (* a q))
                            p
                            q
                            (- count 1)))))

## Exercise 1.20.

The process that a procedure generates is of course dependent on the
rules used by the interpreter. As an example, consider the iterative
`gcd` procedure given above. Suppose we were to interpret this procedure
using normal-order evaluation, as discussed in section 1.1.5. (The
normal-order-evaluation rule for if is described in exercise 1.5.) Using
the substitution method (for normal order), illustrate the process
generated in evaluating `(gcd 206 40)` and indicate the `remainder`
operations that are actually performed. How many `remainder` operations are
actually performed in the normal-order evaluation of `(gcd 206 40)`? In
the applicative-order evaluation?

## Exercise 1.21.

Use the `smallest-divisor` procedure to find the smallest divisor of each
of the following numbers: 199, 1999, 19999.

## Exercise 1.22.

Most Lisp implementations include a primitive called `runtime` that returns
an integer that specifies the amount of time the system has been running
(measured, for example, in microseconds). The following `timed-prime-test`
procedure, when called with an integer *n*, prints *n* and checks to see if
*n* is prime. If *n* is prime, the procedure prints three asterisks followed
by the amount of time used in performing the test.

    (define (timed-prime-test n)
      (newline)
      (display n)
      (start-prime-test n (runtime)))
    (define (start-prime-test n start-time)
      (if (prime? n)
          (report-prime (- (runtime) start-time))))
    (define (report-prime elapsed-time)
      (display " *** ")
      (display elapsed-time))

Using this procedure, write a procedure `search-for-primes` that checks
the primality of consecutive odd integers in a specified range. Use your
procedure to find the three smallest primes larger than 1000; larger than
10,000; larger than 100,000; larger than 1,000,000. Note the time needed
to test each prime. Since the testing algorithm has order of growth of
*Θ(√n)*, you should expect that testing for primes around 10,000 should
take about √10 times as long as testing for primes around 1000. Do your
timing data bear this out? How well do the data for 100,000 and 1,000,000
support the *√n* prediction? Is your result compatible with the notion that
programs on your machine run in time proportional to the number of steps
required for the computation?

## Exercise 1.23.

The `smallest-divisor` procedure shown at the start of this section
does lots of needless testing: After it checks to see if the number is
divisible by 2 there is no point in checking to see if it is divisible
by any larger even numbers. This suggests that the values used for
`test-divisor` should not be 2, 3, 4, 5, 6, ..., but rather 2, 3, 5, 7,
9, .... To implement this change, define a procedure next that returns
3 if its input is equal to 2 and otherwise returns its input plus 2.
Modify the `smallest-divisor procedure to use `(next test-divisor)`
instead of `(+ test-divisor 1)`. With `timed-prime-test` incorporating
this modified version of `smallest-divisor`, run the test for each of
the 12 primes found in exercise 1.22. Since this modification halves
the number of test steps, you should expect it to run about twice as
fast. Is this expectation confirmed? If not, what is the observed ratio
of the speeds of the two algorithms, and how do you explain the fact
that it is different from 2?

## Exercise 1.24.

Modify the `timed-prime-test` procedure of exercise 1.22 to use
`fast-prime?` (the Fermat method), and test each of the 12 primes you
found in that exercise. Since the Fermat test has *Θ(log n)* growth, how
would you expect the time to test primes near 1,000,000 to compare with
the time needed to test primes near 1000? Do your data bear this out? Can
you explain any discrepancy you find?

## Exercise 1.25.

Alyssa P. Hacker complains that we went to a lot of extra work in writing
`expmod`. After all, she says, since we already know how to compute
exponentials, we could have simply written

    (define (expmod base exp m)
      (remainder (fast-expt base exp) m))

Is she correct? Would this procedure serve as well for our fast prime
tester? Explain.

## Exercise 1.26.

Louis Reasoner is having great difficulty doing exercise 1.24. His
`fast-prime?` test seems to run more slowly than his `prime?` test. Louis
calls his friend Eva Lu Ator over to help. When they examine Louis's code,
they find that he has rewritten the `expmod` procedure to use an explicit
multiplication, rather than calling `square`:

    (define (expmod base exp m)
      (cond ((= exp 0) 1)
            ((even? exp)
             (remainder (* (expmod base (/ exp 2) m)
                           (expmod base (/ exp 2) m))
                        m))
            (else
             (remainder (* base (expmod base (- exp 1) m))
                        m))))

"I don't see what difference that could make," says Louis. "I do." says
Eva. "By writing the procedure like that, you have transformed the
*Θ(log n)* process into a *Θ(n)* process." Explain.

## Exercise 1.27.

Demonstrate that the Carmichael numbers listed in footnote 47 really do
fool the Fermat test. That is, write a procedure that takes an integer
*n* and tests whether *aⁿ* is congruent to *a* modulo *n* for every *a<n*, and
try your procedure on the given Carmichael numbers.

## Exercise 1.28.

One variant of the Fermat test that cannot be fooled is called the
*Miller-Rabin test* (Miller 1976; Rabin 1980). This starts from an alternate
form of Fermat's Little Theorem, which states that if *n* is a prime
number and *a* is any positive integer less than *n*, then *a* raised to the
*(n - 1)*st power is congruent to 1 modulo *n*. To test the primality of a
number *n* by the Miller-Rabin test, we pick a random number a<*n* and raise
*a* to the (*n* - 1)st power modulo *n* using the `expmod` procedure. However,
whenever we perform the squaring step in `expmod`, we check to see if we
have discovered a "nontrivial square root of 1 modulo *n*," that is,
a number not equal to 1 or *n* - 1 whose square is equal to 1 modulo *n*. It
is possible to prove that if such a nontrivial square root of 1 exists,
then *n* is not prime. It is also possible to prove that if *n* is an odd
number that is not prime, then, for at least half the numbers *a<n*,
computing *aⁿ⁻¹* in this way will reveal a nontrivial square root of 1
modulo *n*. (This is why the Miller-Rabin test cannot be fooled.) Modify
the `expmod` procedure to signal if it discovers a nontrivial square root
of 1, and use this to implement the Miller-Rabin test with a procedure
analogous to `fermat-test`. Check your procedure by testing various known
primes and non-primes. Hint: One convenient way to make `expmod` signal
is to have it return 0.
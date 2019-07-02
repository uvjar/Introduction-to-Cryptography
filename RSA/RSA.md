# The RSA cryptosystem

## Theoretical background

### Overview of RSA 

**Initial setup**
Bob: 

* choose two primes p, q
* from p and q, determine $n=pq$ and $\varphi(n)$
* choose e smaller than $\varphi(n)$, and that gcd(e,n)=1. 
* From e determine d such that $ed\equiv 1$ mod $\varphi(n)$. d can be calculated using the Extended Euclidian Algorithm

 public key: (n,e)
 secrete key: (n,d)
 
 


**Encryption**
Alice:

* obtain public key $n$ and $e$ 
* do encryption to message $m$, $c\equiv m^e$ mod $n$ 
* send $c$ to Bob

**Decryption**
Bob: 

* Receive $c$ 
* Compute $m\equiv c^d$ mod $n$



### example

* Bob generates
 * $p=101$, $q=113$
 * $n=11413$, and $\varphi(n)=11200$
 * select e to be $e=3533$, $d=6597$
* Bob publishes n and e
Anybody now can use n and $e$ to encrypt a message and send it to Bob. In particular, Alice encrypt $9726$ with: $9726^{3533}\equiv 5761$ mod $11413$
* On receiving the message Bob computes $5761^{6597}\equiv 9726$ mod $11413$

### Reliability of RSA

in the process, n and e are public. To decrypt the message, d is needed. Note that

* $ed\equiv1$ Thus $\varphi(n)$ is needed to determine d
* p and q are needed to determined $\varphi(n)$
* $n$ need to be factorize to determine $p$ and $q$

However, QR problem is proved to be not computationally feasible to solve




### gmp

**Add**  Set rop to op1 + op2.
`void mpz_add (mpz_t rop, const mpz_t op1, const mpz_t op2)`
**sub**
`void mpz_sub (mpz t rop, const mpz t op1, const mpz t op2)`
**mul**
`void mpz_mul (mpz t rop, const mpz t op1, const mpz t op2)`
**Determine whether n is prime**
`int mpz_probab_prime_p (mpz_t n, int reps)`


**gcd**
`void mpz_gcd (mpz t rop, const mpz t op1, const mpz t op2)`
Set rop to the greatest common divisor of op1 and op2. The result is always positive even if one or both input operands are negative. Except if both inputs are zero; then this function defines gcd(0, 0) = 0.

**compare**
`int mpz_cmp (mpz_t op1, mpz_t op2)`



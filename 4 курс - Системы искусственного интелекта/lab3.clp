(deffacts f0
(a a)
(b b)
(c c)
(d d)
(e e))

(defrule r01
(declare(salience 8000))
(e e)
(d d)
(a a)
=>
(assert (p p)))

(defrule r02
(declare (salience 8000))
(b b)
(d d)
=>
(assert (m m)))

(defrule r03
(declare (salience 8000))
(a a)
(c c)
=>
(assert (n n)))

(defrule r04
(declare (salience 8000))
(a a)
(d d)
(b b)
=>
(assert (r r)))

(defrule r05
(declare (salience 6000))
(m m)
(p p)
=>
(assert (r r)))

(defrule r06
(declare (salience 6000))
(a a)
(n n)
(r r)
=>
(assert (s s)))
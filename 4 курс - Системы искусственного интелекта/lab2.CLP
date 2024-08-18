(deftemplate student 
(slot name)
(slot age)
(slot year)
(slot spec)
(slot aver_mark))

(deffacts students
  (student (name John) (age 20) (year 3) (spec "hard") (aver_mark 4.5))
  (student (name Jane) (age 18) (year 2) (spec "hard") (aver_mark 5.0))
  (student (name Jude) (age 22) (year 4) (spec "soft") (aver_mark 3.8))
  (student (name Toma) (age 21) (year 3) (spec "ai")   (aver_mark 3.5))
  (student (name Joan) (age 19) (year 4) (spec "hard") (aver_mark 4.5))
  (student (name Mark) (age 23) (year 5) (spec "soft") (aver_mark 3.0))
  (student (name Fred) (age 20) (year 2) (spec "ai")   (aver_mark 4.0))
  (student (name Eric) (age 24) (year 6) (spec "hard") (aver_mark 4.5))
  (student (name Mary) (age 20) (year 3) (spec "ai")   (aver_mark 3.6))
  (student (name Beth) (age 24) (year 5) (spec "soft") (aver_mark 3.1))
)


(defrule R1
	(student (name ?name) (age  ?age) (year ?year) (spec ?spec) (aver_mark ?ave_mark))
	
		(test (>= 20 (- ?age ?year)))
=>
(printout t crlf ?name " поступил в " ?age " лет" crlf))



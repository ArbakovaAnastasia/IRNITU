
(defrule BCC__start (declare (salience 805))
   (push goal ? ? ?) 
   (stacktop goal 0)
=> 
   (assert (preprocessRules))
)

(defrule BCC__top1 (declare (salience 800))
   (preprocessRules) => 
   (assert(getrules))
)

(defrule BCC__top2 (declare (salience 800))
   (preprocessRules) 
   ?dgr <-(done getrules) 
=> 
   (retract ?dgr)
   (assert (deletebackchainrules))
)

(defrule BCC__top3 (declare (salience 800))
   (preprocessRules) 
   ?dbcr <-(done deletebackchainrules) 
=> 
   (retract ?dbcr)
   (assert (splitrules))
)

(defrule BCC__top4 (declare (salience 800))
   ?pr <- (preprocessRules) 
   ?dbcr <-(done splitrules) 
=> 
   (retract ?pr)
   (retract ?dbcr)
   (assert (backchain))
)


;;--------------Get all the rules and break them into individual rules

(defrule BCC__entergetrules (declare (salience 800))
   (getrules) 
=>
                                 (assert(numrules 0))
                                 (assert (rules (getPPRules)))
                                 (assert (ingetrules))
)

;for each rule 
;;get the first part
;;get the second part
(defrule BCC__BreakOffFirstPart (declare (salience 800))
   (ingetrules)
   ?oldrule <- (rules ?rules) 
=>
   (assert (firstpart (sub-string 0 8 ?rules)))
   (assert (lastpart (sub-string 9 (str-length ?rules) ?rules)))
   (retract ?oldrule)
)

(defrule  BCC__GetSecondPartA (declare (salience 800))
   (ingetrules)
   (lastpart ?rules) 
=> 
   (assert (rule-start-red (str-index (str-cat "def" "rule") ?rules)))
)

(defrule BCC__GetSecondPartB (declare (salience 805))
    (ingetrules)
    ?tempstart<-(rule-start-red ?start) (test(integerp ?start))
=> 
   (assert (rule-start (- ?start 2)))
   (retract ?tempstart)
)

(defrule BCC__BreakOffSecondPart (declare (salience 800))
                            (ingetrules)
                            ?oldrule <- (lastpart ?rules) 
                            ?numrulesfact <- (numrules ?numrules)
                            ?firstpartfact <- (firstpart ?firstpart)
                            ?rule-start <- (rule-start ?start) =>
   (assert (rule (+ ?numrules 1) 
      (str-cat ?firstpart (sub-string 0 ?start ?rules))))
   (assert (rules (sub-string (+ ?start 1) (str-length ?rules) ?rules)))
   (assert (numrules (+ ?numrules 1)))
   (retract ?oldrule)
   (retract ?numrulesfact)
   (retract ?firstpartfact)
   (retract ?rule-start)
)

(defrule BCC__BreakOffLastSecondPart (declare (salience 800))
    (ingetrules)
    ?oldrule <- (lastpart ?rules) 
    ?endmarker <- (rule-start-red FALSE)
    ?numrulesfact <- (numrules ?numrules)
    ?firstpartfact <- (firstpart ?firstpart)
=>
   (assert (rule (+ ?numrules 1) 
      (str-cat ?firstpart (sub-string 0 (str-length ?rules) ?rules))))
   (assert (numrules (+ ?numrules 1)))
   (retract ?oldrule)
   (retract ?endmarker)
   (retract ?numrulesfact)
   (retract ?firstpartfact)
)

(defrule BCC__finishgetrules (declare (salience 799))
   ?ig <- (ingetrules)
   ?g <- (getrules)
=>
   (retract ?ig)
   (retract ?g)
   (assert (done getrules))
)

;-----------delete backchain rules from list
(defrule BCC__enterDeleteRules (declare (salience 800))
   (deletebackchainrules) => 
   (assert (in deletebackrules))
)

(defrule BCC__testrule (declare (salience 800))
   (in deletebackrules) (rule ?num ?body) =>
   (assert (delete-rule ?num (str-index "BCC__" ?body)))
)

(defrule BCC__removerule (declare (salience 800))
   (in deletebackrules) 
   ?rule <- (rule ?num ?body) 
   ?delfact <- (delete-rule ?num ?value) (test (integerp ?value))
=>
   (retract ?rule)
   (retract ?delfact)
)

(defrule BCC__remdeleteFALSE (declare (salience 800))
   (in deletebackrules) 
   ?delfalse <- (delete-rule ? FALSE) 
=>
   (retract ?delfalse)
)

(defrule  BCC__finishdeletebackrules (declare (salience 799))
   ?id <- (in deletebackrules) 
   ?dbc <- (deletebackchainrules)
=> 
   (retract ?id)
   (retract ?dbc)
   (assert (done deletebackchainrules))
)

;-----------split rules into RHS and LHS
(defrule BCC__enterSplitRules (declare (salience 800))
   (splitrules) => 
   (assert (in splitrules))
)
(defrule BCC__exitSplitRules (declare (salience 790))
   ?sr <- (splitrules) 
   ?isr <-(in splitrules)
=> 
   (retract ?sr)
   (retract ?isr)
   (assert (done splitrules))
)

(defrule BCC__enterGetArrow (declare (salience 800))
  (in splitrules) 
  (rule ?num ?rulecontents)
=> 
  (assert(rulearrow ?num (str-index "=>" ?rulecontents)))
)

(defrule BCC__getInitialSplit (declare (salience 800))
   (in splitrules) (rule ?num ?rule-contents)
   ?ra <-(rulearrow ?num ?splitplace)
=> 
  (assert(initialLHS ?num (sub-string 0 (- ?splitplace 1) ?rule-contents)))
  (assert(ruleRHS ?num (sub-string (+ ?splitplace 3)
                  (- (str-length ?rule-contents) 2)
                  ?rule-contents)))
  (assert (ruleRHSParts ?num 0))
  (assert (ruleLHSParts ?num 0))
  (retract ?ra)
)

(defrule BCC__removeLHSDef (declare (salience 800))
  (in splitrules) 
  ?LHS <- (initialLHS ?num ?LHS-contents)
=> 
  (assert(secondLHS ?num (sub-string(+(str-index " " ?LHS-contents) 1)
                                    (str-length ?LHS-contents) ?LHS-contents)))
  (retract ?LHS)
)

(defrule BCC__getLHSName (declare (salience 800))
  (in splitrules) 
  ?LHS <- (secondLHS ?num ?LHS-contents)
=> 
  (assert(rulename ?num (sub-string (+(str-index "MAIN::" ?LHS-contents)6)
                                    (-(str-index " " ?LHS-contents) 2)
;                                    (-(str-index "(" ?LHS-contents) 5)
                                    ?LHS-contents)))
  (assert(ruleLHS ?num (sub-string (str-index "(" ?LHS-contents) 
                                   (str-length ?LHS-contents) ?LHS-contents)))
  (retract ?LHS)
)

;;--split rhs
(defrule BCC__splitRHSStart (declare (salience 800))
   (in splitrules)
   (ruleRHS ?num ?rhs) 
=>
   (assert (RHSSplit ?num (str-index "(assert" ?rhs)))
)

(defrule BCC__splitTrimAssert (declare (salience 800))
   (in splitrules)
   ?rr <- (ruleRHS ?num ?rhs) 
   ?rs <- (RHSSplit ?num ?start)
   (test (integerp ?start))
=>  
   (assert (ruleRHSMid ?num (sub-string (+ ?start 9) (str-length ?rhs) ?rhs)))
   (retract ?rr)
   (retract ?rs)
)

(defrule BCC__splitRHSEnd (declare (salience 800))
   (in splitrules)
   ?rr <- (ruleRHS ?num ?rhs)
   ?rs <- (RHSSplit ?num FALSE)
=>  
   (retract ?rr)
   (retract ?rs)
)

(defrule BCC__splitRHSMid (declare (salience 800))
   (in splitrules)
   ?rrm<- (ruleRHSMid ?num ?rhs) 
=>
   (assert (RHSSplit2 ?num (str-index "))" ?rhs) ?rhs))
   (retract ?rrm)
)

(defrule BCC__splitRHS (declare (salience 800))
   (in splitrules)
   ?rs<-(RHSSplit2 ?num ?start ?rhs)
   ?rrp <- (ruleRHSParts ?num ?partnum)
=>  
   (assert (ruleRHSAssert ?num ?partnum (sub-string 0 (- ?start 1) ?rhs)))
   (assert (ruleRHS ?num (sub-string (+ ?start 2) (str-length ?rhs) ?rhs)))
   (assert (ruleRHSParts ?num (+ ?partnum 1)))
   (retract ?rs)
   (retract ?rrp)
)

;;--split lhs as it is, this assumes only standalone (implicitly anded) 
;lhs parts
(defrule BCC__splitLHSStart (declare (salience 800))
   (in splitrules)
   (ruleLHS ?num ?lhs) 
=>
   (assert (LHSSplit ?num (str-index "(" ?lhs)))
)

(defrule BCC__splitLHSTrimLPar (declare (salience 800))
   (in splitrules)
   ?lr <- (ruleLHS ?num ?lhs) 
   ?ls <- (LHSSplit ?num ?start)
   (test (integerp ?start))
=>  
   (assert (ruleLHSMid ?num (sub-string (+ ?start 1) (str-length ?lhs) ?lhs)))
   (retract ?lr)
   (retract ?ls)
)

(defrule BCC__splitLHSEnd (declare (salience 800))
   (in splitrules)
   ?lr <- (ruleLHS ?num ?lhs)
   ?ls <- (LHSSplit ?num FALSE)
=>  
   (retract ?lr)
   (retract ?ls)
)

(defrule BCC__splitLHSMid (declare (salience 800))
   (in splitrules)
   ?lrm<- (ruleLHSMid ?num ?lhs) 
=>
   (assert (LHSSplit2 ?num (str-index ")" ?lhs) ?lhs))
   (retract ?lrm)
)

(defrule BCC__splitLHS (declare (salience 800))
   (in splitrules)
   ?ls<-(LHSSplit2 ?num ?start ?lhs)
   ?lrp <- (ruleLHSParts ?num ?partnum)
=>  
   (assert (ruleLHSClause ?num ?partnum (sub-string 0 (- ?start 1) ?lhs)))
   (assert (ruleLHS ?num (sub-string (+ ?start 1) (str-length ?lhs) ?lhs)))
   (assert (ruleLHSParts ?num (+ ?partnum 1)))
   (retract ?ls)
   (retract ?lrp)
)

;;------------------------rules for stack manipulation-------------------------
;;In this I've used element as an element of a stack and part as part of 
;;an element.
;;It has three parts per stack element to make it more generic.
;;To get stacks to work you need to declare a stack by 
;;(assert stacktop ?stackname 0)
;;then push elements by (push ?stackname ?p1 ?p2 ?p3)
;;and pop by (pop ?stackname) with the result left in
;;(stackresult ?stackname ?p1 ?p2 ?p3)

(defrule BCC__push (declare (salience 805))
   (backchain)
   ?pi<- (push ?stackname ?part1 ?part2 ?part3) 
   ?st<- (stacktop ?stackname ?val)
=>
   (assert (stack ?stackname (+ ?val 1) ?part1 ?part2 ?part3))
   (assert (stacktop ?stackname (+ ?val 1)))
   (retract ?pi)
   (retract ?st)
)
(defrule BCC__pushD (declare (salience 805))
   (debug backchain)
   (backchain)
   ?pi<- (push ?stackname ?part1 ?part2 ?part3) 
   ?st<- (stacktop ?stackname ?val)
=>
(printout t "push " (+ ?val 1) " " ?part1 crlf)
   (assert (stack ?stackname (+ ?val 1) ?part1 ?part2 ?part3))
   (assert (stacktop ?stackname (+ ?val 1)))
   (retract ?pi)
   (retract ?st)
)

(defrule BCC__pop (declare (salience 805))
   ?pi <- (pop ?stackname)
   ?st <- (stacktop ?stackname ?topval)
   (test (> ?topval 0))
   ?se <- (stack ?stackname ?topval ?part1 ?part2 ?part3)
=>
  (assert (stackresult ?stackname ?part1 ?part2 ?part3))
  (assert (stacktop ?stackname (- ?topval 1)))
  (retract ?pi)
  (retract ?st)
  (retract ?se)
)
(defrule BCC__popD (declare (salience 805))
   (debug backchain)
   ?pi <- (pop ?stackname)
   ?st <- (stacktop ?stackname ?topval)
   (test (> ?topval 0))
   ?se <- (stack ?stackname ?topval ?part1 ?part2 ?part3)
=>
(printout t "pop " ?topval " " ?part1 crlf)
  (assert (stackresult ?stackname ?part1 ?part2 ?part3))
  (assert (stacktop ?stackname (- ?topval 1)))
  (retract ?pi)
  (retract ?st)
  (retract ?se)
)

(defrule BCC__poperror (declare (salience 800))
   ?pi<-(pop ?stackname)
   (stacktop ?stackname ?topval)
   (test (<= ?topval 0))
=>
   (printout t "popped an empty stack " ?stackname crlf)
   (assert (stackresult ?stackname empty))
   (retract ?pi)
)


;;;prompt user 
;;----------  Prompt user for info
(defrule BCC__promptuser (declare (salience 790))
         (stacktop goal ?top)
         (stack goal ?top ?fact ?rulenum ?)
         (promptuser ?fact)
=>  
    (printout t "Is " ?fact " True ")
    (assert (userinput ?fact (read)))
)

(defrule BCC__addUserFact (declare (salience 800))
    ?ui <- (userinput ?fact ?yes)
    (test (eq (str-compare ?yes "yes") 0))
    (stacktop goal ?stacknum)
    (stack goal ?stacknum ? ?rulenum ?)
    (rulename ?rulenum ?name)
=>
    (assert-string (str-cat "(" ?fact ")"))
    (assert (ruleExecutes (isRuleExecutable ?name)))
)

(defrule BCC__dontAddUserFact (declare (salience 800))
    ?ui <- (userinput ?fact ?yes)
    (test (neq (str-compare ?yes "yes") 0))
=>
    (retract ?ui)
)

;;;;rules for trying to execute a rule that resolves a goal
(defrule BCC__checkRuleExecutable (declare (salience 802))
   (backchain)
   (stacktop goal ?num)
   (stack goal ?num ? ?rulenum ?)
   (rulename ?rulenum ?name)
=>
   (assert (ruleExecutes (isRuleExecutable ?name)))
)

(defrule BCC__executeRuleAndUI (declare (salience 802))
   (backchain)
   ?re <- (ruleExecutes TRUE)
   (stacktop goal ?num)
   (stack goal ?num ? ?rulenum ?)
   (rulename ?rulenum ?name)
   ?ui <- (userinput ?fact ?yes)
   (test (eq (str-compare ?yes "yes") 0))
   (not (popStack ? ?))
=>
   (setRuleSalience ?name 900)
   (retract ?re)
   (retract ?ui)
   (assert (popStackE ?num ?rulenum success))
)

(defrule BCC__executeRule (declare (salience 801))
   (backchain)
   ?re <- (ruleExecutes TRUE)
   (stacktop goal ?num)
   (stack goal ?num ? ?rulenum ?)
   (rulename ?rulenum ?name)
=>
   (setRuleSalience ?name 900)
   (retract ?re)
   (assert (popStackE ?num ?rulenum success))
)

(defrule BCC__removeUIYes (declare (salience 800))
   (backchain)
   (stacktop goal ?num)
   ?ui <- (userinput ?fact ?yes)
   (test (eq (str-compare ?yes "yes") 0))
=>
   (retract ?ui)
   (assert (popStackF ?num success))
)

(defrule BCC__removeFalseExecute (declare (salience 802))
   (backchain)
   ?re <- (ruleExecutes FALSE)
=>
   (retract ?re)
)


;;;;PUSH;;;;;;
;;;;if a goal has just been pushed,
;;;if the rule it is trying to fulfill is executable,
;;;   execute it
;;;   then pop success
;;;else if the goal is true, pop success
;;;else see if it is a prompt
;;;   if so prompt the user
;;;      if yes then pop sucess     
;;;      if not (or no prompt)
;;;else if subgoal push subgoals
;;;else pop fail

;;;check the new sub goal is true by asserting it and seeing whether
;;;that assert is false (in which case it's true)
(defrule BCC__newSubGoalTrue1 (declare (salience 801))
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
=>
   (assert (goalFactDoesNotExist (assert-string (str-cat "(" 
            ?thegoal ")"))))
)   

(defrule BCC__retractgoalFact (declare (salience 801))
   ?gf <- (goalFactDoesNotExist ?exist) 
   (test (neq ?exist FALSE))
=> 
   (retract ?exist)
   (retract ?gf)
)

;the subgoal is true so pop it.
(defrule BCC__newSubGoalTrue2 (declare (salience 801))
   ?gf <- (goalFactDoesNotExist FALSE) 
   (stacktop goal ?num) 
=> 
   (retract ?gf)
   (assert (popStackF ?num success))
)


;;;;;rules for setting up a push or several pushes
;;---------------goal matching------------------------
(defrule BCC__match (declare (salience 800))
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
   (ruleRHSAssert ?rulenum ?an ?thegoal)
   (not (goalmatch ?))
=>
   (assert (goalmatch ?rulenum))
)

(defrule BCC__secondMatch (declare (salience 815))
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
   (ruleRHSAssert ?rulenum ?an ?thegoal)
   (goalmatch ?rule1)
   (test (neq ?rule1 ?rulenum))
   (not (backtrack4))
=>
   (assert (othermatch ?rulenum))
)

;push the rule and backups onto the stack
(defrule BCC__assembleOthers (declare (salience 812))
   ?om1 <- (othermatch ?rule1)
   ?om2 <- (othermatch ?rule2)
   (test(neq ?rule1 ?rule2))
=>
   (assert-string (str-cat "(othermatch " ?rule1 "+" ?rule2 ")"))
   (retract ?om1)
   (retract ?om2)
)

;pushMultiplSubgoal and pushLastMultipleSubgoal work by pushingMultipleSubgoal 
;for all but the last one.  This is arranged by salience
(defrule BCC__pushMultipleSubgoals (declare (salience 812))
   (goalmatch ?rulenum)
   (ruleLHSClause ?rulenum ? ?fact)
   (othermatch ?rules)
=>
   (assert(push goal ?fact ?rulenum ?rules))
)

(defrule BCC__pushLastMultipleSubgoals (declare (salience 811))
   ?gm<-(goalmatch ?rulenum)
   (ruleLHSClause ?rulenum ? ?fact)
   ?om<-(othermatch ?rules)
=>
   (assert(push goal ?fact ?rulenum ?rules))
   (retract ?gm)
   (retract ?om)
)

;pushSubgoal and pushLastSubgoal work by pushingSubgoal 
;for all but the last one.  This is arranged by salience
(defrule BCC__pushSubgoal (declare (salience 810))
   ?gm<-(goalmatch ?rulenum)
   (ruleLHSClause ?rulenum ?clausenum ?fact)
=>
   (assert(push goal ?fact ?rulenum 0))
)

(defrule BCC__removeBT4 (declare (salience 807))
   ?bt <- (backtrack4)
=>
   (retract ?bt)
)

(defrule BCC__pushLastSubgoal (declare (salience 808))
   ?gm<-(goalmatch ?rulenum)
   (ruleLHSClause ?rulenum ? ?fact)
=>
   (retract ?gm)
)


;;;POP;;;;;
;;;;;pop success
;;;if popStack1 then return from backchaining success 
;;;else if other subgoals of the current subgoal then
;undone
;;;else rule should be executable, so
;;;  execute rule
;;;  pop success
;;--------goal satisfying --------
(defrule BCC__backchainDone (declare (salience 810))
   ?bc <- (backchain)
   ?st <- (stacktop goal 0)
   ?sr <- (stackresult goal ?Goal 0 ?)
   (not(popStack 1 fail))
=>
   (retract ?bc)
   (retract ?st)
   (retract ?sr)
   (printout t "Goal " ?Goal " Achieved " crlf)
   (assert (goal ?Goal Achieved))
)

;;If a rule has executed successfully (popStackE), get rid of
;;all the stack elements from it.
(defrule BCC__satisfyMultiple (declare (salience 805))
   (backchain)
   (popStackE ?num ?successRule success)
   (stacktop goal ?num2)
   (stack goal ?num2 ? ?successRule ?)
   (test (>= ?num ?num2))
=>
   (assert (pop goal))
)
(defrule BCC__removeRuleSR (declare (salience 804))
   (backchain)
   (popStackE ?num ?successRule success)
   ?sr <- (stackresult goal ? ?successRule ?)
=>
   (retract ?sr)
)

(defrule BCC__removeRulePS (declare (salience 804))
   ?ps <- (popStackE ?num ?successRule success)
=>
   (retract ?ps)
)


(defrule BCC__satisfySingle (declare (salience 805))
   (backchain)
   ?pf <- (popStackF ?num success)
   (stacktop goal ?num)
   (stack goal ?num ? ?rulenum ?)
=>
   (assert (pop goal))
   (retract ?pf)
)

(defrule BCC__removeStackResults (declare (salience 804))
   (backchain)
   ?sg <- (subgoal achieved ?)
   ?sr <- (stackresult goal ? ? ?)
   (not (stacktop goal 0))
=>
   (retract ?sr)
   (retract ?sg)
)

;;;;pop fail
(defrule BCC__backchainDoneFail (declare (salience 790))
   ?bc <- (backchain)
   ?st <- (stacktop goal 0)
   ?sr <- (stackresult goal ?Goal 0 ?)
   ?sf <- (popStack 1 fail)
=>
   (retract ?bc)
   (retract ?st)
   (retract ?sr)
   (retract ?sf)
   (printout t "Goal " ?Goal " Failed " crlf)
   (assert (goal ?Goal Failed))
)

(defrule BCC__popFail (declare (salience 780))
   (backchain)
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
=> 
   (assert (pop goal))
   (assert (popStack ?num fail))
)
   
(defrule BCC__popFailAgain (declare (salience 804))
   (backchain)
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
   ?ps <- (popStack ?num2 fail)
   ?sr <- (stackresult goal ?failedgoal ? 0)
   (test (eq ?num (- ?num2 1)))
=> 
   (assert (pop goal))
   (assert (popStack ?num fail))
   (retract ?sr)
   (retract ?ps)
)
   
;;-----------goals failing-------------
;If there are multiple LHSs on stack,
;;remove all but the last.  Let popbacktrack handle the last
(defrule BCC__popMultipleLHSFail (declare (salience 786))
   (backchain)
   (stacktop goal ?num)
   (stack goal ?num ?thegoal ?failedrule ?otherrules)
   (stack goal ?num2 ? ?failedrule ?otherrules)
   (test (eq ?num (+ ?num2 1)))
   (test (neq ?otherrules 0)) 
=> 
   (assert (pop goal))
   (assert (popMultiStack ?failedrule ?otherrules))
)

(defrule BCC__popMultipleLHSFail2 (declare (salience 804))
   (popMultiStack ?failedrule ?otherrules)
   (stacktop goal ?num)
   (stack goal ?num ?thegoal ?failedrule ?otherrules)
   ?sr <- (stackresult goal ? ? ?)
=> 
   (assert (pop goal))
   (retract ?sr)
)

;stop popping bad LHSs, but setup backtracking
(defrule BCC__popMultipleLHSFail3 (declare (salience 804))
   ?pm <- (popMultiStack ?failedrule ?otherrules)
   (stacktop goal ?num)
   (stack goal ?num ?thegoal ?rule2 ?)
   (test (neq ?rule2 ?failedrule))
=>
   (retract ?pm)
   (assert (backtrack (implode$ (create$ ?otherrules))))
   (assert (popStack (+ ?num 1) fail))
)

;backtrack from last LHS failure
(defrule BCC__popBacktrack (declare (salience 785))
   (backchain)
   (stack goal ?num ?thegoal ?failedrule ?otherrules)
   (stacktop goal ?num)
   (test (neq ?otherrules 0)) 
=> 
   (assert (pop goal))
   (assert (popStack ?num fail))
   (assert (backtrack (implode$ (create$ ?otherrules))))
)

(defrule BCC__pushBacktrack (declare (salience 804))
   ?bt <- (backtrack ?otherrules)
   ?ps <- (popStack ?num fail)
   ?sr <- (stackresult goal ? ? ?)
=> 
   (assert (backtrack ?otherrules (str-index "+" ?otherrules)))
   (retract ?bt)
   (retract ?ps)
   (retract ?sr)
)

   
(defrule BCC__pushBacktrack2 (declare (salience 804))
   ?bt <- (backtrack ?otherrules ?offset)
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
   (test(integerp ?offset))
=> 
   (assert (backtrack3 last (eval(sub-string 0 (- ?offset 1) ?otherrules))
        (sub-string (+ ?offset 1) (str-length ?otherrules)  ?otherrules)))
   (retract ?bt)
)
(defrule BCC__pushBacktrack2a (declare (salience 803))
   ?bt <- (backtrack ?otherrules ?offset)
   (stack goal ?num ?thegoal ? ?)
   (stacktop goal ?num) 
=> 
   (assert (backtrack3 last (eval ?otherrules)))
   (retract ?bt)
)

;The backtrack3s should just set up the normal push
(defrule BCC__pushBacktrack3 (declare (salience 804))
   ?bt <- (backtrack3 last ?new ?otherrules)
=>
   (assert (goalmatch ?new))
   (assert (othermatch (eval ?otherrules)))
   (assert (backtrack4))
   (retract ?bt)
)

(defrule BCC__pushBacktrack3a (declare (salience 804))
   ?bt <- (backtrack3 last ?new )
=>
   (assert (goalmatch ?new))
   (assert (backtrack4))
   (retract ?bt)
)

   




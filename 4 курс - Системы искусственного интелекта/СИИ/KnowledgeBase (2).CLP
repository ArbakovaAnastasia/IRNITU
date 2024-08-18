(deffacts initial
  (initial-fact)
)

(deftemplate weekday   
  (slot id)  
  (slot name)  
)

(deffacts  weekdays
  (weekday (id 1) (name "понедельник"))
  (weekday (id 2) (name "вторник"))
  (weekday (id 3) (name "среда"))
  (weekday (id 4) (name "четверг"))
  (weekday (id 5) (name "пятница"))
  (weekday (id 6) (name "суббота"))
  (weekday (id 7) (name "воскресенье"))
)

(deftemplate personGroup
  (slot id)        
  (slot group_name)       
  (slot person_name)   
)

(deftemplate person
  (slot id)        
  (slot name)       
  (slot group_name)  
)

(deftemplate freeTime
  (slot id_person)
  (slot minDate)
  (slot maxDate)
  (slot minHour)
  (slot maxHour)
  (slot minMinute)
  (slot maxMinute)
  (slot minSecond)
  (slot maxSecond)
  (slot id_weekday)
)

(deftemplate useFreeTime
  (slot id_person)
  (slot minDate)
  (slot maxDate)
  (slot minHour)
  (slot maxHour)
  (slot minMinute)
  (slot maxMinute)
  (slot minSecond)
  (slot maxSecond)
  (slot id_weekday)
)

(deftemplate generalFreeTime
  (slot minDate)
  (slot maxDate)
  (slot minHour)
  (slot maxHour)
  (slot minMinute)
  (slot maxMinute)
  (slot minSecond)
  (slot maxSecond)
  (slot id_weekday)
)

(deftemplate event
  (slot id)
  (slot name)
  (slot hour)
  (slot minute)
  (slot second)
)

(deftemplate eventRequest
  (slot name)
  (slot date)
  (slot group_name)
  (slot minHour)
  (slot maxHour)
  (slot minMinute)
  (slot maxMinute)
  (slot minSecond)
  (slot maxSecond)
)

(deftemplate answer1
  (slot text)
)

(deftemplate answer2
  (slot text)
)

(deftemplate answer3
  (slot text)
)

(deftemplate answer
  (slot text)
)


const calendar = document.querySelector(".calendar"),
    date = document.querySelector(".date"),
    daysContainer = document.querySelector(".days"),
    prev = document.querySelector(".prev"),
    next = document.querySelector(".next"),
    todayBtn = document.querySelector(".today-btn"),
    gotoBtn = document.querySelector(".goto-btn"),
    dateInput = document.querySelector(".date-input"),
    eventDay = document.querySelector(".event-day"),
    eventDate = document.querySelector(".event-date"),
    eventsContainer = document.querySelector(".events"),
    addEventSubmit = document.querySelector(".add-event-btn"),
    eventStats = document.querySelector(".reminders-event"),
    eventStats1 = document.querySelector(".reminders-event-1"),
    eventStats2 = document.querySelector(".reminders-event-2");
    // eventStats3 = document.querySelector(".events-stats-events"),
    // eventStats4 = document.querySelector(".events-stats-events-1");///////////////////////////////////

let today = new Date();
let activeDay;
let month = today.getMonth();
let year = today.getFullYear();

const months = [
    "Январь",
    "Февраль",
    "Март",
    "Апрель",
    "Май",
    "Июнь",
    "Июль",
    "Август",
    "Сентябрь",
    "Октябрь",
    "Ноябрь",
    "Декабрь",
];

let eventsArr = [];
getEvents();
let eventArrDone = [];

function initCalendar(){                                        //функция добавления дней
    const firstDay = new Date(year, month, 1);
    const lastDay = new Date(year, month + 1, 0);
    const prevLastDay = new Date(year, month, 0);
    const prevDays = (firstDay.getDay() + 6) % 7;               //изм
    const lastDate = lastDay.getDate();
    const day = (firstDay.getDay() + 6) % 7;                    //изм
    const nextDays = (7 - lastDay.getDay() - 1 + 7) % 7;        //изм
    
    date.innerHTML = months[month] + "    " + year + " год"; //update date top of calendar
    let  days = ""; //adding days on dom
    //prev month days
    for (let x = day; x > 0; x--){
        days += `<div class="day prev-date">${prevLastDay.getDate() - x + 1}</div>`;    //изм
    }
    
    //current month days
    for (let i = 1; i <= lastDate; i++){
        let event = false;  //check if event present on current day
        eventsArr.forEach((eventObj) => {
            if (
                eventObj.day === i &&
                eventObj.month === month + 1 &&
                eventObj.year === year
            )
            {
                event = true;   //if event found
            }
        });

        //if day is today add class today
        if (i === new Date().getDate() && year === new Date().getFullYear() && month === new Date().getMonth()) {
            activeDay = i;
            getActiveDay(i);
            updateEvents(i);
            updateEventStats(i);
            if (event) {
                days += `<div class="day today active event">${i}</div>`;                                             
            }
            else {
                days += `<div class="day today active">${i}</div>`;                                           
            }
        } else { //add remaing as it is
            if (event) {
                days += `<div class="day event">${i}</div>`;                                             
            }
            else {
                days += `<div class="day">${i}</div>`;                                           
            }
        }   
    }
    
    //next month days
    for(let j = 1; j <= nextDays+1; j++){  //изм
        days += `<div class="day next-date">${j}</div>`;
    }
    daysContainer.innerHTML = days;
    addListner();
}

initCalendar();

function prevMonth(){  //prev month
    month--;
    if (month < 0) {
        month = 11;
        year--;
    }
    initCalendar();
}

function nextMonth(){  //next month
    month++;
    if (month > 11){
        month = 0;
        year++;
    }
    initCalendar();
}

//add event listener on prev and next
prev.addEventListener("click", prevMonth);
next.addEventListener("click", nextMonth);

//add goto date and goto today
todayBtn.addEventListener("click", () => {
    today = new Date();
    month = today.getMonth();
    year = today.getFullYear();
    initCalendar();
});
dateInput.addEventListener("input", (e) => {
    dateInput.value = dateInput.value.replace(/[^0-9/]/g, "");
    if (dateInput.value.length === 2) {
      dateInput.value += "/";
    }
    if (dateInput.value.length > 7) {
      dateInput.value = dateInput.value.slice(0, 7);
    }
    if (e.inputType === "deleteContentBackward") {
      if (dateInput.value.length === 3) {
        dateInput.value = dateInput.value.slice(0, 2);
      }
    }
});

gotoBtn.addEventListener("click", gotoDate);

function gotoDate() {
    const dateArr = dateInput.value.split("/");
    if (dateArr.length === 2) {
        if (dateArr[0] > 0 && dateArr[0] < 13 && dateArr[1].length === 4) {
            month = dateArr[0] - 1;
            year = dateArr[1];
            initCalendar();
            return;
        }
    }
    alert("Неверный ввод.")
};

const addEventBtn = document.querySelector(".add-event"),
    addEventContainer = document.querySelector(".add-event-wrapper"),
    addEventCloseBtn = document.querySelector(".close"),
    addEventTitle = document.querySelector(".event-name"),
    addEventFrom = document.querySelector(".event-time-from"),
    addEventTo = document.querySelector(".event-time-to");
    addEventPerson = document.querySelector(".event-person"),
    addEventType = document.querySelector(".event-type"),
    addEventDescription = document.querySelector(".event-description");

addEventBtn.addEventListener("click", () => {
    addEventContainer.classList.toggle("active");
});
addEventCloseBtn.addEventListener("click", () => {
    addEventContainer.classList.remove("active");
});
document.addEventListener("click", (e) => {
    if (e.target !== addEventBtn && !addEventContainer.contains(e.target)) {
      addEventContainer.classList.remove("active");
    }
});
addEventTitle.addEventListener("input",  (e) => {
    addEventTitle.value = addEventTitle.value.slice(0, 50);
});
addEventPerson.addEventListener("input", (e) => {
     addEventPerson.value = addEventPerson.value.slice(0, 50);
 })
addEventDescription.addEventListener("input", (e) => {
     addEventDescription.value = addEventDescription.value.slice(0, 100);
})

//time format in from and to time
addEventFrom.addEventListener("input", (e) => {
    addEventFrom.value = addEventFrom.value.replace(/[^0-9:]/g, "");
    if(addEventFrom.value.length === 2) {
        addEventFrom.value += ":";
    }
    if (addEventFrom.value.length > 5){
        addEventFrom.value = addEventFrom.value.slice(0, 5);
    }
});
addEventTo.addEventListener("input", (e) => {
    addEventTo.value = addEventTo.value.replace(/[^0-9:]/g, "");
    if(addEventTo.value.length === 2) {
        addEventTo.value += ":";
    }
    if (addEventTo.value.length > 5){
        addEventTo.value = addEventTo.value.slice(0, 5);
    }
});
  
function addListner () {
    const  days = document.querySelectorAll(".day");
    days.forEach((day) => {
        day.addEventListener("click", (e) => {
            activeDay = Number(e.target.innerHTML);
            getActiveDay(e.target.innerHTML);
            updateEvents(Number(e.target.innerHTML));
            //updateEventStats(Number(e.target.innerHTML));
            days.forEach((day) => {
                day.classList.remove("active");
            });
            if(e.target.classList.contains("prev-date")) {
                prevMonth();
                setTimeout(() => {
                    const days = document.querySelectorAll(".day"); 
                    days.forEach((day) => {
                        if(!day.classList.contains("prev-date") && day.innerHTML === e.target.innerHTML){
                            day.classList.add("active");
                        }
                    });
                }, 100);
            } else if(e.target.classList.contains("next-date")) {
                nextMonth();
                setTimeout(() => {
                    const days = document.querySelectorAll(".day"); 
                    days.forEach((day) => {
                        if(!day.classList.contains("next-date") && day.innerHTML === e.target.innerHTML){
                            day.classList.add("active");
                        }
                    });
                }, 100);
            } else {
                e.target.classList.add("active");
            }
        });
    });
}

function getActiveDay(date) { 
    const day = new Date(year, month, date);
    const dayName = day.toString().split(" ")[0];
    if (dayName === "Mon") {
        eventDay.innerHTML = "Понедельник";
    } else if (dayName === "Tue") {
        eventDay.innerHTML = "Вторник";
    } else if (dayName === "Wed") {
        eventDay.innerHTML = "Среда";
    } else if (dayName === "Thu") {
        eventDay.innerHTML = "Четверг";
    } else if (dayName === "Fri") {
        eventDay.innerHTML = "Пятница";
    } else if (dayName === "Sat") {
        eventDay.innerHTML = "Суббота";
    } else if (dayName === "Sun") {
        eventDay.innerHTML = "Воскресенье";
    }
    eventDate.innerHTML = date + " " + months[month] + " " + year;
};
function updateEvents(date) { //events на выбранный день
    let events = "";
    eventsArr.forEach((event) => {
        if (
            date === event.day &&
            month + 1 === event.month &&
            year === event.year
        ){
            event.events.forEach((event) => {
                let iconClass = event.status === "done" ? "fas fa-check" : "fas fa-circle";
                events += `<div class="event">
                    <div class="title">
                      <i class="${iconClass}"></i>
                      <h3 class="event-title">${event.title}</h3>
                    </div>
                    <div class="event-time">
                        <span class="event-time">Время: ${event.time}</span>
                    </div>
                    <div class="event-time">
                        <span class="event-time">Человек: ${event.person}</span>
                    </div>
                    <div class="event-time">
                        <span class="event-time">Тип: ${event.type}</span>
                    </div>
                    <div class="event-time">
                        <span class="event-time">Описание: ${event.description}</span>
                    </div>
                </div>`;
            });
        }
    });
    if (events === "") {
        events = `<div class="no-event">
                <h3>Коммуникаций нет</h3>
            </div>`;
    }
    eventsContainer.innerHTML = events;
    saveEvents();
};
//добавление event
addEventSubmit.addEventListener("click", () => {
    const eventTitle = addEventTitle.value;
    const eventTimeFrom = addEventFrom.value;
    const eventTimeTo = addEventTo.value;
    const eventPerson = addEventPerson.value;
    const eventType = addEventType.value;
    const eventDescription = addEventDescription.value;

    if (eventTitle === "" || eventTimeFrom === "" || eventTimeTo === "") {
        alert("Заполните поля наименования и интервал времени!");
        return;
    }

    const timeFromArr = eventTimeFrom.split(":");
    const timeToArr = eventTimeTo.split(":");

    if (
        timeFromArr.length !== 2 ||
        timeToArr.length !== 2 ||
        timeFromArr[0] > 23 ||
        timeFromArr[1] > 59 ||
        timeToArr[0] > 23 ||
        timeToArr[1] > 59
    ){
        alert("Неправильный ввод!")
    }

    const newEvent = {
        title: eventTitle,
        //date: activeDay,///////////////////
        time: eventTimeFrom + " - " + eventTimeTo,
        person: eventPerson,
        type: eventType,
        description: eventDescription,
        status: "undone",
    };

    let eventAdded = false;
    if (eventsArr.length > 0) {
        eventsArr.forEach((item) => {
            if (
                item.day === activeDay &&
                item.month === month + 1 &&
                item.year === year
            ) {
                item.events.push(newEvent);
                eventAdded = true;
            };
        });
    };
    if (!eventAdded) {
        eventsArr.push({
            day: activeDay,
            month: month + 1,
            year: year,
            events: [newEvent],
        });
    }
    addEventContainer.classList.remove("active");
    addEventTitle.value = "";
    addEventFrom.value = "";
    addEventTo.value = "";
    addEventPerson.value = "";
    addEventType.value = "";
    addEventDescription.value = "";
    updateEvents(activeDay);
    updateEventStats(activeDay);
    const activeDayElem = document.querySelector(".day.active");
    if (!activeDayElem.classList.contains("event")){
        activeDayElem.classList.add("event");
    }
});

eventsContainer.addEventListener("click", (e) => {

    if (e.target.classList.contains("event")){
        const eventTitle = e.target.children[0].children[1].innerHTML;
        eventsArr.forEach((event) => {
            if (
                event.day === activeDay &&
                event.month === month + 1 &&
                event.year === year
            ){
                event.events.forEach((item, index) => {
                    if (item.title === eventTitle) {
                        if (confirm("Отметить как выполненное?")) {
                            event.events[index].status = "done";
                            // // Найти элемент с классом "event"
                            // var eventElement = document.querySelector('.events');

                            // // Изменить класс элемента на "event-done"
                            // eventElement.classList.add('event-done');
                            //здесь код
                            // Найти элемент с классом "event"
    // var eventElement = e.target;

    // // Создать элемент для галочки
    // var checkmarkElement = document.getElementsByName('i');
    // checkmarkElement.classList.add('fas', 'fa-check'); // Используем классы Font Awesome для галочки

    // // Добавить галочку внутрь элемента "event"
    // eventElement.appendChild(checkmarkElement);

    // // Удалить точку из элемента "event"
    // var dotElement = eventElement.querySelector('i');
    // if (dotElement) {
    //     eventElement.removeChild(dotElement);
    // }
                          } else {
                          }
                          if (confirm("Удалить запись?")) {
                            event.events.splice(index, 1);
                          } else {
                          }
                    }
                });
                if (event.events.length === 0) {
                    eventsArr.splice(eventsArr.indexOf(event), 1);
                    const activeDayElem = document.querySelector(".day.active");
                    if (activeDayElem.classList.contains("event")){
                        activeDayElem.classList.remove("event");
                    }
                }
            }
        });
        updateEvents(activeDay);
        //updateEventStats(activeDay);    
    }
});

function saveEvents(){
    localStorage.setItem("events" , JSON.stringify(eventsArr));
}
function getEvents(){
    if (localStorage.getItem("events" === null)){
        return;
    }
    eventsArr.push(... JSON.parse(localStorage.getItem("events")));
}


//const eventStats = document.querySelector(".event-stats");
//eventStats = eventsArr;
function updateEventStats(date) { //events на выбранный день
    let events = "";
    let events1 = "";
    let events2 = "";
    let eventsStats1 = "";
    let eventsStats2 = "";
    let countDay;
    let today = new Date();
    eventsArr.forEach((event) => {
        if (
            today.getDate() === event.day &&
      today.getMonth() + 1 === event.month &&
      today.getFullYear() === event.year
        ){
            let dateEvent = new Date(event.year, event.month - 1, event.day); // Создаем объект Date для выбранной даты события.
            let day = dateEvent.getDate().toString().padStart(2, '0'); // получаем число месяца, добавляя нули при необходимости
            let month = (dateEvent.getMonth() + 1).toString().padStart(2, '0'); // получаем номер месяца (нумерация начинается с 0), добавляя нули при необходимости
            let year = dateEvent.getFullYear(); // получаем год
            let formattedDate = `${day}.${month}.${year}`; // формируем конечную отформатированную дату
            event.events.forEach((event) => {
                events += `
                    <div class="reminders-event-today">
                    <span class="reminders-event-today-0">${formattedDate}</span>
                    <span class="reminders-event-today-1">${event.title}</span>
                    <span class="reminders-event-today-2">Сегодня</span>
                </div>`;
                eventsStats1 += `<div>
                    <span class="events-stats-events-group-1">${formattedDate}</span>
                    <span class="events-stats-events-group-2">${event.title}</span>
                    <span class="events-stats-events-group-3">${event.time}</span>
                    <span class="events-stats-events-group-4">${event.type}</span>
                    <span class="events-stats-events-group-5">${event.person}</span>
                    <span class="events-stats-events-group-6">${event.description}</span><div>
                `;
            });
        }
        if (
            (today.getDate() < event.day &&
            today.getMonth() + 1 <= event.month &&
            today.getFullYear() <= event.year)
        ){
            let dateEvent = new Date(event.year, event.month - 1, event.day); // Создаем объект Date для выбранной даты события.
            let timeDiff = Math.abs(dateEvent.getTime() - today.getTime());
            countDay = Math.ceil(timeDiff / (1000 * 3600 * 24)); // Обновляем countDay с вычисленным значением количества дней.

            let day = dateEvent.getDate().toString().padStart(2, '0'); // получаем число месяца, добавляя нули при необходимости
            let month = (dateEvent.getMonth() + 1).toString().padStart(2, '0'); // получаем номер месяца (нумерация начинается с 0), добавляя нули при необходимости
            let year = dateEvent.getFullYear(); // получаем год
            let formattedDate = `${day}.${month}.${year}`; // формируем конечную отформатированную дату
            event.events.forEach((event) => {   
                events1 += `<div class="reminders-event-days">
                    <span class="reminders-event-days-0">${formattedDate}</span>
                    <span class="reminders-event-days-1">${event.title}</span>
                    <span class="reminders-event-days-2">${countDay}</span>
                    </div>`;
                eventsStats1 += `<div>
                    <span class="events-stats-events-group-1">${formattedDate}</span>
                    <span class="events-stats-events-group-2">${event.title}</span>
                    <span class="events-stats-events-group-3">${event.time}</span>
                    <span class="events-stats-events-group-4">${event.type}</span>
                    <span class="events-stats-events-group-5">${event.person}</span>
                    <span class="events-stats-events-group-6">${event.description}</span></div>
                `;
            });
        }
        if (
            (year + 1 === event.year)
        ){
            
            let dateEvent = new Date(event.year, event.month - 1, event.day); // Создаем объект Date для выбранной даты события.
            let timeDiff = Math.abs(dateEvent.getTime() - today.getTime());
            countDay = Math.ceil(timeDiff / (1000 * 3600 * 24)); // Обновляем countDay с вычисленным значением количества дней.

            let day = dateEvent.getDate().toString().padStart(2, '0'); // получаем число месяца, добавляя нули при необходимости
            let month = (dateEvent.getMonth() + 1).toString().padStart(2, '0'); // получаем номер месяца (нумерация начинается с 0), добавляя нули при необходимости
            let year = dateEvent.getFullYear(); // получаем год
            let formattedDate = `${day}.${month}.${year}`; // формируем конечную отформатированную дату
            event.events.forEach((event) => {
                events2 += `
                    <div class="reminders-event-year">
                    <span class="reminders-event-year-0">${formattedDate}</span>
                    <span class="reminders-event-year-1">${event.title}</span>
                <span class="reminders-event-year-2">${countDay}</span>
                </div>`;
                eventsStats1 += `<div>
                    <span class="events-stats-events-group-1">${formattedDate}</span>
                    <span class="events-stats-events-group-2">${event.title}</span>
                    <span class="events-stats-events-group-3">${event.time}</span>
                    <span class="events-stats-events-group-4">${event.type}</span>
                    <span class="events-stats-events-group-5">${event.person}</span>
                    <span class="events-stats-events-group-6">${event.description}</span></div>
                `;
            });
        }

        if (
            ("done" === event.status)
        ){
            let dateEvent = new Date(event.year, event.month - 1, event.day); // Создаем объект Date для выбранной даты события.
            let day = dateEvent.getDate().toString().padStart(2, '0'); // получаем число месяца, добавляя нули при необходимости
            let month = (dateEvent.getMonth() + 1).toString().padStart(2, '0'); // получаем номер месяца (нумерация начинается с 0), добавляя нули при необходимости
            let year = dateEvent.getFullYear(); // получаем год
            let formattedDate = `${day}.${month}.${year}`; // формируем конечную отформатированную дату
            event.events.forEach((event) => {
                eventsStats2 += `<div>
                    <span class="events-stats-events-group-1">${formattedDate}</span>
                    <span class="events-stats-events-group-2">${event.title}</span>
                    <span class="events-stats-events-group-3">${event.time}</span>
                    <span class="events-stats-events-group-4">${event.type}</span>
                    <span class="events-stats-events-group-5">${event.person}</span>
                    <span class="events-stats-events-group-6">${event.description}</span><div>
                `;
            });
        }
    });

    eventStats.innerHTML = events;
    eventStats1.innerHTML = events1;
    eventStats2.innerHTML = events2;
    //eventStats3.innerHTML = eventsStats1;
    //eventStats4.innerHTML = eventsStats2;
};


document.getElementById('calendarBtn').addEventListener('click', function() {
    this.classList.add('btn-active');
    document.getElementById('statsBtn').classList.remove('btn-active');
    document.getElementById('remindersBtn').classList.remove('btn-active');
   // document.getElementById('loginBtn').classList.remove('btn-active');
    document.querySelector('.container').classList.add('active');
  document.querySelector('.statistic').classList.remove('active');
  document.querySelector('.reminders').classList.remove('active');
  //document.querySelector('.login').classList.remove('active');
  });
  
  document.getElementById('statsBtn').addEventListener('click', function() {
    this.classList.add('btn-active');
    document.getElementById('calendarBtn').classList.remove('btn-active');
    document.getElementById('remindersBtn').classList.remove('btn-active');
    //document.getElementById('loginBtn').classList.remove('btn-active');
    document.querySelector('.statistic').classList.add('active');
  document.querySelector('.container').classList.remove('active');
  document.querySelector('.reminders').classList.remove('active');
  //document.querySelector('.login').classList.remove('active');
  });
  
  document.getElementById('remindersBtn').addEventListener('click', function() {
    this.classList.add('btn-active');
    document.getElementById('calendarBtn').classList.remove('btn-active');
    document.getElementById('statsBtn').classList.remove('btn-active');
    //document.getElementById('loginBtn').classList.remove('btn-active');
    document.querySelector('.reminders').classList.add('active');
  document.querySelector('.container').classList.remove('active');
  document.querySelector('.statistic').classList.remove('active');
  //document.querySelector('.login').classList.remove('active');
  });

//   document.getElementById('loginBtn').addEventListener('click', function() {
//     this.classList.add('btn-active');
//     document.getElementById('calendarBtn').classList.remove('btn-active');
//     document.getElementById('statsBtn').classList.remove('btn-active');
//     document.getElementById('remindersBtn').classList.remove('btn-active');
//     document.querySelector('.login').classList.add('active');
//   document.querySelector('.container').classList.remove('active');
//   document.querySelector('.statistic').classList.remove('active');
//   document.querySelector('.reminders').classList.remove('active');
//   });

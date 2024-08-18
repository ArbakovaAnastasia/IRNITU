<?php


require_once "../../../EntryPoints/ISTU/Courses/AI/ClipsScripts/ClipsEngine.php";

$data = json_decode($_POST["dialogflow"]);
$user = $_POST["username"];
$token = $_POST["token"];

class Format_DateTime{
    public  $date,
            $minHour,
            $maxHour,
            $minMinute,
            $maxMinute,
            $minSecond,
            $maxSecond,
            $minTime,
            $maxTime,
            $id_weekday;
    function __construct(   $date, $minHour, $maxHour, $minMinute,
                            $maxMinute, $minSecond, $maxSecond, $minTime, $maxTime, $weekDay) {
        $this->date         = $date;
        $this->id_weekday      = $weekDay;
        $this->minTime      = $minTime;
        $this->maxTime      = $maxTime;
        $this->minHour      = $minHour;
        $this->maxHour      = $maxHour;
        $this->minMinute    = $minMinute;
        $this->maxMinute    = $maxMinute;
        $this->minSecond    = $minSecond;
        $this->maxSecond    = $maxSecond;
    }

}

class User_DateTime{
    public  $id_person,
            $minDate,
            $maxDate,
            $minHour,
            $maxHour,
            $minMinute,
            $maxMinute,
            $minSecond,
            $maxSecond,
            $id_weekday;
    function __construct(   $id_person, $minDate, $maxDate, $minHour, $maxHour, 
                            $minMinute,$maxMinute, $minSecond, $maxSecond, $weekDay) {
        $this->id_person    = $id_person;
        $this->minDate      = $minDate;
        $this->maxDate      = $maxDate;
        $this->id_weekday      = $weekDay;
        $this->minHour      = $minHour;
        $this->maxHour      = $maxHour;
        $this->minMinute    = $minMinute;
        $this->maxMinute    = $maxMinute;
        $this->minSecond    = $minSecond;
        $this->maxSecond    = $maxSecond;
    }
}

function get_DefaultDateTime($interval = 7) {
    $date = strtotime((new DateTime())->format('Y-m-d H:i:s'));
    $response = array();
    while($interval > 0){
        $interval -= 1;
        $date += 60*60*24;
        $dateFormated = new DateTime("@" . $date);
        $responseDateTime = new Format_DateTime($dateFormated->format("Y-m-d"),
                                                0, 24, 0, 0, 0, 0,
                                                '00:00:00',
                                                '24:00:00',
                                                (date('w', $date) == 0 ? 7 : date('w', $date)));
        $response[] = $responseDateTime;
    }
    return $response;
}

function create_UserDateTime($user_name, $user_id, $default_dateTime, $default_user_dateTime, $token){
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 10);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array('Authorization: Bearer '. $token, 'Content-Type: application/json'));
    $dateStart = new DateTime("@" . strtotime((new DateTime())->format('Y-m-d H:i:s')) + 60*60*24);
    $dateEnd = new DateTime("@" . strtotime((new DateTime())->format('Y-m-d H:i:s')) + 60*60*24*8);

    curl_setopt_array($curl, array(
        CURLOPT_URL => 'https://www.googleapis.com/calendar/v3/calendars/' . $user_name . '/events?timeMax=' . str_replace(':', '%3A', $dateStart->format('Y-m-d') . 'T00:00:00Z') . '&timeMin=' . str_replace(':', '%3A', $dateEnd->format('Y-m-d') . 'T00:00:00Z') .'&access_token=' . $token,
        // CURLOPT_URL => 'https://www.googleapis.com/calendar/v3/calendars/' . $user_name . '/events?timeMax=' . str_replace(':', '%3A', $dateStart->format('Y-m-d') . 'T00:00:00Z') . '&timeMin=' . str_replace(':', '%3A', $dateEnd->format('Y-m-d') . 'T00:00:00Z') .'&access_token=' . $token,
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_ENCODING => '',
        CURLOPT_MAXREDIRS => 10,
        CURLOPT_TIMEOUT => 0,
        CURLOPT_FOLLOWLOCATION => true,
        CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
        CURLOPT_CUSTOMREQUEST => 'GET',
    ));

    $curl_response = json_decode(curl_exec($curl));
    curl_close($curl);

    $user_busyTime_curl = $curl_response->items;

    for($k = 0; $k < count($user_busyTime_curl); $k++){
        if($user_busyTime_curl[$k]->start->timeZone != 'UTC'){
            $start = new DateTime("@" . strtotime((new DateTime($user_busyTime_curl[$k]->start->dateTime))->format("Y-m-d H:i:s")) + 60*60*8);
            $start = str_replace(' ', 'T', $start->format("Y-m-d H:i:s").'Z');

            $end = new DateTime("@" . strtotime((new DateTime($user_busyTime_curl[$k]->end->dateTime))->format("Y-m-d H:i:s")) + 60*60*8);
            $end = str_replace(' ', 'T', $end->format("Y-m-d H:i:s").'Z');

            $user_busyTime_curl[$k]->start->dateTime = $start;
            $user_busyTime_curl[$k]->end->dateTime = $end;
        }
    }

    
    for($i = 0; $i < count($default_dateTime); $i++){
        for($k = 0; $k < count($default_user_dateTime); $k++){

            $obj = '{
                "start": {
                    "dateTime": ""
                },
                "end": {
                    "dateTime": ""
                }
            }';

            $obj = json_decode($obj);

            if($default_user_dateTime[$k]->weekdays == "all"){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "workdays" && $default_dateTime[$i]->id_weekday < 6){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "1" && $default_dateTime[$i]->id_weekday == 1){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "2" && $default_dateTime[$i]->id_weekday == 2){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "3" && $default_dateTime[$i]->id_weekday == 3){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "4" && $default_dateTime[$i]->id_weekday == 4){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "5" && $default_dateTime[$i]->id_weekday == 5){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "6" && $default_dateTime[$i]->id_weekday == 6){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $busy_time[] = $obj;
            }else if($default_user_dateTime[$k]->weekdays == "7" && $default_dateTime[$i]->id_weekday == 7){
                $obj->start->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->minTime . 'Z';
                $obj->end->dateTime = $default_dateTime[$i]->date . 'T' . $default_user_dateTime[$k]->maxTime . 'Z';
                $user_busyTime_curl[] = $obj;
            }
        }
    }

    usort($user_busyTime_curl, function($a, $b) {return strcmp($a->start->dateTime, $b->start->dateTime);});

    $user_busyTime = array();

    for($k = 0; $k < count($user_busyTime_curl); $k++){
        $timeStart_curl = (new DateTime($user_busyTime_curl[$k]->start->dateTime))->format('Y-m-d H:i:s');
        if ((new DateTime($user_busyTime_curl[$k]->end->dateTime))->format('Y-m-d') > (new DateTime($user_busyTime_curl[$k]->start->dateTime))->format('Y-m-d')){
            $timeEnd_curl = (new DateTime($user_busyTime_curl[$k]->start->dateTime))->format('Y-m-d') . 'T' . '24' . ':' . '00' . ':' . '00' . 'Z';
        }else
            $timeEnd_curl = (new DateTime($user_busyTime_curl[$k]->end->dateTime))->format('Y-m-d H:i:s');

        if($k == 0){
            $user_busyTime[] = $user_busyTime_curl[$k];
        }else{
            for($i = 0; $i < count($user_busyTime); $i++){ 
                $timeStart = (new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d H:i:s');
                if ((new DateTime($user_busyTime[$i]->end->dateTime))->format('Y-m-d') > (new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d'))
                    $timeEnd = (new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d') . 'T' . '24' . ':' . '00' . ':' . '00' . 'Z';
                else
                    $timeEnd = (new DateTime($user_busyTime[$i]->end->dateTime))->format('Y-m-d H:i:s');
                if ($timeStart_curl <= $timeStart && $timeEnd_curl >= $timeEnd){
                    $user_busyTime[$i]->start->dateTime = $user_busyTime_curl[$k]->start->dateTime;
                    if((new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d') < (new DateTime($user_busyTime_curl[$k]->end->dateTime))->format('Y-m-d'))
                        $user_busyTime[$i]->end->dateTime = (new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d') . 'T' . "24:00:00Z";
                    else
                        $user_busyTime[$i]->end->dateTime = $user_busyTime_curl[$k]->end->dateTime;
                    break 1;
                }else if($timeStart_curl >= $timeStart && $timeEnd_curl >= $timeEnd && $timeStart_curl <= $timeEnd){
                    if((new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d') < (new DateTime($user_busyTime_curl[$k]->end->dateTime))->format('Y-m-d'))
                        $user_busyTime[$i]->end->dateTime = (new DateTime($user_busyTime[$i]->start->dateTime))->format('Y-m-d') . 'T' . "24:00:00Z";
                    else
                        $user_busyTime[$i]->end->dateTime = $user_busyTime_curl[$k]->end->dateTime;
                    break 1;
                }else if($timeStart_curl <= $timeStart && $timeEnd_curl <= $timeEnd && $timeEnd_curl >= $timeStart){
                    $user_busyTime[$i]->start->dateTime = $user_busyTime_curl[$k]->start->dateTime;
                    break 1;
                }else if($timeStart_curl >= $timeStart && $timeEnd_curl <= $timeEnd){
                    break 1;
                }else if($i + 1 == count($user_busyTime)){
                        $user_busyTime[] = $user_busyTime_curl[$k];
                    }
            }
        }
        
    }


    $free_time = array();

    for($i = 0; $i < count($default_dateTime); $i++){
        $busy_time = array();

        $default_startDateTime = $default_dateTime[$i]->date . ' ' . $default_dateTime[$i]->minHour . '00' . '00';
        $default_endDateTime = $default_dateTime[$i]->date . ' ' . $default_dateTime[$i]->maxHour . '00' . '00';
        

        for($k = 0; $k < count($user_busyTime); $k++){
            $datetimeStart = new DateTime($user_busyTime[$k]->start->dateTime);
            $datetimeEnd = new DateTime($user_busyTime[$k]->end->dateTime);

            $startDateTime = $datetimeStart->format('Y-m-d H:i:s');
            $endDateTime = $datetimeEnd->format('Y-m-d H:i:s');

            $busyDate = (new DateTime($user_busyTime[$k]->start->dateTime))->format('Y-m-d');
            if( $default_dateTime[$i]->date == $busyDate &&
                !($default_startDateTime > $startDateTime && $default_startDateTime > $endDateTime) &&
                !($default_endDateTime < $startDateTime && $default_endDateTime < $endDateTime) ){
                    $busy_time[] = $user_busyTime[$k];
            }
        }

        if(count($busy_time) == 0){
            $user_dateTime = new User_DateTime( $user_id, $default_dateTime[$i]->date, $default_dateTime[$i]->date,
                                                $default_dateTime[$i]->minHour, $default_dateTime[$i]->maxHour, 
                                                $default_dateTime[$i]->minMinute, $default_dateTime[$i]->maxMinute,
                                                $default_dateTime[$i]->minSecond, $default_dateTime[$i]->maxSecond,
                                                $default_dateTime[$i]->id_weekday);
            $free_time[] = $user_dateTime;
        }else{
            $prev_endTime = new DateTime();
            for($k = 0; $k < count($busy_time); $k++){
                $datetimeStart = new DateTime($busy_time[$k]->start->dateTime);
                $datetimeEnd = new DateTime($busy_time[$k]->end->dateTime);
                if($k == 0){
                    if($datetimeStart->format('H:i:s') > $default_dateTime[$i]->minTime){
                        $user_dateTime = new User_DateTime( $user_id, $default_dateTime[$i]->date, $default_dateTime[$i]->date,
                                                            $default_dateTime[$i]->minHour, intval($datetimeStart->format('H')), 
                                                            $default_dateTime[$i]->minMinute, intval($datetimeStart->format('i')),
                                                            $default_dateTime[$i]->minSecond, intval($datetimeStart->format('s')),
                                                            $default_dateTime[$i]->id_weekday);
                        $free_time[] = $user_dateTime;
                        if($default_dateTime[$i]->date == '2024-01-05')
                            echo'-p-----------';
                    }
                    $prev_endTime = $datetimeEnd;
                    
                }else{
                    $user_dateTime = new User_DateTime(     $user_id, $default_dateTime[$i]->date, $default_dateTime[$i]->date,
                                                            intval($prev_endTime->format('H')), intval($datetimeStart->format('H')), 
                                                            intval($prev_endTime->format('i')), intval($datetimeStart->format('i')),
                                                            intval($prev_endTime->format('s')), intval($datetimeStart->format('s')),
                                                            $default_dateTime[$i]->id_weekday);
                    $free_time[] = $user_dateTime;
                    $prev_endTime = $datetimeEnd;
                }

                
                if($k + 1 == count($busy_time)){
                    if(($datetimeEnd->format('H:i:s') == '00:00:00' ? '24:00:00' : $datetimeEnd->format('H:i:s')) < $default_dateTime[$i]->maxTime){
                        $user_dateTime = new User_DateTime( $user_id, $default_dateTime[$i]->date, $default_dateTime[$i]->date,
                                                            intval($datetimeEnd->format('H')), $default_dateTime[$i]->maxHour, 
                                                            intval($datetimeEnd->format('i')), $default_dateTime[$i]->maxMinute,
                                                            intval($datetimeEnd->format('s')), $default_dateTime[$i]->maxSecond,
                                                            $default_dateTime[$i]->id_weekday);
                        $free_time[] = $user_dateTime;
                    }
                }
            }
        }
    }

    return $free_time;


}

$default_busyTime_users = '[
    {"vadim": [
        { 
            "name": "sleep",
            "weekdays":"all",
            "minHour": 0,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 8,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"00:00:00",
            "maxTime":"08:00:00"
        },
        { 
            "name": "work",
            "weekdays": "workdays",
            "minHour": 8,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 17,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"08:00:00",
            "maxTime":"17:00:00"
        },
        { 
            "name": "preference",
            "weekdays": "5",
            "minHour": 18,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 23,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"18:00:00",
            "maxTime":"23:00:00"
        }
    ]},
    {"anton": [
        {
            "name": "sleep",
            "weekdays":"all",
            "minHour": 0,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 8,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"00:00:00",
            "maxTime":"08:00:00"
        },
        {
            "name": "work",
            "weekdays": "workdays",
            "minHour": 8,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 15,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"08:00:00",
            "maxTime":"15:00:00"
        },
        {
            "name": "preference",
            "weekdays": "3",
            "minHour": 18,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 21,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"18:00:00",
            "maxTime":"21:00:00"
        }
    ]},
    {"ananastasiya": [
        {
            "name": "sleep",
            "weekdays":"all",
            "minHour": 0,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 8,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"00:00:00",
            "maxTime":"08:00:00"
        },
        {
            "name": "work",
            "weekdays": "workdays",
            "minHour": 8,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 17,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"08:00:00",
            "maxTime":"17:00:00"
        },
        {
            "name": "preference",
            "weekdays": "5",
            "minHour": 19,
            "minMinute": 0,
            "minSecond": 0,
            "maxHour": 23,
            "maxMinute": 0,
            "maxSecond": 0,
            "minTime":"19:00:00",
            "maxTime":"23:00:00"
        }
    ]}
]';




function getContextByName($contexts, $contextName)
{
    foreach($contexts as $context) {
        if (strpos($context->name, $contextName) !== false) {
            return $context;
        }
    }

    return null;
}
$Context = getContextByName($data->queryResult->outputContexts, "dialog");

$date='';
$event='';
$person='';
$check_event = true;
$check_person = true;
$check_day_of_week = true;
$check_time = true;

function askForParameter($text, $context_name) {
    $response = 
    [
        "fulfillmentText"=> $text,
        "fulfilmentMessage" => 
            [
                [
                    "text" => $text
                ]
                ],
        'outputContexts'=> [
            [
                'name' => "projects/calendar-uu9c/agent/sessions/bfa256e8-d0b8-c76c-3288-adc60bb1289f/contexts/$context_name",
                'lifespanCount' => 5, // Установите желаемую продолжительность жизни контекста
                'text' => $text,
            ]
        ]
    ];

    echo json_encode($response);
    die();
}

if ($Context->parameters->day_of_week)
{
    $date=$Context->parameters->day_of_week;

}
else {
    $check_day_of_week = false;
    // $text = 'Когда хотели бы принять участие в мероприятии?';
    // askForParameter($text);
}
// echo($date);

if ($Context->parameters->event)
{
    $event=$Context->parameters->event;

}
else {
    $check_event = false;
    // $text = 'Какое мероприятие вас интересует?';
    // askForParameter($text);
}
// echo($event);
if ($Context->parameters->person)
{
    $person=$Context->parameters->person;

}
else {
    $check_person = false;
    // $text = 'С кем хотели бы принять участие в мероприятии?';
    // askForParameter($text);
}
if ($Context->parameters->time)
{
    $time=$Context->parameters->time;

}
else {
    $check_time = false;
    // $text = 'С кем хотели бы принять участие в мероприятии?';
    // askForParameter($text);
}

if (($check_event == false) && ($check_person == true) && ($check_day_of_week == true) && $check_time == true){
    $text = 'Какое мероприятие вас интересует?';
    askForParameter($text, 'ask_event_parameter');

}
else if (($check_event == true) && ($check_person == false) && ($check_day_of_week == true && $check_time == true)){
    $text = 'С кем хотели бы принять участие в мероприятии?';
    askForParameter($text, 'ask_person_parameter');
}
else if ($check_event == true && $check_person == true && $check_day_of_week == false && $check_time == true){
    $text = 'Когда хотели бы принять участие в мероприятии?';
    askForParameter($text, 'ask_day_of_week_parameter');
}
else if ($check_event == true && $check_person == true && $check_day_of_week == true && $check_time == false){
    $text = 'В какое время вам это интересно?';
    askForParameter($text, 'ask_time_parameter');
}


$default_busyTime_users = json_decode($default_busyTime_users);


$default_busyTime_users[0]->vadim = array_filter($default_busyTime_users[0]->vadim, function($a){global $event; return $a->name != $event;});
$default_busyTime_users[1]->anton = array_filter($default_busyTime_users[1]->anton, function($a){global $event; return $a->name != $event;});
$default_busyTime_users[2]->$ananastasiya = array_filter($default_busyTime_users[2]->ananastasiya, function($a){global $event; return $a->name != $event;});

$vadim = create_UserDateTime('mandanov2002@gmail.com', 1, get_DefaultDateTime(), $default_busyTime_users[0]->vadim, $token);

$anton = create_UserDateTime('darkraven653@gmail.com', 2, get_DefaultDateTime(), $default_busyTime_users[1]->anton, $token);
// $jsonString = json_encode($anton);

$ananastasiya = create_UserDateTime('arbakova.nastya@gmail.com', 3, get_DefaultDateTime(), $default_busyTime_users[2]->ananastasiya, $token);

$freeTimes = array_merge($vadim, $anton, $ananastasiya);

// $freeTimes = $vadim;
$jsonString = json_encode($freeTimes);
$freeTimes = json_decode($jsonString, true);


if (stripos($time, 'вечер') !== false){
    $minHourTime = 17;
    $minMinuteTime = 0;
    $minSecondTime = 0;
    $maxHourTime = 24;
    $maxMinuteTime = 0;
    $maxSecondTime = 0;
}
elseif (stripos($time, 'утр') !== false){
    $minHourTime = 7;
    $minMinuteTime = 0;
    $minSecondTime = 0;
    $maxHourTime = 13;
    $maxMinuteTime = 0;
    $maxSecondTime = 0;
}
elseif (stripos($time, 'днем') !== false){
    $minHourTime = 13;
    $minMinuteTime = 0;
    $minSecondTime = 0;
    $maxHourTime = 17;
    $maxMinuteTime = 0;
    $maxSecondTime = 0;
};




if (stripos($date, 'понедельник') !== false){
    $requestedDayOfWeek = 1;
}
elseif (stripos($date, 'вторник') !== false){
    $requestedDayOfWeek = 2;
}
elseif (stripos($date, 'сред') !== false){
    $requestedDayOfWeek = 3;
}
elseif (stripos($date, 'четверг') !== false){
    $requestedDayOfWeek = 4;
}
elseif (stripos($date, 'пятниц') !== false){
    $requestedDayOfWeek = 5;
}
elseif (stripos($date, 'суббот') !== false){
    $requestedDayOfWeek = 6;
}
elseif (stripos($date, 'воскресенье') !== false){
    $requestedDayOfWeek = 0;
}

function getNextDateForDayOfWeek($dayOfWeek) {
    // Получаем текущую дату
    $currentDate = new DateTime();

    // Получаем текущий день недели
    $currentDayOfWeek = $currentDate->format('w');

    // Вычисляем разницу между текущим днем недели и запрашиваемым
    $daysToAdd = ($dayOfWeek - $currentDayOfWeek + 7) % 7;

    // Добавляем дни к текущей дате
    $currentDate->add(new DateInterval('P' . $daysToAdd . 'D'));

    // Возвращаем результат в виде строки
    return $currentDate->format('Y-m-d');
}
// $date_of_event = date('Y-m-d', strtotime("+$daysToAdd days", strtotime(getNextDateForDayOfWeek($requestedDayOfWeek)))); 
// $date_of_event = date('2023-12-05');
// print_r(stripos($event, 'о'));
$date_of_event = getNextDateForDayOfWeek($requestedDayOfWeek);

function containsKeyword($sentence) {
    $keywords = ["бар", "гор", "матч"];

    foreach ($keywords as $keyword) {
        if (stripos($sentence, $keyword) !== false) {
            return true;
        }
    }

    return false;
}

//проверка события
if (stripos($event, 'гор') !== false){
    $eventClips = 'поход';
}
elseif (stripos($event, 'оход') !== false){
    $eventClips = 'поход';
}
elseif (stripos($event, 'бар') !== false){
    $eventClips = 'бар';
}
elseif (stripos($event, 'матч') !== false){
    $eventClips = 'матч';
}
elseif (stripos($event, 'ино') !== false){
    $eventClips = 'кино';
}

//проверка группы людей
if (stripos($person, 'друз') !== false){
    $personClips = 'друзья';
}
elseif (stripos($person, 'коллег') !== false){
    $personClips = 'коллега';
}
elseif (stripos($person, 'начальник') !== false){
    $personClips = 'начальник';
}



$events = [
    [
        'id' => 1,
        'name' => 'кино',
        'hour' => 2,
        'minute' => 30,
        'second' => 0
    ],
    [
        'id' => 2,
        'name' => 'матч',
        'hour' => 4,
        'minute' => 0,
        'second' => 0
    ],
    [
        'id' => 3,
        'name' => 'бар',
        'hour' => 5,
        'minute' => 30,
        'second' => 0
    ],
    [
        'id' => 4,
        'name' => 'поход',
        'hour' => 11,
        'minute' => 0,
        'second' => 0
    ]
];

//заглушка вместо ответа от API
// $freeTimes = [
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-01',
//         'maxDate' => '2023-12-01',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 5
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-02',
//         'maxDate' => '2023-12-02',
//         'minHour' => 10,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 6
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-03',
//         'maxDate' => '2023-12-03',
//         'minHour' => 10,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 7
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-04',
//         'maxDate' => '2023-12-04',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 1
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-05',
//         'maxDate' => '2023-12-05',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 2
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-06',
//         'maxDate' => '2023-12-06',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 3
//     ],
//     [
//         'id_person' => 1,
//         'minDate' => '2023-12-07',
//         'maxDate' => '2023-12-07',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 4
//     ],
//     // Добавьте остальные записи для других людей
//     // ...
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-01',
//         'maxDate' => '2023-12-01',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 5
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-02',
//         'maxDate' => '2023-12-02',
//         'minHour' => 10,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 6
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-03',
//         'maxDate' => '2023-12-03',
//         'minHour' => 10,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 7
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-04',
//         'maxDate' => '2023-12-04',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 1
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-05',
//         'maxDate' => '2023-12-05',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 2
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-06',
//         'maxDate' => '2023-12-06',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 3
//     ],
//     [
//         'id_person' => 2,
//         'minDate' => '2023-12-07',
//         'maxDate' => '2023-12-07',
//         'minHour' => 17,
//         'minMinute' => 0,
//         'minSecond' => 0,
//         'maxHour' => 24,
//         'maxMinute' => 0,
//         'maxSecond' => 0,
//         'id_weekday' => 4
//     ],
//     // ...
// ];

$persons = [
    ['id' => 1, 'name' => 'я'],
    ['id' => 2, 'name' => 'Антон'],
    ['id' => 3, 'name' => 'Настя']
];


$personGroups = [
    ['id' => 1, 'group_name' => 'я', 'person_name' => 'я'],
    ['id' => 2, 'group_name' => 'друзья', 'person_name' => 'я'],
    ['id' => 3, 'group_name' => 'друзья', 'person_name' => 'Антон'],
    ['id' => 5, 'group_name' => 'коллеги', 'person_name' => 'я'],
    ['id' => 6, 'group_name' => 'коллеги', 'person_name' => 'Антон'],
    ['id' => 7, 'group_name' => 'коллеги', 'person_name' => 'Настя'],
    ['id' => 8, 'group_name' => 'Антон', 'person_name' => 'я'],
    ['id' => 9, 'group_name' => 'Антон', 'person_name' => 'Антон'],
    ['id' => 10, 'group_name' => 'Настя', 'person_name' => 'я'],
    ['id' => 11, 'group_name' => 'Настя', 'person_name' => 'Настя']
];

// $date_of_event = '2023-12-05';

$clipsString="";

foreach ($persons as $person) {
    $clipsString .= "(person (id {$person['id']}) (name \"{$person['name']}\"))\n";
}

foreach ($personGroups as $personGroup) {
    $clipsString .= "(personGroup (id {$personGroup['id']}) (group_name  \"{$personGroup['group_name']}\") (person_name  \"{$personGroup['person_name']}\"))\n";
}

foreach ($events as $event) {
    $clipsString .= "(event (id {$event['id']}) (name  \"{$event['name']}\") (hour  {$event['hour']}) (minute  {$event['minute']}) (second  {$event['second']}))\n";
}

foreach ($freeTimes as $freeTime) {
    
    $clipsString .= "(freeTime (id_person {$freeTime['id_person']}) (minDate  \"{$freeTime['minDate']}\") (maxDate  \"{$freeTime['maxDate']}\") (minHour  {$freeTime['minHour']}) (minMinute  {$freeTime['minMinute']}) (minSecond  {$freeTime['minSecond']}) (maxHour  {$freeTime['maxHour']}) (maxMinute  {$freeTime['maxMinute']}) (maxSecond  {$freeTime['maxSecond']}) (id_weekday  {$freeTime['id_weekday']}))\n";
}

$clipsString .= "(eventRequest (name \"$eventClips\") (date \"$date_of_event\") (group_name \"$personClips\") (minHour $minHourTime)  (minMinute $minMinuteTime)  (minSecond $minSecondTime) (maxHour $maxHourTime)  (maxMinute $maxMinuteTime)  (maxSecond $maxSecondTime))";
// print_r($clipsString);

$deffacts="(deffacts dialogflow_data ".$clipsString." )";

 // Запуск CLIPS с исходными данными
 $result = RunClips($user, $deffacts);

 $pattern = '/answer \(text "([^\"]+)"/';

 // Выполняем поиск
 if (preg_match($pattern, $result['facts'], $matches)) {
     // $matches[1] содержит текст внутри кавычек
     $parse = $matches[1];
    //  echo $parse;
 } else {
    //  echo "Совпадения не найдены";
 }

$response = 
[
    "fulfillmentText"=> $parse,
    "fulfilmentMessage" => 
        [
            [
                "text" => [$parse, $result, $freeTimes]
            ]
        ],
    'statusCode'=> 200,

    'outputContexts'=> [$Context]
];
echo json_encode($response);
die();

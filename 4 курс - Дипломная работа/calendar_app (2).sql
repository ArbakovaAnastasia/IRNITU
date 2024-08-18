-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1
-- Время создания: Май 14 2024 г., 16:56
-- Версия сервера: 10.4.32-MariaDB
-- Версия PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `calendar_app`
--

-- --------------------------------------------------------

--
-- Структура таблицы `event`
--

CREATE TABLE `event` (
  `id` int(11) NOT NULL,
  `date` date NOT NULL,
  `time` varchar(255) NOT NULL,
  `title` varchar(255) NOT NULL,
  `person` varchar(255) NOT NULL,
  `description` varchar(512) NOT NULL,
  `status` tinyint(1) NOT NULL,
  `type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Дамп данных таблицы `event`
--

INSERT INTO `event` (`id`, `date`, `time`, `title`, `person`, `description`, `status`, `type`) VALUES
(56, '2024-04-27', '00:00 - 23:59', 'День рождения Арины', 'Арина', '', 1, 1),
(57, '2024-05-02', '12:00 - 14:00', 'Отправить документы', '', 'в деканат', 0, 2),
(58, '2024-05-06', '12:00 - 18:00', 'Сходить в гости', '', '', 1, 2),
(59, '2024-05-11', '14:00 - 15:00', 'Встретить друга', '', '', 1, 2),
(60, '2024-05-14', '13:00 - 16:00', 'Позвонить в доставку', '', '', 0, 1),
(61, '2024-05-17', '08:00 - 13:00', 'Отправить отчет', 'Евгений Александрович', '', 0, 2),
(63, '2024-05-22', '13:00 - 15:00', 'Диплом отправить', '', '', 0, 2),
(64, '2024-05-31', '14:00 - 16:00', 'Позвонить на работу', '', '', 0, 1),
(65, '2024-06-12', '13:00 - 20:00', 'День рождения Марины', '', '', 0, 2),
(66, '2024-06-25', '08:00 - 20:00', 'Защита диплома', '', '', 0, 2),
(69, '2024-06-26', '14:00 - 16:00', 'Позвонить в деканат', 'Ольга Игоревна', 'По поводу диплома', 0, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `event_type`
--

CREATE TABLE `event_type` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Дамп данных таблицы `event_type`
--

INSERT INTO `event_type` (`id`, `name`) VALUES
(1, 'Звонок'),
(2, 'Личная встреча'),
(3, 'Видеозвонок'),
(4, 'Видеоконференция');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `event`
--
ALTER TABLE `event`
  ADD PRIMARY KEY (`id`),
  ADD KEY `type` (`type`);

--
-- Индексы таблицы `event_type`
--
ALTER TABLE `event_type`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `event`
--
ALTER TABLE `event`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=70;

--
-- AUTO_INCREMENT для таблицы `event_type`
--
ALTER TABLE `event_type`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `event`
--
ALTER TABLE `event`
  ADD CONSTRAINT `event_ibfk_1` FOREIGN KEY (`type`) REFERENCES `event_type` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

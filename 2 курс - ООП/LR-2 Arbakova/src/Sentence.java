import java.util.Scanner;
public class Sentence {
    String sentence;                                                        //переменная типа строки класса Sentence
    public Sentence(String text){                                           //начало конструктора класса Sentence на вход строка-текст
        this.sentence = text;                                               //присвоение переменной string sentence класса - значение text
    }
    Scanner console = new Scanner(System.in);
    public boolean isNumeric() {                                            // функция правда-ложь является ли числом
        try {
            Double.parseDouble(sentence);                                   // попытка перевода строки в число
            return true;                                                    // если получилось - правда
        } catch (NumberFormatException e) {
            return false;                                                   // не получилось
        }
    }
}
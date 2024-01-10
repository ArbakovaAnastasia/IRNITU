import java.util.Scanner;

public class lab4 {
    public static void main(String[] args) {
    //пример наследования, полиморфизма, инкапсуляции
        Car car3 = new BMV("м673сн", "blue", "S123"); //присвоение ссылки абстрактного класса - класса наследника (car-абстрактный класс bmv-наследник)
        Car car4 = new AUDI("н567ае", "green", "HRT213");
        Car car5 = new Toyota("в465св", "black", "GYD324", true); //все 3 машины - пример полиформизма
        //абстрактный класс имя = new класс-наследник
    //пример переопределения
        System.out.println("Машина 1");
        System.out.println(car3);
        car3.beep();
        System.out.println("\nМашина 2");
        System.out.println(car4);
        car4.beep();
        System.out.println("\nМашина 3");
        System.out.println(car5);
        car5.beep();
    //пример на машинах 6 и 7
        System.out.println("\n");
        Toyota car6 = new Toyota("в345рн", "white", "FHYD12", true);
        Toyota car7 = new Toyota("с465лм", "black", "GYD324", false);
        System.out.println(car6);
        System.out.println(car7);
        System.out.println("Машина 6 говорит: ");
        car6.startRace();
        System.out.println("Машина 7 говорит: ");
        car7.startRace();
    //замена значения переменной isRaceCar
        System.out.println("\nМашина 6 гоночная? "+car6.isRaceCar());
        System.out.println("Машина 6 сломалась.");
        car6.setRaceCar(false);
        System.out.println("Теперь машина 6 гоночная? "+car6.isRaceCar());
        System.out.println("\n");
        System.out.println(car6);
        System.out.println(car7);
        System.out.println("\n");

        Menu.menu();
    }

    public static int inputNumber(int leftGranitcha, int rightGranitcha) {              //функция ввода размерности матрицы
        String input = "";
        int x = 0;
        boolean isCorrect = true;
        Scanner console = new Scanner(System.in);
        do {
            try {
                System.out.print("Введите число от " + leftGranitcha + " до " + (rightGranitcha-1) + ": ");
                input = console.nextLine();
                x = Integer.parseInt(input);
                if ((x>=leftGranitcha) && (x <= rightGranitcha)){
                    break;
                } else { System.out.print("\nНекорректный ввод!\n");}
            }catch(NumberFormatException e) {
                isCorrect = false;
                System.out.print("\nОшибка! Введите число!\n");
            }
        } while (true);
        return x;
    }
}

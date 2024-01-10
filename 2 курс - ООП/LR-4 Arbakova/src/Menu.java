import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Menu {
    public static void menu (){
        StringBuilder builder = new StringBuilder();
        builder.append("\nМеню:\n")                                                            //пункты меню
                .append("1. Вывести список машин\n")
                .append("2. Добавить машину\n")
                .append("3. Удалить машину\n")
                .append("4. Поиск машин по цвету\n")
                .append("5. Выход\n");
        boolean isWork = true;
        List<Car> carList = new ArrayList<>(); //список машин
        String number;
        String color;
        String model;
        String raceCar; boolean isRaceCar = false;
        Scanner scanner = new Scanner(System.in);
        Car car1 = new BMV("в456ук", "black", "Dr123");
        Car car2 = new AUDI("о345мо", "red", "5623");
        Car car3 = new Toyota("ш678на", "blue", "ASD", true);
        Car car4 = new BMV("с294ае", "black", "U876A");
        Car car5 = new Toyota("а340ап", "white", "234VD", false);
        Car car6 = new Toyota("с674ма", "white", "12CS", true);
        Car car7 = new Toyota("с445св", "white", "CCYDJ", false);
        carList.add(car1); carList.add(car2); carList.add(car3); carList.add(car4); carList.add(car5); carList.add(car6); carList.add(car7);
        while (isWork) {
            System.out.println(builder.toString());                                       //вывод меню на экран
            System.out.print("Выберите пункт меню: \n");  String i =  new Scanner(System.in).nextLine();
            switch (i) {
                case "1":
                    System.out.print("Вывести список машин.\n");
                    System.out.println("\nВывод всех машин в группе:");
                    for(int j = 0; j < carList.size(); j++) {
                        System.out.print(j+1);
                        System.out.print(". ");
                        System.out.println(carList.get(j));
                    }
                    System.out.println("\n");
                    break;

                case "2":
                    System.out.print("Добавить машину.\n");
                    System.out.print("Введите марку машины ( 1 - БМВ, 2 - Ауди, 3 - Тойота): ");
                    String marka = scanner.nextLine();
                    Car car;
                    switch (marka) {
                        case "1":
                            System.out.println("\nВведите номер машины: ");
                            number = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите цвет машины: ");
                            color = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите модель машины: ");
                            model = new Scanner(System.in).nextLine();
                            car = new BMV(number, color, model);
                            System.out.println("\nВведенная машина: " + car);
                            carList.add(car);
                            System.out.print("Вы добавили машину!\n");
                            break;

                        case "2":
                            System.out.println("\nВведите номер машины: ");
                            number = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите цвет машины: ");
                            color = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите модель машины: ");
                            model = new Scanner(System.in).nextLine();
                            car = new AUDI(number, color, model);
                            System.out.println("\nВведенная машина: " + car);
                            carList.add(car);
                            System.out.print("Вы добавили машину!\n");
                            break;

                        case "3":
                            System.out.println("\nВведите номер машины: ");
                            number = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите цвет машины: ");
                            color = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите модель машины: ");
                            model = new Scanner(System.in).nextLine();
                            System.out.println("\nВведите является ли эта машина гоночной (Да/Нет): ");
                            raceCar = new Scanner(System.in).nextLine();

                            if ((raceCar.equals("Да")) || (raceCar.equals("да")) || (raceCar.equals("ДА"))) {
                                isRaceCar = true;
                            } else if ((raceCar.equals("Нет")) || (raceCar.equals("нет")) || (raceCar.equals("НЕТ"))) {
                                isRaceCar = false;
                            } else System.out.println("\nВведите Да или Нет. Попробуйте еще раз!");

                            car = new Toyota(number, color, model, isRaceCar);
                            System.out.println("\nВведенная машина: " + car);
                            carList.add(car);
                            System.out.print("Вы добавили машину!\n");
                            break;

                        default:
                            System.out.println("Введите 1 - БМВ, 2 - Ауди или 3 - Тойота!");
                    }
                    break;
                case "3":
                    System.out.print("Удалить машину.\n");
                    System.out.print("Введите номер из списка: \n");
                    int input = lab4.inputNumber(1, carList.size()+1);
                    if (input > carList.size()){
                        System.out.println("Введите число от 1 до "+ (carList.size()+1) + "!");
                    } else
                        System.out.println("\nУдаление машины из группы: "+carList.remove(input-1));
                    break;

                case "4":
                    System.out.print("Поиск машин по цветам.\n");
                    System.out.println("Введите цвет: ");
                    String colorSearch = new Scanner(System.in).nextLine();
                    System.out.println("Найденные машины: ");
                    for (Car carInList: carList){
                        if (carInList.getColor().equals(colorSearch)) {
                            System.out.println(carInList);
                        }
                    }
                    break;

                case "5":
                    System.out.print("Выполнен выход из программы.\n");                   //выход из программы
                    isWork = false;
                    break;

                default:
                    System.out.println("Вы допустили ошибку!");
            }
        }
    }
}

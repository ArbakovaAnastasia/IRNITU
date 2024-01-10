import java.util.Scanner;
public class menu {
    public static void menu() {
        StringBuilder builder = new StringBuilder();
        builder.append("\nМеню:\n")                                                            //пункты меню
                .append("1. Вычислить сумму диагоналей квадратной матрицы.\n")
                .append("2. Определить, является ли заданная строка символов числом.\n")
                .append("3. Выполнить сложение двух матриц.\n")
                .append("4. Выход.\n");
        boolean isWork = true;

            while (isWork) {
                System.out.println(builder.toString());                                       //вывод меню на экран
                Scanner scanner = new Scanner(System.in);
                System.out.print("Выберите пункт меню: \n");  String i = scanner.nextLine();
                switch (i) {                                                                  //выбор пункта меню из диапазона 1-4
                    case "1":
                        System.out.print("Вычислить сумму диагоналей квадратной матрицы.\n"); //1 задание
                        int input = Matrix.inputNumber( 2, 10);         //ввод числа - размер квадратной матрицы
                        Matrix matrix = new Matrix(input);                                    //создание объекта - матрица для задания 1
                        matrix.sumDiagonals();                                                //вычисление сумм диагноалей
                        break;
                    case "2":
                        System.out.print("Определить, является ли заданная строка символов числом.\nВведите строку: "); //2 задание
                        Sentence sentence = new Sentence(scanner.nextLine());                                           //ввод строки
                        System.out.println("Является числом: " + sentence.isNumeric());                                 //выводится сообщение и проверяется является ли строка числом
                        break;
                    case "3":
                        System.out.print("Выполнить сложение двух матриц.\n");                //3 задание
                        input = Matrix.inputNumber( 2, 10);             //ввод числа - размер квадратных матриц
                        Matrix A = new Matrix(input);                                         //создание объекта - матрица А для задания 3
                        Matrix B = new Matrix(input);                                         //создание объекта - матрица B для задания 3
                        A.sumMatrix(B.matrix);                                                //вывод суммы матриц А и В
                        break;
                    case "4":
                        System.out.print("Выполнен выход из программы.\n");                   //выход из программы
                        isWork = false;
                        break;
                    default:
                        System.out.println("Вы допустили ошибку!");
                }
            }
    }
}





//поток ввода - сканер, поток вывода - sout
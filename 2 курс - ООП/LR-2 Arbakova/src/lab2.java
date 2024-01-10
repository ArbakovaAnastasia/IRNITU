import java.util.Scanner;
public class lab2 {
    public static void main(String[] args) {
        System.out.print("\n1. Вычислить сумму диагоналей квадратной матрицы.\n");                                //1 задание
        int input = Matrix.inputNumber( 2, 10);                                        //ввод числа - размер квадратной матрицы
        Matrix matrix = new Matrix(input);                                                                   //создание объекта - матрица для задания 1
        matrix.sumDiagonals();                                                                               //вычисление сумм диагноалей
        System.out.print("\n2. Определить, является ли заданная строка символов числом.\nВведите строку: ");      //2 задание
        Sentence sentence = new Sentence(new Scanner(System.in).nextLine());                                 //ввод строки
        System.out.println("\nЯвляется числом: " + sentence.isNumeric());                                    //выводится сообщение и проверяется является ли строка числом
        System.out.print("\n3. Выполнить сложение двух матриц.\n");                                               //3 задание
        input = Matrix.inputNumber( 2, 10);                                            //ввод числа - размер квадратных матриц
        Matrix A = new Matrix(input);                                                                        //создание объекта - матрица А для задания 3
        Matrix B = new Matrix(input);                                                                        //создание объекта - матрица B для задания 3
        A.sumMatrix(B.matrix);                                                                               //вывод суммы матриц А и В
    }
}
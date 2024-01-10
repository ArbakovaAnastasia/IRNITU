import java.util.Arrays;
import java.util.Scanner;
import java.io.*;

public class lab1 {
    public static void main(String[] args) {
        System.out.print("Задание 1: Вычислите сумму диагоналей квадратной матрицы.\nВведите размер квадратной матрицы: ");
        //сканер для считывания с клавиатуры
        Scanner console = new Scanner(System.in);
        int n;
        do {
            while (!console.hasNextInt()) {
                System.out.print("Введите целое положительное число!\n");
                System.out.print("Введите размер квадратной матрицы: ");
                console.next();
            }
            n = console.nextInt();
        } while (n <= 1);

        //создание матрицы ввод вручную
        int[][] matrix = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print("A[");
                System.out.print(i + 1);
                System.out.print("][");
                System.out.print(j + 1);
                System.out.print("]= ");
                do {
                    while (!console.hasNextInt()) {
                        System.out.print("Введите целое положительное число!\n");
                        System.out.print("Введите еще раз элемент матрицы:");
                        console.next();
                    }
                    matrix[i][j] = console.nextInt();
                } while (matrix[i][j] <= 0);
            }
            System.out.print("\n");
        }

        //вывод матрицы на экран
        System.out.print("Полученная матрица:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(matrix[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }

        //сумма главной
        System.out.print("\n");
        int sum1 = 0;
        System.out.print("Сумма элементов главной диагонали: ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    sum1 = sum1 + matrix[i][j];
                }
            }
        }
        System.out.print(sum1);
        System.out.print("\n");
        //сумма побочной
        int sum2 = 0;
        System.out.print("Сумма элементов побочной диагонали: ");
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                if (i + j == n - 1) {
                    sum2 = sum2 + matrix[i][j];
                }
            }
        }
        System.out.print(sum2);
        System.out.print("\n");

        System.out.println("\nЗадание 2: Определите, является ли заданная строка символов числом: ");
        Scanner console2 = new Scanner(System.in);
        String str = console2.next(); //считывает введенную строку до первого пробела
        if (isNumeric(str)==true){
            System.out.println("Заданная строка является числом");
        }else{
            System.out.println("Заданная строка НЕ является числом");
        }

        System.out.print("\n");
        System.out.println("\nЗадание 3: Выполнить сложение двух матриц.\nВведите размер квадратных матриц: ");
        //сканер для считывания с клавиатуры
        Scanner console1 = new Scanner(System.in);
        int m;
        do {
            while (!console1.hasNextInt()) {
                System.out.print("Введите целое положительное число!\n");
                System.out.print("Введите размер квадратных матриц: ");
                console1.next();
            }
            m = console1.nextInt();
        } while (m <= 0);

        //создание матрицы1 ввод вручную
        int[][] matrix1 = new int[m][m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print("A[");
                System.out.print(i + 1);
                System.out.print("][");
                System.out.print(j + 1);
                System.out.print("]= ");
                do {
                    while (!console1.hasNextInt()) {
                        System.out.print("Введите целое положительное число!\n");
                        System.out.print("Введите еще раз элемент матрицы:");
                        console1.next();
                    }
                    matrix1[i][j] = console1.nextInt();
                } while (matrix1[i][j] <= 0);
            }
            System.out.print("\n");
        }
        //создание матрицы2 ввод вручную
        int[][] matrix2 = new int[m][m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print("B[");
                System.out.print(i + 1);
                System.out.print("][");
                System.out.print(j + 1);
                System.out.print("]= ");
                do {
                    while (!console1.hasNextInt()) {
                        System.out.print("Введите целое положительное число!\n");
                        System.out.print("Введите еще раз элемент матрицы:");
                        console1.next();
                    }
                    matrix2[i][j] = console1.nextInt();
                } while (matrix2[i][j] <= 0);
            }
            System.out.print("\n");
        }
        //вывод матрицы на экран
        System.out.print("Полученная матрица A:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(matrix1[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
        //вывод матрицы на экран
        System.out.print("Полученная матрица B:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(matrix2[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
        //сумма матриц
        int[][] matrix3 = new int[m][m];
        System.out.print("Сумма матриц:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
                System.out.print(matrix3[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
    }
    //пытаемся привести строку к типу Double, и если у нас это получается, мы считаем, что указанная строка – число:
    //try – определяет блок кода, в котором может произойти исключение;
    //catch – определяет блок кода, в котором происходит обработка исключения;
    public static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}

import java.util.Scanner;
public class Matrix {
    int size;                                                                         //размер матрицы
    int[][] matrix;                                                                   //переменная matrix
    public Matrix(int size) {                                                         //конструктор класса
        this.size = size;
        this.matrix = getRandMatrix(size);                                            //получение рандомной матрицы с указанным размером
    }
    public int[][] getRandMatrix(int size) {                                          //функция - получения рандомной матрицы
        int[][] matrix = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double k = Math.random() * 10 + 1;
                matrix[i][j] = (int) k;//изменение типов данных
            }
        } return matrix;
    }
    public void sumMatrix(int[][] matrixB) {                                           //функция - сумма матриц - для 3 задания
        int[][] sumMatrix = new int[size][size];
        System.out.println("\nМатрица А:\n");
        outputMatrix(this.matrix);                                                     //вызов функции - вывод матрицы А
        System.out.println("\nМатрица В:\n");
        outputMatrix(matrixB);                                                         //вызов функции - вывод матрицы В
        System.out.print("\nСумма матриц:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sumMatrix[i][j] = matrix[i][j] + matrixB[i][j];
                System.out.print(sumMatrix[i][j] + " ");
            } System.out.print("\n");
        }
    }
    public void sumDiagonals() {                                                       //функция - сумма диагоналей матрицы - для 1 задания
        int sumMain = 0;
        System.out.println("\nМатрица:\n");
        outputMatrix(this.matrix);                                                     //вызов функции - вывод матрицы
        System.out.print("\nСумма элементов главной диагонали: ");                     //сумма главной диагонали
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    sumMain = sumMain + this.matrix[i][j];
                }
            }
        }
        System.out.print(sumMain);                                                      //вывод суммы главной диагонали
        int sumSide = 0;
        System.out.print("\nСумма элементов побочной диагонали: ");                     //сумма побочной диагонали
        for (int i = 0; i < size; i++) {
            for (int j = size - 1; j >= 0; j--) {
                if (i + j == size - 1) {
                    sumSide = sumSide + matrix[i][j];
                }
            }
        }
        System.out.print(sumSide + "\n");                                               //вывод суммы побочной диагонали
    }
    private void outputMatrix(int[][] matrix) {                                         //функция вывода матрицы на экран
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(matrix[i][j] + " ");
            } System.out.print("\n");
        }
    }
    public static int inputNumber(int leftGranitcha, int rightGranitcha) {              //функция ввода размерности матрицы
        String input = "";
        int x = 0;
        boolean isCorrect = true;
        Scanner console = new Scanner(System.in);
        do {
            try {
                System.out.print("Введите число от " + leftGranitcha + " до " + rightGranitcha + ": ");
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
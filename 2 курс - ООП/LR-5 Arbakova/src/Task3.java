import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Task3 extends JFrame {
    private JButton buildMatrixButton;
    private JTextField textField1;
    private JTable table1;
    private JTable table2;
    private JTable table3;
    private JPanel mainPanel;
    private JButton backMenuButton;

    public Task3(String title) throws HeadlessException {
        super(title);
        setContentPane(mainPanel);
        setSize(500, 500);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); //выход с программы
        setVisible(true);

        buildMatrixButton.addActionListener(e -> {
            String text = textField1.getText();
            if (text.matches("^[0-9]+$")){
                int i = Integer.parseInt(text);
                if (i!=0){
                    Matrix matrix1 = new Matrix(i);
                    Matrix matrix2 = new Matrix(i);
                    int[][] sumMatrix = matrix1.sumMatrix(matrix2.matrix);
                    String[][] matrixString1 = new String[i][i];
                    String[][] matrixString2 = new String[i][i];
                    String[][] matrixString3 = new String[i][i];
                    for (int j = 0; j < i; j++) {
                        for (int k = 0; k < i; k++) {
                            matrixString1[j][k] = Integer.toString(matrix1.matrix[j][k]);
                            matrixString2[j][k] = Integer.toString(matrix2.matrix[j][k]);
                            matrixString3[j][k] = Integer.toString(sumMatrix[j][k]);
                        }
                    }
                    table1.setModel(new DefaultTableModel(matrixString1, matrixString1[0]));
                    table2.setModel(new DefaultTableModel(matrixString2, matrixString2[0]));
                    table3.setModel(new DefaultTableModel(matrixString3, matrixString3[0]));
                } else new checkNumber();
            } else new checkNumber();
        });
        backMenuButton.addActionListener(e -> {
            MainMenu menu = new MainMenu("Главное меню");
            dispose();
        });
    }
}

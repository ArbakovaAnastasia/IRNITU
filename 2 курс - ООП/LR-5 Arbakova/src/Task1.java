import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Task1 extends JFrame{
    private JTextField textField1;
    private JTable table1;
    private JButton buildMatrixButton;
    private JPanel mainPanel;
    private JLabel Answer1;
    private JLabel Answer2;
    private JButton backMenuButton;

    public Task1(String title) throws HeadlessException {
        super(title);
        setContentPane(mainPanel);
        setSize(500, 300);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); //выход с программы


        setVisible(true);

        buildMatrixButton.addActionListener(e -> {
            String text = textField1.getText();
            if (text.matches("^[0-9]+$")){
                int i = Integer.parseInt(text);
                if (i!=0){
                    Matrix matrix = new Matrix(i);
                    String[][] matrixString = new String[i][i];
                    for (int j = 0; j < i; j++) {
                        for (int k = 0; k < i; k++) {
                            matrixString[j][k] = Integer.toString(matrix.matrix[j][k]);
                        }
                    }
                    table1.setModel(new DefaultTableModel(matrixString, matrixString[0]));

                    Answer1.setText(Integer.toString(matrix.sumMainDiagonal()));
                    Answer2.setText(Integer.toString(matrix.sumSideDiagonal()));
                } else new checkNumber();
            } else new checkNumber();
        });
        backMenuButton.addActionListener(e -> {
            MainMenu menu = new MainMenu("Главное меню");
            dispose();
        });
    }
}

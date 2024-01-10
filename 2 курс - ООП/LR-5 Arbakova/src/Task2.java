import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Task2 extends JFrame {
    private JTextField textField1;
    private JButton getAnswerButton;
    private JPanel mainPanel;
    private JLabel Answer;
    private JButton backMenuButton;

    public Task2(String title) throws HeadlessException {
        super(title);
        setContentPane(mainPanel);
        setSize(500, 350);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); //выход с программы
        setVisible(true);

        getAnswerButton.addActionListener(e -> {
            String text = textField1.getText();
            Sentence sentence = new Sentence(text);
            Answer.setText(sentence.isNumeric() ? "Да" : "Нет");
        });
        backMenuButton.addActionListener(e -> {
            MainMenu menu = new MainMenu("Главное меню");
            dispose();
        });
    }
}

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainMenu extends JFrame{
    private JButton task1Button;
    private JButton task2Button;
    private JButton task3Button;
    private JPanel mainPanel;

    public MainMenu(String title) throws HeadlessException {
        super(title);
        setContentPane(mainPanel);
        setSize(500, 150);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); //выход с программы
        setVisible(true);

        task1Button.addActionListener(e -> {
            Task1 task = new Task1("Задание 1");
            dispose();
        });
        task2Button.addActionListener(e -> {
            Task2 task = new Task2("Задание 2");
            dispose();
        });
        task3Button.addActionListener(e -> {
            Task3 task = new Task3("Задание 3");
            dispose();
        });
    }
}

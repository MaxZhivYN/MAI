package com.interrao.zhivmax.client;

// Использование списков JList и модели списка DefaultListModel

import javax.swing.*;

import java.awt.event.*;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.nio.charset.Charset;
import java.util.Locale;
import java.util.Vector;



import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class ListModelTest extends JFrame
{
    // Данные списка
    private final String[]   dataList = { "Бакалея", "Напитки", "Хлеб"};
    private final String[][] dataText = {{"Сахар", "Мука", "Соль"},
            {"Чай"  , "Кофе", "Морс"},
            {"Батон", "Пшеничный",
                    "Бородинский"}};
    private JTextArea content;

    public ListModelTest()
    {
        super("Слушатель событий списка");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        // Создание списка
        JPanel contents = new JPanel();
        final JList<String> list = new JList<String>(dataList);
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        list.setPrototypeCellValue("Увеличенный");
        // Создание текстового поля
        content = new JTextArea(5, 20);
        // Подключения слушателя
        list.addListSelectionListener(new listSelectionListener());
        // Подключение слушателя мыши
        list.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if ( e.getClickCount() == 2 ) {
                    // Получение элемента
                    int selected = list.locationToIndex(e.getPoint());
                    int i = 0;
                    String txt = "";
                    while (i < dataText[selected].length)
                        txt += dataText[selected][i++] + "\n";
                    content.setText (txt);
                }
            }
        });

        // Размещение компонентов в интерфейсе
        contents.add(new JLabel("Список разделов"));
        contents.add(new JScrollPane(list));
        contents.add(new JLabel("Содержимое разделов"));
        contents.add(new JScrollPane(content));
        // Вывод окна
        setContentPane(contents);
        setSize(600, 200);
        setVisible(true);
    }
    /*
     * Слушатель списка
     */
    class listSelectionListener implements ListSelectionListener {
        public void valueChanged(ListSelectionEvent e) {
            // Выделенная строка
            int selected = ((JList<?>)e.getSource()).
                    getSelectedIndex();
            System.out.println ("Выделенная строка : " + String.valueOf(selected));
        }
    }
    public static void main(String[] args) throws UnsupportedEncodingException {
        System.out.println(System.getProperty("file.encoding"));
        PrintStream out = new PrintStream(System.out, true, "UTF-8");
        System.setOut(new PrintStream(System.out, true, "UTF-8"));

        System.out.println("Привет мир!");
        out.println("Привет мир!");
        new ListModelTest();
    }
}
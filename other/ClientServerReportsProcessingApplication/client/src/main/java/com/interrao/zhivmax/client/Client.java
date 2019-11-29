package com.interrao.zhivmax.client;

import javax.swing.*;
import javax.swing.text.DateFormatter;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.MaskFormatter;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.net.Socket;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;

import com.github.lgooddatepicker.datepicker.DatePicker;
import com.github.lgooddatepicker.datepicker.DatePickerSettings;
import com.github.lgooddatepicker.timepicker.TimePickerSettings;
import net.sf.jasperreports.engine.JRField;



public class Client {
    private Socket client;
    private ObjectInputStream objectInputStream;
    private ObjectOutputStream objectOutputStream;

    private final JFrame jFrame = new JFrame() {};
    private final JPanel jPanel = new JPanel();
    private final JList<String> reportList = new JList<String>();
    private final JButton choiceReportButton = new JButton(new ChoiceReportButtonAction());
    private final JList<String> filterList = new JList<String>();
    private final JFormattedTextField filterFrom = new JFormattedTextField();
    private final JFormattedTextField filterTo = new JFormattedTextField();
    private final JButton choiceFilterButton = new JButton(new choiceFilterButtonAction());
    private final JButton createReport = new JButton(new CreateReportAction());
    private DatePicker datePickerFrom;
    private DatePicker datePickerTo;
    private String[][] params;
    JRField[] filterArray;
    Client() throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException, IOException {

        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setTitle("MyApp");
        jFrame.setSize(600, 400);
        jFrame.setLocationRelativeTo(null);
        UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");

        jFrame.add(jPanel);
        GetServerConnection();

        CreateReportList();
        CreateChoiceReportButton();

        CreateFilterList();

        CreateFilterFrom();
        CreateFilterTo();
        CreateDatePicker("From");
        CreateDatePicker("To");


        CreateChoiceFilterButton();
        CreateCreateReportButton();

        jFrame.setVisible(true);

    }

    private void CreateReportList() throws IOException, ClassNotFoundException {
        Vector<String> reportVector = (Vector<String>) objectInputStream.readObject();
        if (reportVector.isEmpty()) {
            JOptionPane.showMessageDialog(null, "На сервер нет отчетов");
            throw new NullPointerException("No reports on server");
        }

        reportList.setListData(reportVector);
        reportList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        reportList.setPrototypeCellValue("Увеличенный");
        JScrollPane filterListScrollPane = new JScrollPane(reportList);
        jPanel.add(filterListScrollPane);
    }

    private void CreateChoiceReportButton() {
        choiceReportButton.setText("Выбрать отчет");
        jPanel.add(choiceReportButton);
    }

    private void CreateFilterList() {
        filterList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        filterList.setPrototypeCellValue("Увеличенный");
        filterList.addMouseListener(new filterFromMouseListener());
        filterList.setEnabled(false);
        JScrollPane reportListScrollPane = new JScrollPane(filterList);
        jPanel.add(reportListScrollPane);
    }

    private void CreateFilterFrom() {
        filterFrom.setColumns(10);
        filterFrom.setEnabled(false);
        JScrollPane filterFromPane = new JScrollPane(filterFrom);
        jPanel.add(filterFromPane);
    }

    private void CreateFilterTo() {
        filterTo.setColumns(10);
        filterTo.setEnabled(false);
        JScrollPane filterToPane = new JScrollPane(filterTo);
        jPanel.add(filterToPane);
    }

    private void CreateChoiceFilterButton() {
        choiceFilterButton.setText("Утвердить параметр");
        choiceFilterButton.setEnabled(false);
        jPanel.add(choiceFilterButton);
    }

    private void CreateCreateReportButton() {
        createReport.setText("Сформировать отчет");
        createReport.setEnabled(false);
        jPanel.add(createReport);
    }

    private void CreateDatePicker(String name) {
        DatePickerSettings datePickerSettings = new DatePickerSettings();
        datePickerSettings.setFormatForDatesBeforeCommonEra(DateTimeFormatter.ofPattern("yyyy-MM-dd"));
        datePickerSettings.setFormatForDatesCommonEra(DateTimeFormatter.ofPattern("yyyy-MM-dd"));
        TimePickerSettings timePickerSettings = new TimePickerSettings();
        timePickerSettings.use24HourClockFormat();

        switch (name) {
            case "From":
                datePickerFrom = new DatePicker(datePickerSettings);
                datePickerFrom.setVisible(false);
                jPanel.add(datePickerFrom);
                break;
            case "To":
                datePickerTo = new DatePicker(datePickerSettings);
                datePickerTo.setVisible(false);
                jPanel.add(datePickerTo);
                break;
        }
    }

    private void GetServerConnection() throws IOException {
        client = new Socket("127.0.0.1", 9000);
        objectInputStream = new ObjectInputStream(client.getInputStream());
        objectOutputStream = new ObjectOutputStream(client.getOutputStream());

    }


    private void EnableFilters() throws IOException, ClassNotFoundException {
        filterList.setEnabled(true);
        filterFrom.setEnabled(true);
        filterTo.setEnabled(true);
        choiceFilterButton.setEnabled(true);
        createReport.setEnabled(true);
        reportList.setEnabled(false);
        choiceReportButton.setEnabled(false);

        filterArray = (JRField[]) objectInputStream.readObject();
        String[] filterArrayString = new String[filterArray.length];

        String description;
        for (int i = 0; i < filterArray.length; ++i) {
            description = filterArray[i].getDescription();
            if (!description.isEmpty())
                filterArrayString[i] = description;
            else {
                filterArrayString[i] = filterArray[i].getName() + " (no discr)";
            }
        }


        params = new String[filterArray.length][2];

        filterList.setListData(filterArrayString);
    }



    // CLASSES





    private class ChoiceReportButtonAction extends AbstractAction {
        ChoiceReportButtonAction() {
            putValue(AbstractAction.SHORT_DESCRIPTION, "Информация о кнопеке");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            System.out.println(reportList.getAnchorSelectionIndex());
            int reportListIndex = reportList.getAnchorSelectionIndex();

            if (reportListIndex < 0) {
                JOptionPane.showMessageDialog(null, "Выберете отчет");
                return;
            }

            try {
                System.out.println("massage waiting");
                objectOutputStream.writeInt(reportList.getAnchorSelectionIndex());
                objectOutputStream.flush();
                EnableFilters();

            } catch (IOException | ClassNotFoundException ex) {
                ex.printStackTrace();
            }
        }
    }

    private class choiceFilterButtonAction extends AbstractAction {
        choiceFilterButtonAction() {
            putValue(AbstractAction.SHORT_DESCRIPTION, "Информация о кнопеке");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            int index = filterList.getAnchorSelectionIndex();
            System.out.println(filterArray[index].getValueClassName());
            if (filterArray[index].getValueClassName().equals("java.sql.Date")) {
                params[index][0] = datePickerFrom.getText();
                params[index][1] = datePickerTo.getText();
            }
            else {
                params[index][0] = filterFrom.getText();
                params[index][1] = filterTo.getText();
            }

            System.out.println(index + " " + params[index][0] + " " + params[index][1]);
        }
    }

    private class CreateReportAction extends AbstractAction {
        CreateReportAction() {
            putValue(AbstractAction.SHORT_DESCRIPTION, "Информация о кнопеке");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                objectOutputStream.writeObject(params);

            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }


    private class filterFromMouseListener extends MouseAdapter {
        @Override
        public void mouseClicked(MouseEvent e) {
            int index = filterList.getAnchorSelectionIndex();

            switch (filterArray[index].getValueClassName()) {
                case "java.lang.String":
                    if (!filterFrom.isVisible()) filterFrom.setVisible(true);
                    if (filterTo.isVisible()) filterTo.setVisible(false);
                    if (datePickerFrom.isVisible()) datePickerFrom.setVisible(false);
                    if (datePickerTo.isVisible()) datePickerTo.setVisible(false);

                    filterFrom.setText(params[index][0]);
                    break;
                case "java.sql.Date":
                    if (filterFrom.isVisible()) filterFrom.setVisible(false);
                    if (filterTo.isVisible()) filterTo.setVisible(false);
                    if (!datePickerFrom.isVisible()) datePickerFrom.setVisible(true);
                    if (!datePickerTo.isVisible()) datePickerTo.setVisible(true);

                    datePickerFrom.setText(params[index][0]);
                    datePickerTo.setText(params[index][1]);
//                    filterFrom.setText(params[index][0]);
//                    filterTo.setText(params[index][1]);
                    break;
                case "java.lang.Integer":
                    if (!filterFrom.isVisible()) filterFrom.setVisible(true);
                    if (!filterTo.isVisible()) filterTo.setVisible(true);
                    if (datePickerFrom.isVisible()) datePickerFrom.setVisible(false);
                    if (datePickerTo.isVisible()) datePickerTo.setVisible(false);


                    filterFrom.setText(params[index][0]);
                    filterTo.setText(params[index][1]);
                    break;
                default:
                    System.out.println("ERROR: Data type not founded");
            }

//            filterFrom.setFormatterFactory(new DefaultFormatterFactory());
////            switch (index) {
////                case 0:
////                    filterFrom.setFormatterFactory(new FormatPhoneNumber());
////                    break;
////                case 1:
////                    filterFrom.setFormatterFactory(new FormatDate());
////                    break;
////            }
            jPanel.revalidate();
        }
    }

//    class FormatPhoneNumber extends JFormattedTextField.AbstractFormatterFactory {
//        @Override
//        public JFormattedTextField.AbstractFormatter getFormatter(JFormattedTextField tf) {
//            try {
//                MaskFormatter phoneFormatter = new MaskFormatter("+7-###-###-##-##");
//                phoneFormatter.setPlaceholderCharacter(' ');
//                return phoneFormatter;
//            } catch (ParseException e) {
//                e.printStackTrace();
//                return null;
//            }
//        }
//    }
//
//    class FormatDate extends JFormattedTextField.AbstractFormatterFactory {
//        @Override
//        public JFormattedTextField.AbstractFormatter getFormatter(JFormattedTextField tf) {
//            //DateFormat dateFormat = ;
//            DateFormatter dateFormatter = new DateFormatter(new SimpleDateFormat("yyyyMMdd"));
//
//
//            //dateFormatter.setAllowsInvalid(false);
//            //dateFormatter.setOverwriteMode(true);
//            //dateFormatter.setCommitsOnValidEdit(false);
//            return dateFormatter;
//
//        }
//    }
//
//    public class DateLabelFormatter extends JFormattedTextField.AbstractFormatter {
//
//        private String datePattern = "yyyy-MM-dd";
//        private SimpleDateFormat dateFormatter = new SimpleDateFormat(datePattern);
//
//        @Override
//        public Object stringToValue(String text) throws ParseException {
//            return dateFormatter.parseObject(text);
//        }
//
//        @Override
//        public String valueToString(Object value) throws ParseException {
//            if (value != null) {
//                Calendar cal = (Calendar) value;
//                return dateFormatter.format(cal.getTime());
//            }
//
//            return "";
//        }
//
//    }
}

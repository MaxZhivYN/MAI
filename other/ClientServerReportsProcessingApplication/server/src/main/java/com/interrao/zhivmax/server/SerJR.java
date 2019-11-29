package com.interrao.zhivmax.server;

import net.sf.jasperreports.engine.*;
import net.sf.jasperreports.engine.design.JRDesignQuery;
import net.sf.jasperreports.engine.design.JRDesignQueryChunk;
import net.sf.jasperreports.engine.design.JasperDesign;
import net.sf.jasperreports.engine.export.ooxml.JRXlsxExporter;
import net.sf.jasperreports.engine.query.JRAbstractQueryExecuter;
import net.sf.jasperreports.engine.query.JRQueryExecuterFactory;
import net.sf.jasperreports.engine.xml.JRXmlLoader;
import net.sf.jasperreports.export.SimpleExporterInput;
import net.sf.jasperreports.export.SimpleOutputStreamExporterOutput;
import net.sf.jasperreports.export.SimpleXlsxReportConfiguration;
import net.sf.jasperreports.view.JasperViewer;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.URL;
import java.util.*;
import java.sql.*;

public class SerJR {
    private static final String pathToFolder = "C:\\Users\\Planzz\\IdeaProjects\\server\\src\\main\\jasperreports\\JRxmlFolder";

    private File[] files;
    private static final String DB_URL = "jdbc:postgresql://localhost:5432/CreateReportsDB";
    private static final String USER = "postgres";
    private static final String PASS = "123";
    private Vector<String> reportVector = new Vector<>();
    private static Connection connection = null;
    private JasperDesign jasperDesign;
    private JRField[] jrFields;
    private int reportListIndex;
    SerJR() {
        try {
            File folder = new File(pathToFolder);
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection(DB_URL, USER, PASS);
            if (folder.exists() && folder.isDirectory()) {
                files = folder.listFiles();
                if (files == null || files.length < 1)
                    throw new NullPointerException("No files in folder");
            } else
                throw new NullPointerException("Path to folder doesn't exist");
        }
        catch (NullPointerException | ClassNotFoundException | SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public Vector<String> getReportList() {
        files = new File(pathToFolder).listFiles();
        if (!reportVector.isEmpty())
            reportVector.clear();

        String localReportName;

        for (int i = 0; i < files.length; ++i) {
            localReportName = files[i].getName();
            if (localReportName.substring(localReportName.lastIndexOf('.'), localReportName.length()).equals(".jrxml")) {
                reportVector.add(localReportName.substring(0, localReportName.lastIndexOf('.')));
            }
        }

        return reportVector;
    }

    public JRField[] getReportParams(int reportListIndex) {
        try {
            File file = new File(pathToFolder + "\\" + reportVector.get(reportListIndex) + ".jrxml");
            jasperDesign = JRXmlLoader.load(file.getAbsolutePath());
            jrFields = jasperDesign.getFields();
            this.reportListIndex = reportListIndex;
            Collection<JRExpression> collection = jasperDesign.getExpressions();

//            for (Collection<JRExpression> jr : jasperDesign.getExpressions()) {
//
//            }


            return jrFields;
        }
        catch (JRException  e) {
            System.out.println(e.getMessage());
            return null;
        }
    }

    public String getReportWithFilters(String[][] filters) {

        try {

            JRDesignQuery designQuery = new JRDesignQuery();
            String queryText = jasperDesign.getQuery().getText();

            designQuery.setText(queryText + " " + GetQueryString(filters));
            System.out.println(designQuery.getText());
            jasperDesign.setQuery(designQuery);

            Map<String, Object> parameters = new HashMap<>();
//            URL image1 = this.getClass().getResource(pathToFolder + "\\coffee.jpg");
//            URL image2 = this.getClass().getResource(pathToFolder + "\\coffee_stain.png");
//            parameters.put("coffee", image1);
//            parameters.put("kek", image2);

            JasperReport jasperReport = JasperCompileManager.compileReport(jasperDesign);
            JasperPrint jasperPrint = JasperFillManager.fillReport(jasperReport, parameters, connection);

            //SimpleXlsxReportConfiguration configuration = new SimpleXlsxReportConfiguration();
            //configuration.setOnePagePerSheet(true);
            //configuration.setIgnoreGraphics(false);

            File outputFile = new File(pathToFolder + "\\" + reportVector.get(reportListIndex) + ".xlsx");

            try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                 OutputStream fileOutputStream = new FileOutputStream(outputFile)) {
                JRXlsxExporter exporter = new JRXlsxExporter();
                exporter.setExporterInput(new SimpleExporterInput(jasperPrint));
                exporter.setExporterOutput(new SimpleOutputStreamExporterOutput(byteArrayOutputStream));
                exporter.exportReport();
                byteArrayOutputStream.writeTo(fileOutputStream);
            }

            JasperExportManager.exportReportToPdfFile(jasperPrint, pathToFolder + "\\" + reportVector.get(reportListIndex) + ".pdf");
            System.out.println("OK");

            return pathToFolder + "\\" + reportVector.get(reportListIndex) + ".xlsx";
        }
        catch (JRException | IOException e) {
            System.out.println(e.getMessage());
            //e.printStackTrace();
            return null;
        }


    }

    private String GetQueryString(String[][] filters) {
        String queryString = "";
        boolean andFlag = false;
        for (int i = 0; i < filters.length; ++i) {
            switch (jrFields[i].getValueClassName()) {
                case "java.lang.String":
                    if (filters[i][0] != null) {
                        queryString += ((andFlag) ? "AND " : "WHERE ") + "\"" + jrFields[i].getName() + "\" like '" + filters[i][0] + "' ";
                        if (!andFlag) andFlag = true;
                    }
                    break;
                case "java.sql.Date":
                    if (filters[i][0] != null && !filters[i][0].isEmpty()) {
                        queryString += ((andFlag) ? "AND " : "WHERE ") + "\"" + jrFields[i].getName() + "\" >= " + "to_date('" + filters[i][0] + "', 'yyyy-MM-dd')" + " ";
                        if (!andFlag) andFlag = true;
                    }
                    //      to_date('1999-01-20', 'yyyy-MM-dd')
                    if (filters[i][1] != null && !filters[i][1].isEmpty()) {
                        queryString += ((andFlag) ? "AND " : "WHERE ") + "\"" + jrFields[i].getName() + "\" >= " + "to_date('" + filters[i][1] + "', 'yyyy-MM-dd')" + " ";
                        if (!andFlag) andFlag = true;
                    }
                    break;
                case "java.lang.Integer":
                    if (filters[i][0] != null && !filters[i][0].isEmpty()) {
                        queryString += ((andFlag) ? "AND " : "WHERE ") + "\"" + jrFields[i].getName() + "\" >= " + filters[i][0] + " ";
                        if (!andFlag) andFlag = true;
                    }
                    if (filters[i][1] != null && !filters[i][1].isEmpty()) {
                        queryString += ((andFlag) ? "AND " : "WHERE ") + "\"" + jrFields[i].getName() + "\" <= " + filters[i][1] + " ";
                        if (!andFlag) andFlag = true;
                    }
                    System.out.println(queryString);
                    break;
                default:
                    System.out.println("ERROR: Data type not founded");
                    return null;
            }
        }

        return queryString;
    }
}

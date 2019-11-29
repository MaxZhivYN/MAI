package com.interrao.zhivmax.server;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.design.JRDesignQuery;
import net.sf.jasperreports.engine.design.JRDesignQueryChunk;
import net.sf.jasperreports.engine.design.JasperDesign;
import net.sf.jasperreports.engine.xml.JRXmlLoader;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ServerMain {
    public static void main(String[] args) throws IOException, ClassNotFoundException, SQLException, JRException {
//        Class.forName("org.postgresql.Driver");
//        JasperDesign jasperDesign = JRXmlLoader.load("C:\\Users\\Planzz\\IdeaProjects\\server\\src\\main\\jasperreports\\JRxmlFolder\\SampleReport.jrxml");
//
//        System.out.println(jasperDesign.getQuery().getText());
//
//        String queryText = jasperDesign.getQuery().getText();
//        JRDesignQuery designQuery = new JRDesignQuery();
//        JRDesignQueryChunk jrDesignQueryChunk = new JRDesignQueryChunk();
//        jrDesignQueryChunk.setText(queryText + " WHERE \"id\" > 4");
//        designQuery.addChunk(jrDesignQueryChunk);
//
//
//
//        jasperDesign.setQuery(designQuery);
//        System.out.println(jasperDesign.getQuery().getText());
        new Server();
    }
}

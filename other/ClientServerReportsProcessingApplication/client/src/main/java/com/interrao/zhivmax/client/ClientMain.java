package com.interrao.zhivmax.client;

import javax.swing.*;
import java.io.IOException;
import java.io.PrintStream;


public class ClientMain {
    public static void main(String[] args) throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException, IOException {
        System.setOut(new PrintStream(System.out, true, "UTF-8"));
        new Client();
    }
}

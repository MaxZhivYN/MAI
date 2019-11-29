package com.interrao.zhivmax.client;

import java.io.IOException;
import java.net.*;

public class Main {

    public static void main(String[] args) throws IOException {
        Socket client = new Socket("127.0.0.1", 9000);


        client.close();
    }
}

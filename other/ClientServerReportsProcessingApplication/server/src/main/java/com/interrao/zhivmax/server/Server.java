package com.interrao.zhivmax.server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;


public class Server {
    Server() throws IOException {
        ServerSocket server = new ServerSocket(9000);

        while (true) {
            ClientProcessingThread clientProcessingThread = new ClientProcessingThread(server);
            clientProcessingThread.start();
            System.out.println("End cycle");
        }
    }

    private class ClientProcessingThread extends Thread {
        private Socket client;
        private final SerJR serJR = new SerJR();
        ClientProcessingThread(ServerSocket server) {
            try {
                client = server.accept();
                System.out.println("Client accept");
            }
            catch (IOException e) {
                e.printStackTrace();
            }

        }

        @Override
        public void run()	//Этот метод будет выполнен в побочном потоке
        {
            try {
                ObjectOutputStream objectOutputStream = new ObjectOutputStream(client.getOutputStream());
                ObjectInputStream objectInputStream = new ObjectInputStream(client.getInputStream());


                objectOutputStream.writeObject(serJR.getReportList());
                int reportListIndex = objectInputStream.readInt();

//                for (String s : serJR.getReportParams(reportListIndex)) {
//                    System.out.println(s);
//                }
                objectOutputStream.writeObject(serJR.getReportParams(reportListIndex));


                ;
                FileOutputStream fileOutputStream = new FileOutputStream(serJR.getReportWithFilters((String[][]) objectInputStream.readObject()));


                objectOutputStream.close();
                client.close();
                System.out.println("Client disconnected");
            }
            catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}





































/*




        ServerSocket serever = new ServerSocket(9000);
        int count = 0;

        while (true) {
            Socket client = serever.accept();
            System.out.println("Client accept " + (++count));
            OutputStreamWriter out = new OutputStreamWriter(client.getOutputStream());
            out.write("acceptance");
            out.flush();

            Thread.sleep(3000);

            out.write("123123123123");
            out.flush();
            System.out.println("mess go out");
            client.close();
        }
    }

 */
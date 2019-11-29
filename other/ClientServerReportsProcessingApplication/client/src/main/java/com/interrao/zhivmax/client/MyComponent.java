package com.interrao.zhivmax.client;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.net.MalformedURLException;
import java.net.URL;

public class MyComponent extends JComponent {
    @Override
    protected void paintComponent(Graphics graphics) {
        Font font = new Font("Impact", Font.BOLD, 20);
        Graphics2D graphics2D = (Graphics2D) graphics;
        graphics2D.setFont(font);
        graphics.drawString("Hello word", 50, 30);
        Line2D line2D = new Line2D.Double(0, 0, 190, 190);
        graphics2D.draw(line2D);

        Ellipse2D ellipse2D = new Ellipse2D.Double(50, 50, 100, 100);
        graphics2D.draw(ellipse2D);

        try {
            URL url = new URL("https://static.tgstat.ru/public/images/channels/_0/0f/0f8a2773df847871112769dc691c1270.jpg");
            Image image = new ImageIcon(url).getImage();
            graphics2D.drawImage(image, 300, 150, null);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }

    }
}

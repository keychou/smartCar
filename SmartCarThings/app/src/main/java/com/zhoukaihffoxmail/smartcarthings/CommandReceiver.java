package com.zhoukaihffoxmail.smartcarthings;

import android.os.Handler;
import android.os.Message;
import android.text.StaticLayout;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by klein on 2018/3/11.
 */

public class CommandReceiver {
    private static final String TAG = "CommandReceiver";
    private ServerSocket serverSocket;
    private Socket clientSocket;
    String remoteIP;
    int remotePort;
    private BufferedReader in;
    private PrintWriter out;

    GpioControl gpioControl = new GpioControl();
    Handler handler;



    public CommandReceiver(Handler handler){
        this.handler = handler;
        ServerThread serverThread = new ServerThread();
        serverThread.start();

    }

    private class ServerThread extends Thread{

        @Override
        public void run() {
            // TODO Auto-generated method stub
            //super.run();

            Log.d(TAG,"server run");
            try {
//                serverSocket = new ServerSocket(50005);//默认的路由器地址为Address: 192.168.43.1
                serverSocket = new ServerSocket(5000);
                while (true) {
                    clientSocket = serverSocket.accept();//阻塞等待处理...
                    remoteIP = clientSocket.getInetAddress().getHostAddress();
                    remotePort = clientSocket.getLocalPort();
                    Log.d(TAG,"A client connected. IP:" + remoteIP+ ", Port: " + remotePort);
                    Log.d(TAG,"server: receiving.............");
                    // 获得 client 端的输入输出流，为进行交互做准备
                    in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    out = new PrintWriter(clientSocket.getOutputStream(), false);

                    for(;;){
                        try {
                            // 获得 client 端发送的数据
                            String command = in.readLine();
                            // String content = new String(tmp.getBytes("utf-8"));
                            Log.d(TAG,"command < " + command);

                            Message msg = new Message();
                            msg.what = gpioControl.getCommandId(command);
                            handler.sendMessage(msg);

                            // 向 client 端发送响应数据
                            out.println("Your message has been received successfully！.");
                        }catch (Exception e){
                            e.printStackTrace();
                            break;
                        }
                    }

                    // 关闭各个流
                    out.close();
                    in.close();
                }
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }
    }
}

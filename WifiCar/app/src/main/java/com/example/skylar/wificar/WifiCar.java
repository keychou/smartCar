package com.example.skylar.wificar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class WifiCar extends AppCompatActivity{

    Button forward, backward, turnleft, turnright;
    static PrintWriter mPrintWriterClient = null;
    private Socket mSocketClient = null;
    static BufferedReader mBufferedReaderClient	= null;
    private Thread mThreadClient = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wifi_car);
        forward = (Button) findViewById(R.id.forward);
        backward = (Button) findViewById(R.id.backward);
        turnleft = (Button) findViewById(R.id.turnleft);
        turnright = (Button) findViewById(R.id.turnright);

        mThreadClient = new Thread(mRunnable);
        mThreadClient.start();

        forward.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();

                switch(action)
                {
                    case MotionEvent.ACTION_DOWN:
                        System.out.println("klein------forward---ACTION_DOWN-----");
                        mPrintWriterClient.print("W");
                        mPrintWriterClient.flush();
                        break;
                    case MotionEvent.ACTION_UP:
                        System.out.println("klein------forward---ACTION_UP-----");
                        mPrintWriterClient.print("P");
                        mPrintWriterClient.flush();
                }
                return false;
            }
        });


        backward.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event) {

                int action = event.getAction();
                switch(action)
                {
                    case MotionEvent.ACTION_DOWN:
                        System.out.println("klein------backward---ACTION_DOWN-----");
                        mPrintWriterClient.print("S");
                        mPrintWriterClient.flush();
                        break;
                    case MotionEvent.ACTION_UP:
                        System.out.println("klein------backward---ACTION_UP-----");
                        mPrintWriterClient.print("P");
                        mPrintWriterClient.flush();
                }
                return false;
            }
        });


        turnleft.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();
                switch(action)
                {
                    case MotionEvent.ACTION_DOWN:
                        System.out.println("klein------turnleft---ACTION_UP-----");
                        mPrintWriterClient.print("A");
                        mPrintWriterClient.flush();
                        break;
                    case MotionEvent.ACTION_UP:
                        System.out.println("klein------turnleft---ACTION_UP-----");
                        mPrintWriterClient.print("P");
                        mPrintWriterClient.flush();
                }
                return false;
            }

        });

        turnright.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();
                switch(action)
                {
                    case MotionEvent.ACTION_DOWN:
                        System.out.println("klein------turnright---ACTION_UP-----");
                        mPrintWriterClient.print("D");
                        mPrintWriterClient.flush();
                        break;
                    case MotionEvent.ACTION_UP:
                        System.out.println("klein------turnright---ACTION_UP-----");
                        mPrintWriterClient.print("P");
                        mPrintWriterClient.flush();
                }
                return false;
            }

        });
    }

    private Runnable mRunnable	= new Runnable() {
        public void run() {

            String msgText ="192.168.1.1:2001";

            int start = msgText.indexOf(":");

            String sIP = msgText.substring(0, start);
            String sPort = msgText.substring(start+1);
            int port = Integer.parseInt(sPort);


            try{
                //连接服务器
                System.out.println("klein---connecting----");
                mSocketClient = new Socket(sIP, port);	//portnum
                System.out.println("klein---connected----");
                //取得输入、输出流
                mBufferedReaderClient = new BufferedReader(new InputStreamReader(mSocketClient.getInputStream()));
                mPrintWriterClient = new PrintWriter(mSocketClient.getOutputStream(), true);

                System.out.println("klein------------mPrintWriterClient = " + mPrintWriterClient);

            }catch (Exception e){
                e.printStackTrace();
            }

        }

    };
}

package com.example.skylar.wificar;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


/**
 * Created by klein on 2018/3/18.
 */

public class CommandSender extends Thread implements CommandInterface {

    public static final String TAG = "WifiCar.CommandSender";
    static PrintWriter mPrintWriterClient = null;
    private Socket mSocketClient = null;
    static BufferedReader mBufferedReaderClient	= null;
    Handler commandSenderHander;




    public CommandSender(){
        Log.i(TAG, "CommandSender construtor");

    }

    public Handler getHander(){
        return commandSenderHander;
    }

    public void run() {

        String msgText ="192.168.0.106:5000";

        int start = msgText.indexOf(":");

        String sIP = msgText.substring(0, start);
        String sPort = msgText.substring(start+1);
        int port = Integer.parseInt(sPort);

        try{
            //连接服务器
            Log.i(TAG, "klein---connecting----");
            mSocketClient = new Socket(sIP, port);	//portnum
            Log.i(TAG, "klein---connected----");
            //取得输入、输出流
            mBufferedReaderClient = new BufferedReader(new InputStreamReader(mSocketClient.getInputStream()));
            mPrintWriterClient = new PrintWriter(mSocketClient.getOutputStream(), true);

            Log.i(TAG, "klein------------mPrintWriterClient = " + mPrintWriterClient);

        }catch (Exception e){
            e.printStackTrace();
        }

        //mPrintWriterClient.print("hello");
        //mPrintWriterClient.flush();

        Looper.prepare();
        Log.i(TAG, "init handler");
        commandSenderHander = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                Log.i(TAG, "handleMessage, msg.what = " +msg.what);
                switch (msg.what) {
                    case INT_COMMAND_TURN_LEFT:
                        Log.i(TAG, "send left");
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_LEFT);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_RIGHT:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_RIGHT);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_UP:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_UP);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_DOWN:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_DOWN);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_ACC:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_ACC);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_DEC:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_DEC);
                        mPrintWriterClient.flush();
                        break;
                    case INT_COMMAND_TURN_STOP:
                        mPrintWriterClient.print(CommandInterface.COMMAND_TURN_STOP);
                        mPrintWriterClient.flush();
                        break;
                    default:
                        break;
                }
            }
        };

        Looper.loop();


    }

    private class CommandSenderHander extends Handler{
        public CommandSenderHander(){
        }


    }
}



package com.example.skylar.wificar;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class WifiCar extends AppCompatActivity{
     public static final String TAG = "WifiCar";
    Button forward, backward, turnleft, turnright, acc, dec, light_on, light_off;

    Handler handler;
    CommandSender commandSender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wifi_car);
        forward = (Button) findViewById(R.id.forward);
        backward = (Button) findViewById(R.id.backward);
        turnleft = (Button) findViewById(R.id.turnleft);
        turnright = (Button) findViewById(R.id.turnright);
        acc = (Button) findViewById(R.id.acc);
        dec = (Button) findViewById(R.id.dec);
        light_on = (Button) findViewById(R.id.light_on);
        light_off = (Button) findViewById(R.id.light_off);

        Log.i(TAG, "onCreate");

        commandSender = new CommandSender();
        commandSender.start();
        try{
            Thread.sleep(1000);
        }catch (Exception e){

        }
        handler = commandSender.getHander();
        Log.i(TAG, "handler = " + handler);


        forward.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();


                switch(action)
                {
                    case MotionEvent.ACTION_DOWN:
                        Log.i(TAG, "klein------forward---ACTION_DOWN-----");
                        Message msg = Message.obtain();
                        msg.what = CommandInterface.INT_COMMAND_TURN_UP;
                        handler.sendMessage(msg);
                        break;
                    case MotionEvent.ACTION_UP:
                        Log.i(TAG, "klein------forward---ACTION_UP-----");
                        Message msg1 = Message.obtain();
                        msg1.what = CommandInterface.INT_COMMAND_TURN_STOP;
                        handler.sendMessage(msg1);
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
                        Log.i(TAG, "klein------backward---ACTION_DOWN-----");
                        Message msg = Message.obtain();
                        msg.what = CommandInterface.INT_COMMAND_TURN_DOWN;
                        handler.sendMessage(msg);
                        break;
                    case MotionEvent.ACTION_UP:
                        Log.i(TAG, "klein------backward---ACTION_UP-----");
                        Message msg1 = Message.obtain();
                        msg1.what = CommandInterface.INT_COMMAND_TURN_STOP;
                        handler.sendMessage(msg1);
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
                        Log.i(TAG, "klein------turnleft---ACTION_UP-----");
                        Message msg = Message.obtain();
                        msg.what = CommandInterface.INT_COMMAND_TURN_LEFT;
                        handler.sendMessage(msg);

                        break;
                    case MotionEvent.ACTION_UP:
                        Log.i(TAG, "klein------turnleft---ACTION_UP-----");
                        Message msg1 = Message.obtain();
                        msg1.what = CommandInterface.INT_COMMAND_TURN_STOP;
                        handler.sendMessage(msg1);
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
                        Log.i(TAG, "klein------turnright---ACTION_UP-----");
                        Message msg = Message.obtain();
                        msg.what = CommandInterface.INT_COMMAND_TURN_RIGHT;
                        handler.sendMessage(msg);
                        break;
                    case MotionEvent.ACTION_UP:
                        Log.i(TAG, "klein------turnright---ACTION_UP-----");
                        Message msg1 = Message.obtain();
                        msg1.what = CommandInterface.INT_COMMAND_TURN_STOP;
                        handler.sendMessage(msg1);
                }
                return false;
            }

        });

        acc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "klein------acc---");
                Message msg = Message.obtain();
                msg.what = CommandInterface.INT_COMMAND_TURN_ACC;
                handler.sendMessage(msg);
            }
        });

        dec.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "klein------dec---");
                Message msg = Message.obtain();
                msg.what = CommandInterface.INT_COMMAND_TURN_DEC;
                handler.sendMessage(msg);
            }
        });

        light_on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "klein-----led on---");

            }
        });

        light_off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "klein------led off---");

            }
        });
    }


}

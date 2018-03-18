package com.zhoukaihffoxmail.smartcarthings;

import android.app.Activity;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;

import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.GpioCallback;
import com.google.android.things.pio.PeripheralManagerService;
import com.google.android.things.pio.Pwm;

import java.io.IOException;
import java.util.LinkedHashMap;
import java.util.Map;



public class SmartCarThings extends Activity {
    private static final String TAG = "SmartCarThings";

    GpioControl gpioControl;
    CommandReceiver commandReceiver;
    Button btEngineStart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_smart_car_things);

        gpioControl = new GpioControl();
        commandReceiver = new CommandReceiver(gpioControl.GetHandler());

        btEngineStart = (Button) findViewById(R.id.enginestart);


    }
}

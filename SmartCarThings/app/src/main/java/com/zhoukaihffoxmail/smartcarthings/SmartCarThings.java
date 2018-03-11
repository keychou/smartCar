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

    private static final String LED_PIN_NAME = "BCM4";

    //moto control
    public static final String MOTO_A1C1 = "BCM5";
    public static final String MOTO_A2C2 = "BCM6";
    public static final String MOTO_B1D1 = "BCM17";
    public static final String MOTO_B2D2 = "BCM27";

    //PWM0
    private static final String MOTO_PWM = "PWM1";

    public Gpio mMotoA1C1Gpio;
    public Gpio mMotoA2C2Gpio;
    public Gpio mMotoB1D1Gpio;
    public Gpio mMotoB2D2Gpio;
    public Pwm mMotoPwm;

    Button btEngineStart;

    PeripheralManagerService pioService = new PeripheralManagerService();

     //public Gpio mLedGpio;
    //Button open, close;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_smart_car_things);
        //open = (Button) findViewById(R.id.open);
        //close = (Button) findViewById(R.id.close);
        getGpioInfo();
        btEngineStart = (Button) findViewById(R.id.enginestart);

        try {
            mMotoA1C1Gpio = pioService.openGpio(MOTO_A1C1);
            mMotoA1C1Gpio.setEdgeTriggerType(Gpio.EDGE_NONE);
            mMotoA1C1Gpio.setActiveType(Gpio.ACTIVE_HIGH);
            mMotoA1C1Gpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);

            mMotoA2C2Gpio = pioService.openGpio(MOTO_A2C2);
            mMotoA2C2Gpio.setEdgeTriggerType(Gpio.EDGE_NONE);
            mMotoA2C2Gpio.setActiveType(Gpio.ACTIVE_HIGH);
            mMotoA2C2Gpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);

            mMotoB1D1Gpio = pioService.openGpio(MOTO_B1D1);
            mMotoB1D1Gpio.setEdgeTriggerType(Gpio.EDGE_NONE);
            mMotoB1D1Gpio.setActiveType(Gpio.ACTIVE_HIGH);
            mMotoB1D1Gpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);

            mMotoB2D2Gpio = pioService.openGpio(MOTO_B2D2);
            mMotoB2D2Gpio.setEdgeTriggerType(Gpio.EDGE_NONE);
            mMotoB2D2Gpio.setActiveType(Gpio.ACTIVE_HIGH);
            mMotoB2D2Gpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);

            mMotoPwm = pioService.openPwm(MOTO_PWM);

        }catch (Exception e){
            e.printStackTrace();
        }

        btEngineStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG, "engine start");
                try{
                    mMotoA1C1Gpio.setValue(false);
                    mMotoA2C2Gpio.setValue(true);
                    mMotoB1D1Gpio.setValue(true);
                    mMotoB2D2Gpio.setValue(false);

                    mMotoPwm.setPwmFrequencyHz(100);
                    mMotoPwm.setPwmDutyCycle(50);
                    mMotoPwm.setEnabled(true);
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        });




//        try {
//            mLedGpio = pioService.openGpio(LED_PIN_NAME);
//
//            mLedGpio.setEdgeTriggerType(Gpio.EDGE_NONE);
//            mLedGpio.setActiveType(Gpio.ACTIVE_HIGH);
//            mLedGpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);
//
//        } catch (IOException e) {
//            Log.e(TAG, "Error configuring GPIO pins", e);
//
//        }

//        open.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                setLedValue(true);
//            }
//        });
//
//        close.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                setLedValue(false);
//            }
//        });


    }


//    void GpioRealease(Gpio gpio){
//        if (gpio != null) {
//            try {
//                gpio.close();
//
//            } catch (IOException e) {
//                Log.e(TAG, "Error closing LED GPIO", e);
//            } finally{
//                gpio = null;
//            }
//            gpio = null;
//        }
//    }
//
//    void PwmRealease(Pwm pwm){
//        if (pwm != null) {
//            try {
//                pwm.close();
//
//            } catch (IOException e) {
//                Log.e(TAG, "Error closing LED GPIO", e);
//            } finally{
//                pwm = null;
//            }
//            pwm = null;
//        }
//    }
//
//
//    @Override
//    protected void onDestroy() {
//        super.onDestroy();
//        Log.d(TAG, "----------------onDestroy--------------------");
//        GpioRealease(mMotoA1C1Gpio);
//        GpioRealease(mMotoA2C2Gpio);
//        GpioRealease(mMotoB1D1Gpio);
//        GpioRealease(mMotoB2D2Gpio);
//        PwmRealease(mMotoPwm);
//
//    }

    void getGpioInfo(){
        int i = 1;
        for (String name : pioService.getGpioList()) {
            Log.d(TAG, "i = " + (i++) + ", GPIO: " + name);
        }

        for (String name : pioService.getPwmList()) {
            Log.d(TAG, "PWM: " + name);
        }

        for (String name : pioService.getI2cBusList()) {
            Log.d(TAG, "I2C: " + name);
        }


        for (String name : pioService.getUartDeviceList()) {
            Log.d(TAG, "uart device: " + name);
        }

        for (String name : pioService.getSpiBusList()) {
            Log.d(TAG, "spi: " + name);
        }
    }
}

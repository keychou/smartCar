package com.zhoukaihffoxmail.smartcarthings;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.PeripheralManagerService;
import com.google.android.things.pio.Pwm;

import java.security.spec.ECField;


/**
 * Created by klein on 2018/3/13.
 */

public class GpioControl {
    private static final String TAG = "SCThings.GpioControl";
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

    private int dutyCycle = 50;
    private int dutyGrad = 10;

    GcHandler gcHandler;

    public static final String COMMAND_TURN_LEFT = "A";
    public static final String COMMAND_TURN_RIGHT = "D";
    public static final String COMMAND_TURN_UP = "W";
    public static final String COMMAND_TURN_DOWN = "S";
    public static final String COMMAND_TURN_ACC = "U";
    public static final String COMMAND_TURN_DEC = "N";
    public static final String COMMAND_TURN_STOP = "P";

    public static final int INT_COMMAND_BASE = 0x01;
    public static final int INT_COMMAND_TURN_LEFT = INT_COMMAND_BASE + 1;
    public static final int INT_COMMAND_TURN_RIGHT = INT_COMMAND_BASE + 2;
    public static final int INT_COMMAND_TURN_UP = INT_COMMAND_BASE + 3;
    public static final int INT_COMMAND_TURN_DOWN = INT_COMMAND_BASE + 4;
    public static final int INT_COMMAND_TURN_ACC = INT_COMMAND_BASE + 5;
    public static final int INT_COMMAND_TURN_DEC = INT_COMMAND_BASE + 6;
    public static final int INT_COMMAND_TURN_STOP = INT_COMMAND_BASE + 7;

    int getCommandId(String commandstring){
         if (commandstring.equals(COMMAND_TURN_LEFT)){
             return INT_COMMAND_TURN_LEFT;
         } else if (commandstring.equals(COMMAND_TURN_RIGHT)){
             return INT_COMMAND_TURN_RIGHT;
         } else if (commandstring.equals(COMMAND_TURN_UP)){
             return INT_COMMAND_TURN_UP;
         } else if (commandstring.equals(COMMAND_TURN_DOWN)){
             return INT_COMMAND_TURN_DOWN;
         }else if (commandstring.equals(COMMAND_TURN_ACC)){
             return INT_COMMAND_TURN_ACC;
         } else if (commandstring.equals(COMMAND_TURN_DEC)){
             return INT_COMMAND_TURN_DEC;
         } else if (commandstring.equals(COMMAND_TURN_STOP)){
             return INT_COMMAND_TURN_STOP;
         }

         return -1;
    }

    PeripheralManagerService pioService = new PeripheralManagerService();

    public GpioControl(){
        MotoInit();
        gcHandler = new GcHandler();
    }

    Handler GetHandler(){
        return gcHandler;
    }

    public class GcHandler extends Handler{

        public GcHandler(){
        }

        @Override
        public void handleMessage(Message msg) {

            switch (msg.what) {
                case INT_COMMAND_TURN_LEFT:
                    Log.i(TAG, "left");
                    MotoTurn(true);
                    break;
                case INT_COMMAND_TURN_RIGHT:
                    Log.i(TAG, "right");
                    MotoTurn(false);
                    break;
                case INT_COMMAND_TURN_UP:
                    Log.i(TAG, "up");
                    MotoStart(true);
                    break;
                case INT_COMMAND_TURN_DOWN:
                    Log.i(TAG, "down");
                    MotoStart(false);
                    break;
                case INT_COMMAND_TURN_ACC:
                    Log.i(TAG, "acc");
                    MotoAcc();
                    break;
                case INT_COMMAND_TURN_DEC:
                    Log.i(TAG, "dec");
                    MotoDec();
                    break;
                case INT_COMMAND_TURN_STOP:
                    Log.i(TAG, "stop");
                    try{
                        mMotoPwm.setEnabled(false);
                    }catch (Exception e){
                        e.printStackTrace();
                    }
                    break;
                default:
                    break;
            }
        }
    }


    void MotoInit(){
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
            mMotoPwm.setPwmFrequencyHz(100);

        }catch (Exception e){
            e.printStackTrace();
        }
    }

    void SetSpeed(boolean isacc, int cycle){
        Log.i(TAG, "isacc = " + isacc + ", cycle = " + cycle +", old dutyCycle = " + dutyCycle);
        if (isacc){
            try{
                if (dutyCycle <= 100 - cycle)
                    dutyCycle = dutyCycle + cycle;
            }catch (Exception e){
                e.printStackTrace();
            }
        } else {
            try{
                if (cycle <= dutyCycle)
                    dutyCycle = dutyCycle - cycle;
            }catch (Exception e){
                e.printStackTrace();
            }
        }

        Log.i(TAG, "new dutyCycle = " + dutyCycle);
    }

    void MotoStart(boolean moveforward){
        try{
            mMotoA1C1Gpio.setValue(!moveforward);
            mMotoA2C2Gpio.setValue(moveforward);
            mMotoB1D1Gpio.setValue(!moveforward);
            mMotoB2D2Gpio.setValue(moveforward);
            mMotoPwm.setPwmDutyCycle(dutyCycle);
            mMotoPwm.setEnabled(true);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    void MotoTurn(boolean turnleft){
        try{
            mMotoA1C1Gpio.setValue(turnleft);
            mMotoA2C2Gpio.setValue(!turnleft);
            mMotoB1D1Gpio.setValue(!turnleft);
            mMotoB2D2Gpio.setValue(turnleft);
            mMotoPwm.setPwmDutyCycle(dutyCycle);
            mMotoPwm.setEnabled(true);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    void MotoAcc(){
        try{
            SetSpeed(true, dutyGrad);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    void MotoDec(){
        try{
            SetSpeed(false, dutyGrad);
        }catch (Exception e){
            e.printStackTrace();
        }
    }


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

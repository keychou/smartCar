package com.example.skylar.wificar;

/**
 * Created by klein on 2018/3/18.
 */

public interface CommandInterface {

    public static final String COMMAND_TURN_LEFT = "A\n";
    public static final String COMMAND_TURN_RIGHT = "D\n";
    public static final String COMMAND_TURN_UP = "W\n";
    public static final String COMMAND_TURN_DOWN = "S\n";
    public static final String COMMAND_TURN_ACC = "U\n";
    public static final String COMMAND_TURN_DEC = "N\n";
    public static final String COMMAND_TURN_STOP = "P\n";


    public static final int INT_COMMAND_BASE = 0x01;
    public static final int INT_COMMAND_TURN_LEFT = INT_COMMAND_BASE + 1;
    public static final int INT_COMMAND_TURN_RIGHT = INT_COMMAND_BASE + 2;
    public static final int INT_COMMAND_TURN_UP = INT_COMMAND_BASE + 3;
    public static final int INT_COMMAND_TURN_DOWN = INT_COMMAND_BASE + 4;
    public static final int INT_COMMAND_TURN_ACC = INT_COMMAND_BASE + 5;
    public static final int INT_COMMAND_TURN_DEC = INT_COMMAND_BASE + 6;
    public static final int INT_COMMAND_TURN_STOP = INT_COMMAND_BASE + 7;



}

package com.smartos.sensor.pojo;

public class Sensor {

    //数据结构
    private String imsi;   //IMSI号
    private String frameID; //帧号
    private String temp; //温度
    private String MCUtemp; //MCU温度
    private String humidity;//湿度
    private String light;//光照
    private String sound;//声音
    private String human;//人体感应
    private String led; //电灯
    private String fan; //风扇
    //private String state; //控制用电设备开关
    private Boolean sendState; //回发状态，用于判断是否可以回发

    //getter和setter
    public String getImsi() {
        return imsi;
    }

    public void setImsi(String imsi) {
        this.imsi = imsi;
    }

    public String getTemp() {
        return temp;
    }

    public void setTemp(String temp) {
        this.temp = temp;
    }

    public String getMCUtemp() {
        return MCUtemp;
    }

    public void setMCUtemp(String MCUtemp) {
        this.MCUtemp = MCUtemp;
    }

    public String getHumidity() {
        return humidity;
    }

    public void setHumidity(String humidity) {
        this.humidity = humidity;
    }

    public String getLight() {
        return light;
    }

    public void setLight(String light) {
        this.light = light;
    }

    public String getSound() {
        return sound;
    }

    public void setSound(String sound) {
        this.sound = sound;
    }

    public String getHuman() {
        return human;
    }

    public void setHuman(String human) {
        this.human = human;
    }

    public String getLed() {
        return led;
    }

    public void setLed(String led) {
        this.led = led;
    }

    public String getFan() {
        return fan;
    }

    public void setFan(String fan) {
        this.fan = fan;
    }

//    public String getState() {
//        return state;
//    }
//
//    public void setState(String state) {
//        this.state = state;
//    }

    public Boolean getSendState() {
        return sendState;
    }

    public void setSendState(Boolean sendState) {
        this.sendState = sendState;
    }

    public String getFrameID() {
        return frameID;
    }

    public void setFrameID(String frameID) {
        this.frameID = frameID;
    }
}

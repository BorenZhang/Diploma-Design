package com.smartos.sensor.pojo;

//传感器采集数据域
public class SensorData {
    public String type;
    public String value;
    public String name;
    public int size;
    public String otherName;
    public String wr;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getOtherName() {
        return otherName;
    }

    public void setOtherName(String otherName) {
        this.otherName = otherName;
    }

    public String getWr() {
        return wr;
    }

    public void setWr(String wr) {
        this.wr = wr;
    }
}
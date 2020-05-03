package com.smartos.sensor.pojo;

import java.util.ArrayList;
import java.util.List;

//对应json数据格式2
public class NBIOT_Format2 {
    public String command;
    public String source;
    public String dest;
    public String password;
    public int currentRow;
    public int totalRows;
    public List<SensorData> data=new ArrayList<SensorData>();

    public String getCommand() {
        return command;
    }

    public void setCommand(String command) {
        this.command = command;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getDest() {
        return dest;
    }

    public void setDest(String dest) {
        this.dest = dest;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public int getCurrentRow() {
        return currentRow;
    }

    public void setCurrentRow(int currentRow) {
        this.currentRow = currentRow;
    }

    public int getTotalRows() {
        return totalRows;
    }

    public void setTotalRows(int totalRows) {
        this.totalRows = totalRows;
    }

    public List<SensorData> getData() {
        return data;
    }

    public void setData(List<SensorData> data) {
        this.data = data;
    }
}
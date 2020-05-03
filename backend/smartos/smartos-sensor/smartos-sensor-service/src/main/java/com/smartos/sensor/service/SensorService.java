package com.smartos.sensor.service;

import com.google.gson.Gson;
import com.smartos.OpenDataCollection;
import com.smartos.sensor.pojo.NBIOT_Format2;
import com.smartos.sensor.pojo.Sensor;
import org.springframework.stereotype.Service;

@Service
public class SensorService {

    /**
     * 根据IMSI获取数据
     *
     * @param imsi
     * @return Sensor
     */
    public Sensor getDataByIMSI(String imsi) {
        if (OpenDataCollection.webSocketClientUtil.getSource().equals(imsi)) { //字符串比较用equals
            return OpenDataCollection.webSocketClientUtil.getSensor();
        } else return null;
    }


    /**
     * 远程控制风扇和电灯
     * @param sensor
     */
    public void sendMessage(Sensor sensor) {
        /**
         * 流程：
         *  step1: 获取最近的数据帧
         *  step2: 改造数据帧
         *  step3: 回发数据
         */
        //获取最近的数据帧
        NBIOT_Format2 message = OpenDataCollection.webSocketClientUtil.getNbiot_format2();
        //改造最近的数据帧
        message.command = "send";
        message.source = "web";
        message.dest = sensor.getImsi();
        message.data.get(28).value = sensor.getFan(); //更改风扇状态
        message.data.get(29).value = sensor.getLed(); //更改电灯状态
        //回发数据
        Gson gson=new Gson();
        String jsonMessage=gson.toJson(message);
        OpenDataCollection.webSocketClientUtil.send(jsonMessage);
        System.out.println(OpenDataCollection.webSocketClientUtil.getValue());
    }

    public Boolean getSendState() {
        return OpenDataCollection.webSocketClientUtil.getSensor().getSendState();
    }
}

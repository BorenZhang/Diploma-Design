package com.smartos.sensor.util;

import com.google.gson.Gson;
import com.smartos.sensor.pojo.NBIOT_Format1;
import com.smartos.sensor.pojo.NBIOT_Format2;
import com.smartos.sensor.pojo.Sensor;
import org.java_websocket.client.WebSocketClient;
import org.java_websocket.drafts.Draft;
import org.java_websocket.handshake.ServerHandshake;

import java.net.URI;

public class WebSocketClientUtil extends WebSocketClient {

    private static Sensor sensor=new Sensor();  //传感器状态

    private static String source;  //imsi号

    private static String value; //value值，即数据库中的行号

    private static NBIOT_Format1 nbiot_format1=null;

    private static NBIOT_Format2 nbiot_format2=null;

    public Sensor getSensor() {
        return sensor;
    }

    public String getSource() {
        return source;
    }

    public String getValue() {
        return value;
    }

    public static NBIOT_Format1 getNbiot_format1() {
        return nbiot_format1;
    }

    public static NBIOT_Format2 getNbiot_format2() {
        return nbiot_format2;
    }


    public WebSocketClientUtil(URI serverUri, Draft draft){
        super(serverUri,draft);
    }
    public WebSocketClientUtil(URI serverURI){
        super(serverURI);
    }

    @Override
    public void onOpen(ServerHandshake serverHandshake) {
        System.out.println("opened connection");
    }

    @Override
    public void onMessage(String s) {
        System.out.println(s);
        Gson gson = new Gson();
        /**
         * 根据接收到的帧的指令不同对帧进行不同的处理
         * 1.recv帧：帧结构-{"command":"recv","source":"460113003233156","password":"","value":"743"}
         *  1.1 过滤出source（及IMSI号），判断是否与参数对应
         *  1.2 过滤出value值（及帧号），以便之后获取对应帧的数据
         *  1.3 发送ask指令，请求对应帧的实时数据（需要重新组装帧）
         * 2.reAsk帧：
         *  2.1 过滤出传感器采集的数据
         *  2.2 为sensor赋值，并返回
         */
        if (s.contains("recv")) {  //服务器向客户端推送实时数据到来的通知
            nbiot_format1 = gson.fromJson(s, NBIOT_Format1.class);
            source=nbiot_format1.getSource(); //获取ismi号
            value=nbiot_format1.getValue();
            System.out.println(value);
            send("{" +
                            "\"command\":"+"\"ask\","+
                            "\"source\":"+"\"web\","+
                            "\"password\":"+"\"\","+
                            "\"value\":"+"\""+value+"\""+
                            "}");
            //sensor.setState("CAN_CHANGE_SWITCH"); //开启开关控制
            //发送心跳包，保持websocket通信不断开
            //send("shake");
        } else if (s.contains("reAsk")) {  //服务器向客户端发送实时数据或者历史数据
            nbiot_format2 = gson.fromJson(s, NBIOT_Format2.class);
            sensor.setImsi(nbiot_format2.getData().get(2).getValue());  //获取IMSI号
            sensor.setTemp(nbiot_format2.getData().get(23).getValue()); //获取温度
            float mcu_temp=Float.parseFloat(nbiot_format2.getData().get(14).getValue());
            sensor.setMCUtemp(Float.toString(mcu_temp/10)); //获取MCU温度
            //sensor.setHumidity("30");  //获取湿度
            sensor.setHumidity(Integer.toString((int)(Math.random()*(96-94)+94)));
            sensor.setLight(nbiot_format2.getData().get(24).getValue()); //获取光照强度
            sensor.setSound(nbiot_format2.getData().get(27).getValue()); //获取声音强度
            sensor.setHuman(nbiot_format2.getData().get(26).getValue()); //获取人体感应数据
            sensor.setLed(nbiot_format2.getData().get(29).getValue()); //获取电灯状态
            sensor.setFan(nbiot_format2.getData().get(28).getValue()); //获取风扇状态
            sensor.setFrameID(nbiot_format2.getData().get(1).getValue());//获取帧号
        }
        else if(s.contains("SUCCESS")){  //客户端回发成功响应帧
            send("{" +
                    "\"command\":"+"\"ask\","+
                    "\"source\":"+"\"web\","+
                    "\"password\":"+"\"\","+
                    "\"value\":"+"\""+value+"\""+
                    "}");
            //sensor.setState("NO_CHANGE_SWITCH");
        }
        else if(s.contains("CANSEND")){  //可以回发
            sensor.setSendState(true);
        }
        else if(s.contains("CANNOTSEND")){ //无法回发
            sensor.setSendState(false);
        }
    }

    @Override
    public void onClose(int i, String s, boolean b) {
        System.out.println("已关闭连接");
    }

    @Override
    public void onError(Exception e) {
        e.printStackTrace();
    }


}

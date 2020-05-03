package com.smartos.sensor.controller;

import com.smartos.sensor.pojo.Sensor;
import com.smartos.sensor.service.SensorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class SensorController {

    @Autowired
    private SensorService sensorService;


    /**
     * 根据ismi号获取数据
     * @param imsi
     * @return
     */
    @GetMapping("data")
    public ResponseEntity<Sensor> getDataByIMSI(@RequestParam("imsi")String imsi){

        //参数错误
        if (imsi == null || imsi.length() < 0) {
            // 响应400，相当于ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
            return ResponseEntity.badRequest().build();
        }
        Sensor sensor=this.sensorService.getDataByIMSI(imsi);
        if (sensor==null) {
            // 未获取到数据，响应404
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(sensor);
    }

    /**
     * 远程控制风扇和电灯
     * @param sensor
     * @return
     */
    @PostMapping("send")
    public ResponseEntity<Void> sendMessage(Sensor sensor){
        this.sensorService.sendMessage(sensor);
        return ResponseEntity.ok().build();
    }

    /**
     * 获取回发状态：判断是否可以回发
     * @return
     */
    @GetMapping("getSendState")
    public ResponseEntity<Boolean> getSendState(){
        Boolean state=this.sensorService.getSendState();
        return ResponseEntity.ok(state);
    }

}

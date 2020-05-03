package com.smartos;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import tk.mybatis.spring.annotation.MapperScan;

@SpringBootApplication
@EnableDiscoveryClient
@MapperScan("com.smartos.user.mapper")
public class SmartOSUserApplication {
    public static void main(String[] args) {
        SpringApplication.run(SmartOSUserApplication.class,args);
    }
}

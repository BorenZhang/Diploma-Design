package com.smartos;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;

@SpringBootApplication
@EnableDiscoveryClient
public class SmartOSSensorServiceApplication {
    public static void main(String[] args) {
        SpringApplication.run(SmartOSSensorServiceApplication.class,args);
    }
}

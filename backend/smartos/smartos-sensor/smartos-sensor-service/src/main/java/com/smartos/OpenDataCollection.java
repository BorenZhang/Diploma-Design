package com.smartos;

import com.smartos.sensor.util.WebSocketClientUtil;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.stereotype.Component;

import java.net.URI;

@Component
public class OpenDataCollection implements ApplicationRunner {



    public static WebSocketClientUtil webSocketClientUtil=null;

    @Override
    public void run(ApplicationArguments args) throws Exception {
            try {
                webSocketClientUtil=new WebSocketClientUtil(new URI("ws://121.41.100.186:38967/wsServices/"));
            } catch (Exception e) {
                e.printStackTrace();
            }
            webSocketClientUtil.connect();
    }
}

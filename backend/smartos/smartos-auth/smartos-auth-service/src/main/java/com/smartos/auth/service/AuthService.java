package com.smartos.auth.service;

import com.smartos.auth.client.UserClient;
import com.smartos.auth.config.JwtProperties;
import com.smartos.auth.test.pojo.UserInfo;
import com.smartos.auth.test.utils.JwtUtils;
import com.smartos.user.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.stereotype.Service;

@Service
@EnableConfigurationProperties(JwtProperties.class)

public class AuthService {

    @Autowired
    private UserClient userClient;

    @Autowired
    private JwtProperties jwtProperties;

    public String login(String username, String password) {
        //远程调用用户中心的查询接口，这也是使用feign的原因
        User user = this.userClient.queryUser(username, password);
        //判断用户是否为空
        if (user == null) {
            return null;
        }

        //初始化载荷对象
        UserInfo userInfo=new UserInfo();
        userInfo.setId(user.getId());
        userInfo.setUsername(user.getUsername());
        try {
            //生成jwt类型的token
            return JwtUtils.generateToken(userInfo,this.jwtProperties.getPrivateKey(),this.jwtProperties.getExpire());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

}

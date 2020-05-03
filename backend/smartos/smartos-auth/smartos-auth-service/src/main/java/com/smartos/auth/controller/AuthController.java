package com.smartos.auth.controller;

import com.smartos.auth.config.JwtProperties;
import com.smartos.auth.service.AuthService;
import com.smartos.auth.test.pojo.UserInfo;
import com.smartos.auth.test.utils.JwtUtils;
import com.smartos.common.utils.CookieUtils;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CookieValue;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Controller
public class AuthController {

    @Autowired
    private AuthService authService;

    @Autowired
    private JwtProperties jwtProperties;

    @PostMapping("login")
    public ResponseEntity<Void> login(
            @RequestParam("username") String username,
            @RequestParam("password") String password,
            HttpServletRequest request,
            HttpServletResponse response

    ) {
        //调用service方法生成jwt
        String token = this.authService.login(username, password);
        if (StringUtils.isBlank(token)) {
            return ResponseEntity.badRequest().build();
        }
        //使用cookieUtils.setCookie方法，把jwt类型的token设置给cookie
        CookieUtils.setCookie(request, response, "SMARTOS_TOKEN", token, this.jwtProperties.getExpire() * 60, "utf-8", true);
        return ResponseEntity.ok().build();

    }

    /**
     * 验证用户信息
     *
     * @param token
     * @return
     */
    @GetMapping("verify")
    public ResponseEntity<UserInfo> verify(
            @CookieValue("SMARTOS_TOKEN") String token,
            HttpServletRequest request,
            HttpServletResponse response
    ) {
        try {
            //从token中解析token的信息
            UserInfo userInfo = JwtUtils.getInfoFromToken(token, this.jwtProperties.getPublicKey());
            if (userInfo == null) {
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
            }
            //解析成功要重新刷新token,本质就是重新生成jwt
            token=JwtUtils.generateToken(userInfo,this.jwtProperties.getPrivateKey(),this.jwtProperties.getExpire());

            //更新cookie中的token
            CookieUtils.setCookie(request,response,"SMARTOS_TOKEN",token,this.jwtProperties.getExpire()*60,null,true);
            //解析成功返回用户信息
            return ResponseEntity.ok(userInfo);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
        }
    }

}

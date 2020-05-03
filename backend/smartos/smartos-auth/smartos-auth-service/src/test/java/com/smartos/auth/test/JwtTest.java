package com.smartos.auth.test;

import com.smartos.auth.test.pojo.UserInfo;
import com.smartos.auth.test.utils.JwtUtils;
import com.smartos.auth.test.utils.RsaUtils;
import org.junit.Before;
import org.junit.Test;

import java.security.PrivateKey;
import java.security.PublicKey;

public class JwtTest {

    private static final String pubKeyPath = "C:\\tmp\\rsa\\rsa.pub";

    private static final String priKeyPath = "C:\\tmp\\rsa\\rsa.pri";

    private PublicKey publicKey;

    private PrivateKey privateKey;

    @Test
    public void testRsa() throws Exception {
        RsaUtils.generateKey(pubKeyPath, priKeyPath, "234");
    }

    @Before
    public void testGetRsa() throws Exception {
        this.publicKey = RsaUtils.getPublicKey(pubKeyPath);
        this.privateKey = RsaUtils.getPrivateKey(priKeyPath);
    }

    @Test
    public void testGenerateToken() throws Exception {
        // 生成token
        String token = JwtUtils.generateToken(new UserInfo(20L, "jack"), privateKey, 5);
        System.out.println("token = " + token);
    }

    @Test
    public void testParseToken() throws Exception {
        String token = "eyJhbGciOiJSUzI1NiJ9.eyJpZCI6MjAsInVzZXJuYW1lIjoiamFjayIsImV4cCI6MTU4NTUzMzgwOX0.ZAR4am920oPna0XpuWgZ_Tzx06NDEZLrFEYkMkzPZ3DXTyR1WA4fuNJP2AzriwChdqAvRQ6MWBJTg9oi9e9jHv9fMEObX_Ujc9PH4amtSzBOwG-IURJa01xymYfv4LP813QXkIEvuIIsO7UzAzLAz3bDha805pNLyp6L3Bvie1Q";

        // 解析token
        UserInfo user = JwtUtils.getInfoFromToken(token, publicKey);
        System.out.println("id: " + user.getId());
        System.out.println("userName: " + user.getUsername());
    }
}
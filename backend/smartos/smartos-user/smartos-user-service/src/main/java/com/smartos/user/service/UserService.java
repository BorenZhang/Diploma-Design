package com.smartos.user.service;

import com.smartos.user.mapper.UserMapper;
import com.smartos.user.pojo.User;
import com.smartos.utils.CodecUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;

@Service
public class UserService {

    @Autowired
    private UserMapper userMapper;

    public Boolean checkData(String data, Integer type) {
        User record = new User();
        switch (type) {
            case 1:
                record.setUsername(data);
                break;
            case 2:
                record.setPhone(data);
                break;
            default:
                return null;
        }
        return this.userMapper.selectCount(record) == 0; //这是个判断语句！！如果等于0，结果返回true，说明数据库中没有该用户，允许注册；如果不等于0，说明已经存在该用户，不允许注册。
    }

    public Boolean register(User user) {

        //生成盐
        String salt = CodecUtils.generateSalt();
        user.setSalt(salt);

        //对密码加密
        user.setPassword(CodecUtils.md5Hex(user.getPassword(), salt));

        //强制设置不能制定的参数为null
        user.setId(null);
        user.setCreated(new Date());

        //添加到数据库
        boolean b = this.userMapper.insertSelective(user) == 1;

        return b;
    }

    public User queryUser(String username, String password) {

        //查询
        User record = new User();
        record.setUsername(username);
        User user = this.userMapper.selectOne(record);
        //校验用户名
        if (user == null) {
            return null;
        }
        //校验密码
        if (!user.getPassword().equals(CodecUtils.md5Hex(password, user.getSalt()))) {
            String salt=user.getSalt();
            String s=CodecUtils.md5Hex(password, salt);
            return null;
        }
        return user;
    }
}

package com.smartos.gateway.filter;

import com.netflix.zuul.ZuulFilter;
import com.netflix.zuul.context.RequestContext;
import com.netflix.zuul.exception.ZuulException;
import com.smartos.auth.test.utils.JwtUtils;
import com.smartos.common.utils.CookieUtils;
import com.smartos.gateway.config.FilterProperties;
import com.smartos.gateway.config.JwtProperties;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Component;

import javax.servlet.http.HttpServletRequest;

@Component //将过滤器放入spring容器
@EnableConfigurationProperties({JwtProperties.class, FilterProperties.class})
public class LoginFilter extends ZuulFilter {

    @Autowired
    private JwtProperties jwtProperties;

    @Autowired
    private FilterProperties filterProperties;

    @Override
    public String filterType() {
        return "pre"; //声明为前置过滤
    }

    @Override
    public int filterOrder() {
        return 10;  //过滤器执行顺序
    }

    @Override
    public boolean shouldFilter() {
        //初始化zuul上下文对象
        RequestContext context = RequestContext.getCurrentContext();
        HttpServletRequest request = context.getRequest();

        //获取完整请求路径，包含域名
        String url = request.getRequestURI().toString();  //注意此处的url为完整路径
        //遍历白名单，判断完整路径是否包含某个白名单片段
        for (String path : this.filterProperties.getAllowPaths()){
            if(url.contains(path)){
                return false;
            }
        }
        return true;   //激活run方法
    }

    @Override
    public Object run() throws ZuulException {
        //初始化zuul上下文对象
        RequestContext context = RequestContext.getCurrentContext();
        HttpServletRequest request = context.getRequest();
        //获取cookie中的token信息
        String token = CookieUtils.getCookieValue(request, this.jwtProperties.getCookieName());

        try {
            JwtUtils.getInfoFromToken(token,this.jwtProperties.getPublicKey());
        } catch (Exception e) {
            e.printStackTrace();
            context.setSendZuulResponse(false);  //不转发请求
            context.setResponseStatusCode(HttpStatus.UNAUTHORIZED.value()); //设置响应状态码为401
        }
        return null;
    }
}

import Vue from 'vue'
import Router from 'vue-router'


Vue.use(Router)

function route(path, file, name, children) {
    return {
        exact: true,
        path,
        name,
        children,
        component: () => import('../pages' + file)
    }
}

export default new Router({
    routes: [
        route("/login", '/Login', "Login"),// /login路径，路由到登录组件
        route("/register", '/Register', "Register"),// /Register路径，路由到注册组件
        {
            path: "/", // 根路径，路由到 Layout组件
            component: () => import('../pages/Layout'),
            redirect: "/Login",
            children: [ // 其它所有组件都是 Layout的子组件
                route("/index/dashboard", "/Dashboard", "Dashboard"),
                route("/config/sensor", '/config/Sensor', "Sensor"),
                route("/item/category", '/item/Category', "Category"),
                route("/item/brand", '/item/Brand', "Brand"),
                route("/item/list", '/item/Goods', "Goods"),
                route("/item/specification", '/item/specification/Specification', "Specification"),
                route("/user/statistics", '/item/Statistics', "Statistics"),
                route("/trade/promotion", '/trade/Promotion', "Promotion"),
                route("/authority/profile",'/user/Profile',"Profile"),
            ]
        }
    ]
})

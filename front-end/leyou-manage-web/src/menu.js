var menus = [
    {
        action: "home",
        title: "首页",
        path: "/index",
        items: [{title: "统计", path: "/dashboard"}]
    },
    {
        action: "settings",
        title: "配置",
        path: "/config",
        items: [
            {title: "终端配置", path: "/sensor"},

        ]
    },
    // {
    //   action: "people",
    //   title: "会员管理",
    //   path:"/user",
    //   items: [
    //     { title: "会员统计", path: "/statistics" },
    //     { title: "会员管理", path: "/list" }
    //   ]
    // },
    {
        action: "settings",
        title: "个人中心",
        path: "/authority",
        items: [
            {title: "详细资料", path: "/profile"},
        ]
    }
]

export default menus;

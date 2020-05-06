<template>
    <v-app :dark="dark">
        <!-- 左侧导航条 -->
        <v-navigation-drawer
                :dark="dark"
                persistent
                :mini-variant="miniVariant"
                v-model="drawer"
                disable-resize-watcher
                fixed
                app

        >
            <v-toolbar flat class="transparent">
                <v-list class="pa-0">
                    <v-list-tile avatar v-if="user && user.username">
                        <v-list-tile-avatar>
                            <img src="../assets/2.jpeg">
                        </v-list-tile-avatar>
                        <v-list-tile-content>
                            <v-list-tile-title>{{user.username}}</v-list-tile-title>
                        </v-list-tile-content>
                    </v-list-tile>
                    <v-list-tile avatar v-else>
                        <v-list-tile-content>
                            <v-list-tile-title>您还未登录，请<a @click="goToLogin">登录</a></v-list-tile-title>
                        </v-list-tile-content>
                    </v-list-tile>
                </v-list>
            </v-toolbar>
            <v-divider/>
            <!-- 左侧菜单 -->
            <v-list class="pt-0" dense expand>
                <v-list-tile
                        to="/index/dashboard"
                        class="my-2">
                    <v-icon class="mr-5" medium>home</v-icon>
                    <span>首页</span>
                </v-list-tile>
                <v-list-tile
                        to="/config/sensor"
                        class="my-2">
                    <v-icon class="mr-5" medium>settings</v-icon>
                    <span>终端配置</span>
                </v-list-tile>
                <v-list-tile
                        to="/authority/profile"
                        class="my-2">
                    <v-icon class="mr-5" medium>person</v-icon>
                    <span>个人中心</span>
                </v-list-tile>
                <!--<v-list-group-->
                <!--v-model="item.active"-->
                <!--v-for="item in items"-->
                <!--:key="item.title"-->
                <!--:prepend-icon="item.action"-->
                <!--no-action-->
                <!--&gt;-->
                <!--&lt;!&ndash;一级菜单 &ndash;&gt;-->
                <!--<v-list-tile slot="activator">-->
                <!--<v-list-tile-content>-->
                <!--<v-list-tile-title>{{ item.title }}</v-list-tile-title>-->
                <!--</v-list-tile-content>-->
                <!--</v-list-tile>-->
                <!--&lt;!&ndash; 二级菜单 &ndash;&gt;-->
                <!--<v-list-tile v-for="subItem in item.items" :key="subItem.title" :to="item.path + subItem.path">-->
                <!--<v-list-tile-content>-->
                <!--<v-list-tile-title>{{ subItem.title }}</v-list-tile-title>-->
                <!--</v-list-tile-content>-->
                <!--<v-list-tile-action>-->
                <!--<v-icon>{{ subItem.action }}</v-icon>-->
                <!--</v-list-tile-action>-->
                <!--</v-list-tile>-->
                <!--</v-list-group>-->
            </v-list>
        </v-navigation-drawer>
        <!-- 顶部工具条 -->
        <v-toolbar
                app
                dark
                :color="dark ? 'secondary' : 'primary'"
        >
            <!-- 隐藏左侧菜单的按钮-->
            <v-toolbar-side-icon @click.stop="drawer = !drawer"/>
            <!-- 收起左侧菜单的按钮-->
            <v-btn icon @click.stop="miniVariant = !miniVariant">
                <v-icon v-html="miniVariant ? 'chevron_right' : 'chevron_left'"/>
            </v-btn>
            <!-- 切换黑暗主题 -->
            <v-flex xs1>
                <v-switch
                        :label="dark ? '暗黑' : '明亮'"
                        v-model="dark"
                        color="dark"
                        hide-details
                />
            </v-flex>
            <!-- 顶部导航标题 -->
            <v-flex xs3></v-flex>
            <v-toolbar-title v-text="title"/>
            <v-spacer/>

            <!-- 调色板 -->
            <v-btn icon @click.stop="dark = !dark">
                <v-icon>invert_colors</v-icon>
            </v-btn>
            <!-- 顶部导航用户菜单 -->
            <v-btn icon @click.stop="dark = !dark">
                <v-icon>account_box</v-icon>
            </v-btn>
        </v-toolbar>
        <!--中间内容主体-->
        <v-content>
            <v-breadcrumbs>
                <v-icon slot="divider">chevron_right</v-icon>
                <v-breadcrumbs-item>{{item1}}</v-breadcrumbs-item>
                <v-breadcrumbs-item>{{item2}}</v-breadcrumbs-item>
            </v-breadcrumbs>
            <div>
                <!--定义一个路由锚点，Layout的子组件内容将在这里展示-->
                <router-view></router-view>
            </div>
        </v-content>
    </v-app>
</template>

<script>
    import menus from "../menu";

    export default {
        data() {
            return {
                dark: false,// 是否暗黑主题
                drawer: true,// 左侧导航是否隐藏
                miniVariant: false,// 左侧导航是否收起
                title: '智慧办公室',// 顶部导航条名称,
                menuMap: {},
                user: null
            }
        },
        computed: {
            items() {
                return menus;
            },
            item1() {
                const arr = this.$route.path.split("/");
                return this.menuMap[arr[1]].name;
            },
            item2() {
                const arr = this.$route.path.split("/");
                return this.menuMap[arr[1]][arr[2]];
            }
        },
        name: 'App',
        watch: {},
        created() {
            this.$http.get("/auth/verify").then(
                resp => {
                    this.user = resp.data;
                }
            )
            menus.forEach(m => {
                const p1 = m.path.slice(1);
                this.menuMap[p1] = {name: m.title};
                m.items.forEach(i => {
                    this.menuMap[p1][i.path.slice(1)] = i.title;
                })
            })
        },
        methods: {
            goToLogin() {
                this.$router.push("/Login");
            }
        }
    }
</script>

<style scoped>
    .box {
        width: 90%;
    }
</style>

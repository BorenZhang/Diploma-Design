<template>
    <v-app>
        <v-content>
            <v-container fluid fill-height>
                <v-layout align-center justify-center>
                    <v-flex xs12 sm8 md3>
                        <v-card class="elevation-12">
                            <v-toolbar dark color="primary">
                                <v-spacer></v-spacer>
                                <v-toolbar-title>智慧办公室系统登录</v-toolbar-title>
                                <v-spacer></v-spacer>
                            </v-toolbar>
                            <v-card-text>
                                <v-form>
                                    <v-text-field prepend-icon="person" v-model="username" label="用户名" type="text"/>
                                    <v-text-field
                                            prepend-icon="lock"
                                            v-model="password"
                                            label="密码"
                                            id="password"
                                            :append-icon="e1 ? 'visibility' : 'visibility_off'"
                                            :append-icon-cb="() => (e1 = !e1)"
                                            :type="e1 ? 'text' : 'password'"
                                    ></v-text-field>
                                </v-form>
                            </v-card-text>
                            <v-card-actions>
                                <v-btn color="primary" @click="doLogin" block="true">登录</v-btn>
                                <p style="width: 40%;text-align: right;margin-right: 10%;font-size: medium">还没有账号，去<a
                                        @click="toRegister">注册</a></p>
                            </v-card-actions>
                        </v-card>
                    </v-flex>
                </v-layout>
            </v-container>
        </v-content>
        <v-dialog v-model="dialog" width="300px">
            <v-alert icon="warning" color="error" :value="true">
                {{dialog_message}}
            </v-alert>
        </v-dialog>
    </v-app>
</template>

<script>
    export default {
        data: () => ({
            username: "",
            password: "",
            dialog: false,
            e1: false,
            dialog_message: '',
        }),
        methods: {
            doLogin() {
                if (!this.username || !this.password) {
                    this.dialog_message = "用户名和密码不能为空";
                    this.dialog = true;
                    return false;
                } else {
                    let form = {
                        username: '',
                        password: ''
                    }
                    form.username = this.username;
                    form.password = this.password;
                    this.$http.post("/auth/login", this.$qs.stringify(form))
                        .then(
                            resp => {
                                if (resp.status == 200) {
                                    this.$router.push("/index/Dashboard");
                                }
                            }
                        )
                        .catch(
                            () => {
                                this.dialog_message = "用户名或密码错误";
                                this.dialog = true;
                                return false;
                            }
                        )
                }
                console.log(this.username + " ... " + this.password);
            },
            toRegister() {
                this.$router.push("/Register");
            },
            loginTest() {
                if (!this.username || !this.password) {
                    this.dialog_message = "用户名和密码不能为空";
                    this.dialog = true;
                    return false;
                } else {
                    this.$router.push("/index/Dashboard");
                }

            }
        }
    };
</script>

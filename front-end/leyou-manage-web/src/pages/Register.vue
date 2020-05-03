<template>
    <v-app>
        <v-content>
            <v-container fluid fill-height>
                <v-layout align-center justify-center>
                    <v-flex xs12 sm8 md3>
                        <v-card class="elevation-12" light="true">
                            <v-toolbar dark color="primary">
                                <v-spacer></v-spacer>
                                <v-toolbar-title>智慧办公室系统注册</v-toolbar-title>
                                <v-spacer></v-spacer>
                            </v-toolbar>
                            <v-card-text>
                                <v-form v-model="valid" ref="RegisterForm">
                                    <!--注册表单-->
                                    <v-text-field prepend-icon="person" v-model="username" :rules="nameRules"
                                                  label="用户名" type="text" @blur="checkUsername"/>
                                    <v-spacer></v-spacer>
                                    <span style="color: red;">{{ usernamemessage }}</span>
                                    <v-text-field prepend-icon="phone" v-model="phone" :rules="phoneRules" label="手机号"
                                                  type="text" @blur="checkPhone"/>
                                    <span style="color: red;">{{ phonemessage }}</span>

                                    <v-text-field
                                            prepend-icon="lock"
                                            v-model="password"
                                            label="登录密码"
                                            id="password"
                                            :append-icon="e1 ? 'visibility' : 'visibility_off'"
                                            :append-icon-cb="() => (e1 = !e1)"
                                            :type="e1 ? 'text' : 'password'"
                                            :rules="passwordRules"
                                    ></v-text-field>
                                    <v-text-field
                                            prepend-icon="lock"
                                            v-model="confirm_password"
                                            label="确认密码"
                                            id="confirm_password"
                                            :append-icon="e2 ? 'visibility' : 'visibility_off'"
                                            :append-icon-cb="() => (e2 = !e2)"
                                            :type="e2 ? 'text' : 'password'"
                                            :rules="confirmPasswordRules"
                                    ></v-text-field>
                                </v-form>
                            </v-card-text>
                            <v-card-actions>
                                <v-btn color="primary" @click="doRegister" block="true">注册</v-btn>

                                <p style="width: 40%;text-align: right;margin-right: 10%;font-size: medium">已有账号，去<a @click="toLogin">登录</a></p>
                            </v-card-actions>
                        </v-card>
                    </v-flex>
                </v-layout>
            </v-container>
        </v-content>
    </v-app>
</template>

<script>
    export default {
        name: "Register",
        data: () => ({
            valid: false,
            username: '',
            nameRules: [
                v => !!v || '请输入用户名',
            ],
            phone: '',
            phoneRules: [
                v => !!v || '请输入手机号',
                v => /^1[35678]\d{9}$/.test(v) || '手机号不合法',
            ],
            password: '',
            passwordRules: [
                v => v.length >= 6 || '密码不能少于6位',
            ],
            confirm_password: '',
            usernamemessage: '',
            phonemessage: '',
        }),
        computed: {
            confirmPasswordRules() {
                const rules = []

                if (this.confirm_password) {
                    const rule =
                        v => (!!v && v) === this.password || '两次输入密码不一致'

                    rules.push(rule)
                }
                return rules
            }
        },
        watch: {
            password: 'validateField',
            confirm_password: 'validateField',  //声明用validateField函数监视confirm_password字段
        },
        methods: {
            validateField() {
                this.$refs.RegisterForm.validate() //检验输入是否符合规则
            },
            toLogin() {
                this.$router.push("/Login");
            },
            checkUsername() {
                this.$http.get("user/check/" + this.username + "/1")
                    .then(
                        resp => {
                            console.log(resp)

                            if (resp.data == false) {
                                this.usernamemessage = "用户名已存在，请更换";
                            } else {
                                this.usernamemessage = "";
                            }
                        }
                    )
            },
            checkPhone() {
                this.$http.get("user/check/" + this.phone + "/2")
                    .then(
                        resp => {
                            console.log(resp)

                            if (resp.data == false) {
                                this.phonemessage = "该手机号已被注册";
                            } else {
                                this.phonemessage = "";
                            }
                        }
                    )
            },
            doRegister() {
                if(this.$refs.RegisterForm.validate()){
                    //因为后台接受的是user对象，所以此处需要将参数封装为user对象
                    let user = {
                        username:'',
                        password:'',
                        phone: ''
                    }
                    user.username=this.username;
                    user.password=this.password;
                    user.phone=this.phone;

                    //发送请求
                    this.$http.post("/user/register",this.$qs.stringify(user))
                        .then(
                            resp=>{
                                if(resp.status==201){
                                    // 注册成功
                                    alert("注册成功,即将跳转到登录页！");
                                    setTimeout(() => this.$router.push("/Login"), 2000);
                                }
                            }
                        )
                        .catch(()=>alert("注册失败"))
                }


            }

        }
    }
</script>

<style scoped>

</style>
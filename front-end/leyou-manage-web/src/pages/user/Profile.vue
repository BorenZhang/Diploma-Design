<template>
    <v-container fluid>
        <v-layout row align-start justify-center>
            <v-flex xs12 sm5 md3 class="mr-3">
                <v-card>
                    <v-container>
                        <v-layout row wrap>
                            <v-flex>
                                <v-icon>person</v-icon>
                                <span class="body-1">about me</span>
                            </v-flex>
                        </v-layout>
                        <!--分隔条-->
                        <v-divider class="my-2"></v-divider>
                        <v-layout row wrap align-center justify-center class="mb-2">
                            <v-avatar
                                    size="150"
                                    color="grey lighten-4"
                            >
                                <img src="../../assets/2.jpeg" alt="avatar">
                            </v-avatar>
                        </v-layout>
                        <v-layout row wrap align-center justify-center class="mb-2">
                            <span>super admin</span>
                        </v-layout>
                        <v-layout row wrap class="mb-2">
                            <v-flex>
                                <v-icon>library_books</v-icon>
                                <span class="body-1">Education</span>
                            </v-flex>
                        </v-layout>
                        <!--分隔条-->
                        <v-divider class="my-2"></v-divider>
                        <v-layout row wrap class="mb-4">
                            <span class="body-2">nantong university JS in Computer Science from the University of Technology</span>
                        </v-layout>
                        <v-layout row wrap>
                            <v-flex>
                                <v-icon>poll</v-icon>
                                <span class="body-1">skills</span>
                            </v-flex>
                        </v-layout>
                        <!--分隔条-->
                        <v-divider class="my-2"></v-divider>
                        <v-layout row wrap>
                            <v-flex xs12 sm12 md12>
                                <span class="subheading">java</span>
                                <v-progress-linear value="30" color="blue"></v-progress-linear>
                            </v-flex>
                            <v-flex xs12 sm12 md12>
                                <span class="subheading">Vue</span>
                                <v-progress-linear value="50" color="green"></v-progress-linear>
                            </v-flex>
                            <v-flex xs12 sm12 md12>
                                <span class="subheading">python</span>
                                <v-progress-linear value="60" color="yellow"></v-progress-linear>
                            </v-flex>
                            <v-flex xs12 sm12 md12>
                                <span class="subheading">javascript</span>
                                <v-progress-linear value="20" color="red"></v-progress-linear>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <v-flex xs12 sm7 md9>
                <v-card>
                    <v-container>
                        <v-layout>
                            <v-flex>
                                <span class="headline">Account</span>
                                <!--分隔条-->
                                <v-divider class="my-3"></v-divider>
                                <span class="title">用户名:</span>
                                <v-text-field
                                        v-model="name"
                                        :rules="nameRules"
                                        :counter="10"
                                        label="Name"
                                        required
                                        solo
                                        class="my-3"
                                ></v-text-field>
                                <span class="title">手机号:</span>
                                <v-text-field
                                        v-model="email"
                                        :rules="emailRules"
                                        label="E-mail"
                                        required
                                        solo
                                        class="mt-3 mb-4"
                                ></v-text-field>
                                <v-btn color="info" large class="mx-0">保存修改</v-btn>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
        </v-layout>
    </v-container>
</template>

<script>
    export default {
        name: "Profile"
    }
</script>

<style scoped>

</style>
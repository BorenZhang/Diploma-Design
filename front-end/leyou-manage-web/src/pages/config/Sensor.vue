<template>
    <v-container fluid>
        <v-layout row align-start justify-center>
            <v-flex xs12 sm10 md7>
                <v-card height="800">
                    <v-layout row class="py-3">
                        <v-flex xs10 sm10 md10 offset-xs1 offset-sm1 offset-md1>
                            <span class="headline">配置项</span>
                        </v-flex>
                    </v-layout>
                    <v-layout row>
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <v-subheader class="title">温度阈值：</v-subheader>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5">
                            <v-text-field
                                    id="temp"
                                    name="input-1"
                                    label="温度（℃）"
                            ></v-text-field>
                        </v-flex>
                    </v-layout>
                    <v-layout row>
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <v-subheader class="title">光照阈值：</v-subheader>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5">
                            <v-text-field
                                    id="light"
                                    name="input-1"
                                    label="光照（lx）"
                            ></v-text-field>
                        </v-flex>
                    </v-layout>
                    <v-layout row>
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <v-subheader class="title">数据接收间隔：</v-subheader>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5">
                            <v-text-field
                                    id="transdata"
                                    name="input-1"
                                    label="时间（s)"
                            ></v-text-field>
                        </v-flex>
                    </v-layout>
                    <v-layout row class="pb-3">
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <v-subheader class="title">自动开关风扇：</v-subheader>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5">
                            <v-switch :label="`${switch1?'开':'关'}`" v-model="switch1" hide-details
                                      class="pt-2"></v-switch>
                        </v-flex>
                    </v-layout>
                    <v-layout row class="pb-3">
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <v-subheader class="title">自动开关电灯：</v-subheader>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5">
                            <v-switch :label="`${switch2?'开':'关'}`" v-model="switch2" hide-details
                                      class="pt-2"></v-switch>
                        </v-flex>
                    </v-layout>
                    <v-layout row class="py-3">
                        <v-flex xs10 sm10 md4 offset-xs1 offset-sm1 offset-md1 class="pt-2 pl-2">
                            <div class="text-xs-justify pl-2">
                                <v-btn round color="primary" dark large>保存配置</v-btn>
                            </div>
                        </v-flex>
                        <v-flex xs10 sm10 md8 class="pr-5 pt-2">
                            <div>
                                <div class="text-xs-justify">
                                    <v-btn round dark large color="primary" @click.native.stop="dialog = !dialog">帮助</v-btn>
                                </div>
                            </div>
                        </v-flex>
                    </v-layout>
                    <v-dialog v-model="dialog" max-width="500px">
                        <v-card>
                            <v-card-text>
                                <small class="grey--text">
                                    温度阈值：自动开关风扇的温度临界点<br/>
                                    光照阈值：自动开关电灯的光照临界点<br/>
                                    数据接收间隔：开发板上传数据的时间间隔<br/>
                                    自动开关风扇：是否开启自动开关风扇功能<br/>
                                    自动开关电灯：是否开启自动开关电灯功能<br/>
                                </small>
                            </v-card-text>
                        </v-card>
                    </v-dialog>
                </v-card>
            </v-flex>
        </v-layout>
    </v-container>
</template>
<script>
    export default {
        name: "Sensor",
        data() {
            return {
                switch1: false,
                switch2: false,
                alert:false,
                dialog: false,
            }
        },
    }
</script>

<style scoped>

</style>
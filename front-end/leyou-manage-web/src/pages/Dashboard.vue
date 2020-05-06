<template>
    <v-container fluid grid-list-sm>
        <!--开发板选择器-->
        <v-layout justify-start align-center row wrap class="mx-1">
            <v-flex d-flex xs12 sm5 md2>
                <span class="headline" style="text-align: left;">选择IMSI号：</span>
            </v-flex>
            <v-flex d-flex xs12 sm5 md3 class="px-1">
                <v-select
                        v-model="select"
                        :items="items"
                        label="IMSI号"
                        solo
                        autocomplete
                        @input="refreshData"
                ></v-select>
            </v-flex>
        </v-layout>

        <v-divider class="my-3"></v-divider>

        <!--显示传感器数据-->
        <v-layout row wrap class="mx-1">
            <v-flex d-flex xs12>
                <span class="headline">传感器数据</span>
            </v-flex>
            <!--显示湿度-->
            <v-flex d-flex xs12 sm6 md3 class="my-2">
                <v-card light elevation="20" class="mx-3 my-0" height="130" @mouseenter="changeColor1(1)"
                        @mouseleave="changeColor2(1)">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex xs3 sm3 md3 :class="{green:isGreen,blue:!isGreen,'lighten-5':!isGreen}" align-center
                                    justify-center fill-height>
                                <v-layout align-center justify-center v-if="this.isGreen">
                                    <v-icon x-large color="white">opacity</v-icon>
                                </v-layout>
                                <v-layout align-center justify-center v-else>
                                    <v-icon x-large color="green">opacity</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex xs9 sm9 md9 fill-height>
                                <v-container class="pt-1 pl-2" fluid fill-height>
                                    <v-layout row wrap class="pt-0">
                                        <v-flex d-flex xs12 sm12 md12>
                                            <v-card-title primary-title class="pa-0">
                                                <span class="headline display-3">湿度:</span>
                                            </v-card-title>
                                        </v-flex>
                                        <v-flex xs10 sm10 md10 fill-height class="ma-0 pa-0">
                                            <div style="height: auto;text-align: center">
                                                <span class="display-3">
                                                {{sensor_data.humidity}}
                                                </span>
                                            </div>
                                        </v-flex>
                                        <v-flex xs2 sm2 md2 fill-height>
                                            <v-layout align-end justify-start fill-height class="pb-3">
                                                <span class="display-2">%</span>
                                            </v-layout>
                                        </v-flex>
                                    </v-layout>
                                </v-container>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <!--显示温度-->
            <v-flex d-flex xs12 sm6 md3 class="my-2">
                <v-card light elevation="20" class="mx-3 my-0" height="130" @mouseenter="changeColor1(2)"
                        @mouseleave="changeColor2(2)">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex xs3 sm3 md3 :class="{red:isRed,blue:!isRed,'lighten-5':!isRed}" align-center
                                    justify-center fill-height>
                                <v-layout align-center justify-center v-if="this.isRed">
                                    <v-icon x-large color="white">flare</v-icon>
                                </v-layout>
                                <v-layout align-center justify-center v-else>
                                    <v-icon x-large color="red">flare</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex xs9 sm9 md9 fill-height>
                                <v-container class="pt-1 pl-2" fluid fill-height>
                                    <v-layout row wrap class="pt-0">
                                        <v-flex d-flex xs12 sm12 md12>
                                            <v-card-title primary-title class="pa-0">
                                                <span class="headline display-3">温度:</span>
                                            </v-card-title>
                                        </v-flex>
                                        <v-flex xs10 sm10 md10 fill-height class="ma-0 pa-0">
                                            <div style="height: auto;text-align: center">
                                                <span class="display-3">
                                                {{sensor_data.temp}}
                                                </span>
                                            </div>
                                        </v-flex>
                                        <v-flex xs2 sm2 md2 fill-height>
                                            <v-layout align-end justify-start fill-height class="pb-3">
                                                <span class="display-2">℃</span>
                                            </v-layout>
                                        </v-flex>
                                    </v-layout>
                                </v-container>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <!--显示光照-->
            <v-flex d-flex xs12 sm6 md3 class="my-2">
                <v-card light elevation="20" class="mx-3 my-0" height="130" @mouseenter="changeColor1(3)"
                        @mouseleave="changeColor2(3)">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex xs3 sm3 md3 :class="{orange:isOrange,blue:!isOrange,'lighten-5':!isOrange}"
                                    align-center justify-center fill-height>
                                <v-layout align-center justify-center v-if="this.isOrange">
                                    <v-icon x-large color="white">brightness_5</v-icon>
                                </v-layout>
                                <v-layout align-center justify-center v-else>
                                    <v-icon x-large color="orange">brightness_5</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex xs9 sm9 md9 fill-height>
                                <v-container class="pt-1 pl-2" fluid fill-height>
                                    <v-layout row wrap class="pt-0">
                                        <v-flex d-flex xs12 sm12 md12>
                                            <v-card-title primary-title class="pa-0">
                                                <span class="headline display-3">光照:</span>
                                            </v-card-title>
                                        </v-flex>
                                        <v-flex xs10 sm10 md10 fill-height class="ma-0 pa-0">
                                            <div style="height: auto;text-align: center">
                                                <span class="display-3">
                                                {{sensor_data.light}}
                                                </span>
                                            </div>
                                        </v-flex>
                                        <v-flex xs2 sm2 md2 fill-height>
                                            <v-layout align-end justify-start fill-height class="pb-3">
                                                <span class="display-2">lx</span>
                                            </v-layout>
                                        </v-flex>
                                    </v-layout>
                                </v-container>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <!--显示声音-->
            <v-flex d-flex xs12 sm6 md3 class="my-2">
                <v-card light elevation="20" class="mx-3 my-0" height="130" @mouseenter="changeColor1(4)"
                        @mouseleave="changeColor2(4)">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex xs3 sm3 md3 :class="{cyan:isCyan,blue:!isCyan,'lighten-5':!isCyan}" align-center
                                    justify-center fill-height>
                                <v-layout align-center justify-center v-if="this.isCyan">
                                    <v-icon x-large color="white">record_voice_over</v-icon>
                                </v-layout>
                                <v-layout align-center justify-center v-else>
                                    <v-icon x-large color="cyan">record_voice_over</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex xs9 sm9 md9 fill-height>
                                <v-container class="pt-1 pl-2" fluid fill-height>
                                    <v-layout row wrap class="pt-0">
                                        <v-flex d-flex xs12 sm12 md12>
                                            <v-card-title primary-title class="pa-0">
                                                <span class="headline display-3">声音:</span>
                                            </v-card-title>
                                        </v-flex>
                                        <v-flex xs10 sm10 md10 fill-height class="ma-0 pa-0">
                                            <div style="height: auto;text-align: center">
                                                <span class="display-3">
                                                {{sensor_data.sound}}
                                                </span>
                                            </div>
                                        </v-flex>
                                        <v-flex xs2 sm2 md2 fill-height>
                                            <v-layout align-end justify-start fill-height class="pb-3">
                                                <span class="display-2">dB</span>
                                            </v-layout>
                                        </v-flex>
                                    </v-layout>
                                </v-container>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <!--显示人体感应-->
            <v-flex d-flex xs12 sm6 md3 class="my-2">
                <v-card light elevation="20" class="mx-3 my-0" height="130" @mouseenter="changeColor1(5)"
                        @mouseleave="changeColor2(5)">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex xs3 sm3 md3 :class="{purple:isPurple,blue:!isPurple,'lighten-5':!isPurple}"
                                    align-center justify-center fill-height>
                                <v-layout align-center justify-center v-if="this.isPurple">
                                    <v-icon x-large color="white">person</v-icon>
                                </v-layout>
                                <v-layout align-center justify-center v-else>
                                    <v-icon x-large color="purple">person</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex xs9 sm9 md9 fill-height>
                                <v-container class="pt-1 pl-2" fluid fill-height>
                                    <v-layout row wrap class="pt-0">
                                        <v-flex d-flex xs12 sm12 md12>
                                            <v-card-title primary-title class="pa-0">
                                                <span class="headline display-3">人体感应:</span>
                                            </v-card-title>
                                        </v-flex>
                                        <v-flex xs12 sm12 md12 fill-height class="ma-0 pa-0">
                                            <div style="height: auto;text-align: center">
                                                <span class="display-3">
                                                {{sensor_data.human}}
                                                </span>
                                            </div>
                                        </v-flex>
                                    </v-layout>
                                </v-container>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
        </v-layout>
        <!--分隔条-->
        <v-divider class="my-3"></v-divider>
        <!--远程控制-->
        <v-layout row wrap class="mx-1">
            <v-flex d-flex xs12 class="py-2">
                <span class="headline">远程控制:</span>
            </v-flex>
            <!--远程控制风扇-->
            <v-flex d-flex xs12 sm6 md3>
                <v-card light elevation="20" class="mr-3 ml-2 my-0 pa-0" height="130">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex d-flex xs6 sm6 md6 v-if="fan_switch==true">
                                <v-layout align-center justify-center fill-height>
                                    <v-icon x-large color="green">ac_unit</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex d-flex xs6 sm6 md6 v-else="fan_switch==false">
                                <v-layout align-center justify-center fill-height>
                                    <v-icon x-large color="grey">ac_unit</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex d-flex xs6 sm6 md6>
                                <v-layout row wrap justify-end align-center class="py-2">
                                    <span class="px-3 headline ql-font">风扇开关:</span>
                                    <v-switch
                                            v-model="fan_switch"
                                            hide-details
                                            class="px-1"
                                            @change="sendMessage(1)"
                                            :disabled="disabled"
                                    ></v-switch>
                                </v-layout>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
            <!--远程控制电灯-->
            <v-flex d-flex xs12 sm6 md3>
                <v-card light elevation="20" class="mr-3 ml-2 my-0" height="130">
                    <v-container fluid class="pa-0" fill-height>
                        <v-layout row wrap>
                            <v-flex d-flex xs6 sm6 md6 v-if="led_switch==true">
                                <v-layout align-center justify-center fill-height>
                                    <v-icon x-large color="yellow">wb_incandescent</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex d-flex xs6 sm6 md6 v-else="led_switch==false">
                                <v-layout align-center justify-center fill-height>
                                    <v-icon x-large color="grey">wb_incandescent</v-icon>
                                </v-layout>
                            </v-flex>
                            <v-flex d-flex xs6 sm6 md6>
                                <v-layout row wrap justify-end align-center class="py-2">
                                    <span class="px-3 headline ql-font">电灯开关:</span>
                                    <v-switch
                                            v-model="led_switch"
                                            hide-details
                                            class="px-1"
                                            @change="sendMessage(2)"
                                            :disabled="disabled"
                                    ></v-switch>
                                </v-layout>
                            </v-flex>
                        </v-layout>
                    </v-container>
                </v-card>
            </v-flex>
        </v-layout>
        <!--分隔条-->
        <v-divider class="my-3"></v-divider>
        <!--曲线图-->
        <v-layout row wrap class="mx-1">
            <v-flex d-flex xs12 class="py-2">
                <span class="headline">实时温度:</span>
            </v-flex>
            <v-flex d-flex xs12 sm10 md10>
                <v-card>
                    <v-card-text class="px-2">
                        <div ref="temp" style="width: 100%;height: 300px;"></div>
                    </v-card-text>
                </v-card>
            </v-flex>
        </v-layout>
        <v-dialog v-model="dialog" width="500px">
            <v-alert icon="warning" color="error" :value="true">
                {{dialog_message}}
            </v-alert>
        </v-dialog>
    </v-container>
</template>

<script>
    // 引入 ECharts 主模块
    var echarts = require('echarts/lib/echarts');
    require('echarts/lib/chart/line');
    require('echarts/lib/chart/bar');
    require('echarts/lib/component/title')
    require('echarts/lib/component/tooltip')
    require('echarts/lib/component/toolbox')
    require('echarts/lib/component/legend')


    export default {
        name: "dashboard",
        data: () => ({
            sensor_data: {
                imsi: '',
                frameID: '',
                temp: '暂无',
                mcutemp: '暂无',
                humidity: '暂无',
                light: '暂无',
                sound: '暂无',
                human: '暂无',
                led: '',
                fan: '',
                state: 'CAN_CHANGE_SWITCH',
            },
            select: null,
            items: ["460113003233156"],
            isGreen: false,
            isRed: false,
            isOrange: false,
            isCyan: false,
            isPurple: false,
            dialog: false,
            dialog_message: '',
            led_switch: false,
            fan_switch: false,
            switch_flag: true,
            disabled: false,
            frameID: '',
            env_temps: [15,15,15,15,15,15,15],  //环境温度集合
            MCU_temps: [20,20,20,20,20,20,20],  //MCU温度集合
        }),
        created() {
            setInterval(this.getSendState, 1000)
        },
        mounted() {
            this.$nextTick(() => {
                let temp=echarts.init(this.$refs.temp);
                let option={
                    title: {
                        text: '最近温度变化',
                            subtext: '环境温度/MCU温度'
                    },
                    tooltip: {
                        trigger: 'axis'
                    },
                    legend: {
                        data: ['环境温度', 'MCU温度']
                    },
                    toolbox: {
                        show: true,
                            feature: {
                            dataZoom: {
                                yAxisIndex: 'none'
                            },
                            dataView: {readOnly: false},
                            magicType: {type: ['line', 'bar']},
                            restore: {},
                            saveAsImage: {}
                        }
                    },
                    xAxis: {
                        type: 'category',
                            boundaryGap: false,
                            data: ['210s前', '3分前', '150s前', '2分前', '90s前', '1分前', '30s前']
                    },
                    yAxis: {
                        type: 'value',
                            axisLabel: {
                            formatter: '{value} °C'
                        }
                    },
                    series: [
                        {
                            name: '环境温度',
                            type: 'line',
                            data: this.env_temps,
                            markPoint: {
                                data: [
                                    {type: 'max', name: '最大值'},
                                    {type: 'min', name: '最小值'}
                                ]
                            },
                            markLine: {
                                data: [
                                    {type: 'average', name: '平均值'}
                                ]
                            }
                        },
                        {
                            name: 'MCU温度',
                            type: 'line',
                            data: this.MCU_temps,
                            markPoint: {
                                data: [
                                    {name: '周最低', value: -2, xAxis: 1, yAxis: -1.5}
                                ]
                            },
                            markLine: {
                                data: [
                                    {type: 'average', name: '平均值'},
                                    [{
                                        symbol: 'none',
                                        x: '90%',
                                        yAxis: 'max'
                                    }, {
                                        symbol: 'circle',
                                        label: {
                                            position: 'start',
                                            formatter: '最大值'
                                        },
                                        type: 'max',
                                        name: '最高点'
                                    }]
                                ]
                            }
                        }
                    ]
                };
                setInterval(function () {
                    temp.setOption(option);
                },1000);
            })
        },
        methods: {
            changeColor1(index) {
                if (index == 1) {
                    this.isGreen = true;
                } else if (index == 2) {
                    this.isRed = true;
                } else if (index == 3) {
                    this.isOrange = true;
                } else if (index == 4) {
                    this.isCyan = true;
                } else if (index == 5) {
                    this.isPurple = true;
                }

            },
            changeColor2(index) {
                if (index == 1) {
                    this.isGreen = false;
                } else if (index == 2) {
                    this.isRed = false;
                } else if (index == 3) {
                    this.isOrange = false;
                } else if (index == 4) {
                    this.isCyan = false;
                } else if (index == 5) {
                    this.isPurple = false;
                }
            },
            getSensorData() {
                this.$http.get("/sensor/data", {
                    params: {
                        imsi: this.select
                    }
                })
                    .then(
                        resp => {
                            //resp.data获取的值，会自动转换为小写字母，所以vue的data中定义数据和后台有关时，使用小写
                            console.log(resp)
                            if (resp.status == 200) {
                                this.sensor_data = resp.data;
                                if (this.frameID != this.sensor_data.frameID) {  //新的一帧到来
                                    this.frameID = this.sensor_data.frameID;
                                    for(let i=0;i<6;i++){
                                        this.env_temps[i]=this.env_temps[i+1];
                                        this.MCU_temps[i]=this.MCU_temps[i+1];
                                    }
                                    this.env_temps[6]=this.sensor_data.temp;
                                    this.MCU_temps[6]=this.sensor_data.mcutemp;
                                    this.fan_switch = this.sensor_data.fan == "1" ? false : true;
                                    this.led_switch = this.sensor_data.led == "1" ? false : true;
                                }
                                this.sensor_data.human = this.sensor_data.human == "1" ? "有人" : "无人";
                            }
                        }
                    )
                    .catch(
                        () => {
                            this.dialog_message = "数据获取失败";
                            this.dialog = true;
                        }
                    )
            },
            refreshData() {
                this.getSensorData();
                setInterval(this.getSensorData, 2000)
            },
            sendMessage(index) {
                if (this.select == null) {
                    this.dialog_message = "请选择开发板";
                    this.dialog = true;
                } else {
                    this.sensor_data.led = this.led_switch ? "0" : "1";
                    this.sensor_data.fan = this.fan_switch ? "0" : "1";
                    this.$http.post('/sensor/send', this.$qs.stringify(this.sensor_data))
                        .then(
                            () => {
                                if (index == 1) {
                                    this.fan_switch = this.sensor_data.fan == "1" ? false : true;
                                } else if (index == 2) {
                                    this.led_switch = this.sensor_data.led == "1" ? false : true;
                                }
                            }
                        )
                        .catch(
                            () => {
                                //this.dialog_message = "数据获取失败";
                                //this.dialog = true;  //数据获取失败时提示
                            }
                        )
                }
            },
            getSendState() {
                this.$http.get('/sensor/getSendState')
                    .then(
                        resp => {
                            this.disabled = !resp.data
                        }
                    )
            },
        }
    }
</script>

<style scoped>

</style>

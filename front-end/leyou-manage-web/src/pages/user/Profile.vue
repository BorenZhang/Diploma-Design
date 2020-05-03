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
                        <v-divider class="my-3"></v-divider>
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
                        <v-layout row wrap>
                            <v-flex>
                                <span class="headline">Education</span>
                            </v-flex>
                        </v-layout>
                        <!--分隔条-->
                        <v-divider class="my-3"></v-divider>
                    </v-container>
                </v-card>
            </v-flex>
            <v-flex xs12 sm7 md9>
                <v-card height="800">

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
import { createApp } from 'vue'
import { createRouter, createWebHashHistory } from 'vue-router'
import Main from './components/Main.vue'
import App from './App.vue'

const app = createApp(App)

const router = createRouter({
  history: createWebHashHistory(),
  routes: [
   { path: '/', component: Main } 
  ]
})

app.use(router)

app.mount('#app')
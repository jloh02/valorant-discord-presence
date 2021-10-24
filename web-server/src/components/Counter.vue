<template>
  <p>Counter:</p>
  <p>{{ count }}</p>
  <button @click="increment">Click to +1</button>
</template>

<script>
  export default {
    name: 'Counter',
    data() {
      return { count: 1 }
    },
    methods: { 
      increment(){
        this.count++
        console.log('count is: ' + this.count)
      }
    },
    created() {
      // `this` points to the vm instance
      console.log('count is: ' + this.count) // => "count is: 1"
    }
}
</script>

<style>
  h3 {
    margin-bottom: 5%;
  }
</style>
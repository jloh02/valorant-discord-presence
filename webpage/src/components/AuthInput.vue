<template>
  <div class="input-container">
    <div class="input-box">
      <input :type="type" @input="onInput" alt="tt" required />
      <span class="input-label">{{ label }}</span>
      <!-- TODO: see/unseen password using v-if -->
    </div>
  </div>
</template>

<script>
export default {
  name: "AuthInput",
  props: ["label", "type", "fieldInput"],
  methods: {
    onInput(v) {
      this.$emit("on-field-input", v.target.value);
    },
  },
};
</script>

<style>
div.input-container {
  display: flex;
  align-items: flex-start;
  justify-content: space-around;
}

div.input-box {
  position: relative;
  width: 100%;
  margin-top: 2rem;
  border: 1px solid whitesmoke;
  border-radius: 4px;
}

input {
  color: whitesmoke;
  background-color: transparent;
  border: none;

  margin: 0.5rem;
  width: 100%;
  height: 1.5rem;
  font-size: 1rem;
  padding-left: 0.875rem;
  line-height: 147.6%;
  padding-top: 0.5rem;
  padding-bottom: 0.5rem;
}

input:focus {
  outline: none;
}

span.input-label {
  color: whitesmoke;
  position: absolute;
  top: 1rem;
  left: 1.1rem;
  line-height: 150%;
  transition: top 0.2s, left 0.2s, background-color 0.2s, font-size 0.2s;
  padding: 0 5px;
}

input:focus + span.input-label,
input:valid + span.input-label {
  font-size: 0.9rem;
  top: -0.7rem;
  left: 0.8rem;
  display: block;
  background-color: #666666;
}
</style>
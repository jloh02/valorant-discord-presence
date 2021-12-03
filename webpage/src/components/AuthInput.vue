<template>
  <div class="input-container">
    <div class="input-box">
      <input :type="inputType" @input="onInput" :alt="label" required />
      <span class="input-label">{{ label }}</span>
      <button
        v-if="label === 'Password' && currentInput"
        @click="showHidePw"
        class="show-hide-button"
        type="button"
      >
        <svg
          v-if="inputType === 'password'"
          xmlns="http://www.w3.org/2000/svg"
          viewBox="0 0 24 24"
          height="24px"
          width="24px"
          fill="#FFFFFF"
        >
          <path d="M0 0h24v24H0z" fill="none" />
          <path
            d="M12 4.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5zM12 17c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z"
          />
        </svg>
        <svg
          v-else
          xmlns="http://www.w3.org/2000/svg"
          height="24px"
          viewBox="0 0 24 24"
          width="24px"
          fill="#FFFFFF"
        >
          <path
            d="M0 0h24v24H0zm0 0h24v24H0zm0 0h24v24H0zm0 0h24v24H0z"
            fill="none"
          />
          <path
            d="M12 7c2.76 0 5 2.24 5 5 0 .65-.13 1.26-.36 1.83l2.92 2.92c1.51-1.26 2.7-2.89 3.43-4.75-1.73-4.39-6-7.5-11-7.5-1.4 0-2.74.25-3.98.7l2.16 2.16C10.74 7.13 11.35 7 12 7zM2 4.27l2.28 2.28.46.46C3.08 8.3 1.78 10.02 1 12c1.73 4.39 6 7.5 11 7.5 1.55 0 3.03-.3 4.38-.84l.42.42L19.73 22 21 20.73 3.27 3 2 4.27zM7.53 9.8l1.55 1.55c-.05.21-.08.43-.08.65 0 1.66 1.34 3 3 3 .22 0 .44-.03.65-.08l1.55 1.55c-.67.33-1.41.53-2.2.53-2.76 0-5-2.24-5-5 0-.79.2-1.53.53-2.2zm4.31-.78l3.15 3.15.02-.16c0-1.66-1.34-3-3-3l-.17.01z"
          />
        </svg>
      </button>
    </div>
  </div>
</template>

<script>
export default {
  name: "AuthInput",
  data() {
    return {
      inputType: this.type,
      currentInput: "",
    };
  },
  props: ["label", "type", "fieldInput"],
  methods: {
    onInput(v) {
      this.currentInput = v.target.value;
      this.$emit("on-field-input", v.target.value);
    },
    showHidePw() {
      this.inputType = this.inputType === "password" ? "text" : "password";
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
  display: flex;
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
  pointer-events: none;

  -webkit-touch-callout: none;
  -webkit-user-select: none;
  -khtml-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}

input:focus + span.input-label,
input:valid + span.input-label {
  font-size: 0.9rem;
  top: -0.7rem;
  left: 0.8rem;
  display: block;
  background-color: #666666;
}

button.show-hide-button,
button.show-hide-button:hover {
  background-color: transparent;
  margin: 0.2rem;
  border: none;
  text-decoration: none;
  display: flex;
  flex-direction: column;
  justify-content: center;
}
</style>
<template>
      <div class="login-form">
<!--        <form>-->
          <fieldset>
            <legend>Login</legend>
            <div class="form-group">
              <label>Username</label>
              <input id="username" name="username" type="text" placeholder="Username" class="form-control" v-model="auth.username"/>
            </div>
            <div class="form-group">
              <label>Password</label>
              <input id="password" name="password" type="password" placeholder="Password" class="form-control" v-model="auth.password"/>
            </div>
            <div class="form-group">
              <label>Database</label>
              <input id="database" name="database" type="text" placeholder="Database. Ex: test" class="form-control" v-model="auth.database"/>
            </div>
            <div class="log-in-button">
              <button @click="handleLogin(auth)">Login</button>
            </div>
          </fieldset>
<!--        </form>-->
      </div>
</template>

<script>
export default {
  name: "Login",
  data() {
    return {
      auth: {
        username: '',
        password: '',
        database: '',
      }
    }
  },
  methods: {
    handleLogin: function(auth) {
      localStorage.setItem('auth', JSON.stringify(auth));
      localStorage.setItem('currentDatabase', auth.database);
      alert('logged in');
      this.$router.push('/')
    }
  }
}
</script>

<style scoped>

</style>
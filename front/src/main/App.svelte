<script lang="ts">
  import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
</script>

<main>
  <div class="flex flex-col items-center min-h-screen justify-center gap-5">
      <p class="text-mono text-8xl text-white">Bitlace</p>
      <div class="flex flex-row items-center gap-3">
        <img
          src="/src/main/assets/gluten.svg"
          alt="Glutesha logo"
          class="size-10"
        />
        <p class="text-mono text-3xl text-white">By Glutesha Devices</p>
  </div>
  <div class="flex justify-center items-center">
    <Display />
  </div>
  <div class="flex justify-center items-center p-5">
    <Erase />
  </div>
</main>
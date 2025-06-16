<script lang="ts">
  import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
</script>

<main>
  <div class="flex flex-col items-center min-h-screen justify-center font-mono gap-5">
      <p class="text-8xl font-bold text-white">Bitlace</p>
      <div class="flex flex-row items-center gap-3">
        <img
          src="/src/main/assets/gluten.svg"
          alt="Glutesha logo"
          class="size-10"
        />
        <p class="text-3xl text-white">By Glutesha Devices</p>
  </div>
  <div class="flex justify-center items-center">
    <Display />
  </div>
  <div class="flex justify-center items-center gap-5 p-5 mr-3">
    <a href="/settings/"><button class="bg-lime-800 hover:bg-lime-900 active:bg-lime-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl shadow-2xl font-bold shadow-neutral-900">Settings</button></a>
    <Erase />
  </div>

</main>
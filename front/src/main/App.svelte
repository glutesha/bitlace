<script lang="ts">
  import Battery from './lib/Battery.svelte';
import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
    import Settings from './lib/Settings.svelte';
</script>

<main>
  <Battery />
  <div class="flex pt-8 flex-col items-center min-h-screen justify-center font-mono gap-2">
    <p class="text-7xl font-bold text-white">Bitlace</p>
    <div class="flex flex-row items-center gap-3">
      <img
        src="gluten.svg"
        alt="Glutesha logo"
        class="size-10"
      />
      <p class="text-2xl text-white">By Glutesha Devices</p>
  </div>
  <div class="flex justify-center items-center">
    <Display />
  </div>
  <div class="flex justify-center items-center gap-5 p-5 mr-3">
    <Settings />
    <Erase />
  </div>

</main>